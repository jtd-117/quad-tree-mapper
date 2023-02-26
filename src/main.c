/**
 * @file    main.c
 * @brief   A program to map & query data into a quad-tree
 * @author  Jude Thaddeau Data
 * @note    GitHub: https://github.com/jtd-117
*/
/* -------------------------------------------------------------------------- */

// LIBRARIES & RELEVANT HEADER FILES:
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "cmp.h"
#include "data.h"
#include "coordinates.h"
#include "dynamic-array.h"
#include "quad-tree.h"
#include "sll.h"

/* -------------------------------------------------------------------------- */

// CONSTANT DEFINITIONS:
#define MIN_ARGS 7
#define MODE_1 1
#define MODE_2 2

#define MODE_ARG 1
#define CSV_ARG 2
#define OUTPUT_ARG 3
#define X_BOTTOM_LEFT_ARG 4
#define Y_BOTTOM_LEFT_ARG 5
#define X_TOP_RIGHT_ARG 6
#define Y_TOP_RIGHT_ARG 7

/* -------------------------------------------------------------------------- */

// FUNCTION PROTOTYPES:
void process_args(int argc, char **argv);
long double custom_strtold(const char *str);
void point_query(FILE *output_file, qt_tree_t *tree);
void range_query(FILE *output_file, qt_tree_t *tree);

/* -------------------------------------------------------------------------- */

int main(int argc, char **argv) {

    // STEP 1: Check the validity of the program arguments
    process_args(argc, argv);

    // STEP 2: Record the input arguments into variables
    int stage_number = atoi(argv[MODE_ARG]);
    FILE *input_file = fopen(argv[CSV_ARG], "r");
    FILE *output_file = fopen(argv[OUTPUT_ARG], "w");
    assert((input_file != NULL) && (output_file != NULL));

    // STEP 3: Intialise the quad-tree (SEARCH coordinates)
    point_2d_t root_bounds_bl = 
        point_2d_init(custom_strtold(argv[X_BOTTOM_LEFT_ARG]), 
        custom_strtold(argv[Y_BOTTOM_LEFT_ARG]));
    point_2d_t root_bounds_tr = 
        point_2d_init(custom_strtold(argv[X_TOP_RIGHT_ARG]), 
        custom_strtold(argv[Y_TOP_RIGHT_ARG]));
    rectangle_t root_bounds = rectangle_init(root_bounds_bl, root_bounds_tr);
    qt_tree_t *qtree = qt_tree_init(root_bounds);

    // STEP 4: Initialise the linked-list (STORE data entries)
    sll_t *list = dll_init();

    // STEP 5: Skip the header & read the data into the quad-tree
    data_t *tmp_data = NULL;
    point_2d_t *tmp_point = NULL;

    file_skip_line(input_file);
    while ((tmp_data = read_line_data(input_file, tmp_data)) != NULL) {

        // STEP 5A: Read & insert the start_lon & start_lat
        tmp_point = point_2d_malloc(tmp_data->start_lon, tmp_data->start_lat);
        qt_insert(qtree, tmp_point, tmp_data);
        tmp_point = NULL;

        // STEP 5B: Read & insert end_lon & end_lat
        tmp_point = point_2d_malloc(tmp_data->end_lon, tmp_data->end_lat);
        qt_insert(qtree, tmp_point, tmp_data);
        tmp_point = NULL;

        // STEP 5C: Store the data into the linked-list
        dll_insert_tail(list, tmp_data);
    }

    // STEP 6: Perform the stage-specifc tasks of STAGE 3 or 4
    if (stage_number == MODE_1) {
        stage_three_query(output_file, qtree);
    } else if (stage_number == MODE_2) {
        stage_four_query(output_file, qtree);
    }
    
    // STEP 7: Free the heap of previous memory allocations, & close files
    dll_free(list);
    qt_free(qtree);
    fclose(input_file);
    fclose(output_file);
    return 0;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       Checks if the arguments are correct before program execution
 * @param[out]  argc    The number of arguments
 * @param[in]   argv    An 2D array of characters for storing argument names
*/
void 
process_args(int argc, char **argv) {
    
    // CASE 1: Insufficient number of arguments
    if ((argc < MIN_ARGS) || (argc > MIN_ARGS + 1)) {
        fprintf(stderr, "ERROR: Invalid number of arguments\n");
        fprintf(stderr, "Only %d were supplied. %d OR %d arguments required\n", 
            argc, MIN_ARGS, MIN_ARGS + 1);
        exit(EXIT_FAILURE);
    }
    // CASE 2: Stage arguments must be either '3' or '4'
    if ((atoi(argv[MODE_ARG]) < MODE_1) || 
        (atoi(argv[MODE_ARG]) > MODE_2)) {
        fprintf(stderr, "ERROR: 1st argument, %s, must equal either 3 or 4\n", 
            argv[MODE_ARG]);
        exit(EXIT_FAILURE);
    }
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       Same as strtold - ignores the non-numeric characters
 * @param[in]   str     The string to extract a long double from
 * @return      A long double extracted from str
*/
long double 
custom_strtold(const char *str) {
    long double result;
    char *garbage;
    result = strtold(str, &garbage);
    return result;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       Takes input coordinates from STDIN, checks if they exist in 
 *              quad-tree & then returns matched entries
 * @param[in]   output_file     The file to write output to
 * @param[in]   tree            Contains coordinates for quick look-up
*/
void 
point_query(FILE *output_file, qt_tree_t *tree) {

    char read[MAX_STR_LEN + 1];
    point_2d_t query;
    qt_node_t *search = NULL;
    char path[MAX_PATH_LENGTH + 1] = "";

    // STEP 1: Read the queries from STDIN
    while (scanf("%[^\n]\n", read) == 1) {
        assert(sscanf(read ,"%Lf %Lf\n", &query.x, &query.y) == 2);

        // STEP 2: Search the quad-tree for the query
        if ((search = qt_search(tree, &query, path)) != NULL) {

            // STEP 3: Print the findings to the output file
            fprintf(output_file, "%s\n", read);
            for (int i = 0; i < search->items->logical_size; i++) {
                print_data_to_file(output_file, search->items->data[i]);
            }

            // STEP 4: Print the findings to STDOUT
            printf("%s -->", read);
            printf("%s\n", path);
            strcpy(path, "");
        }
    }
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       Takes input boundaries (i.e. ranges) from STDIN & prints all
 *              the points that exists within the query range
 * @param[in]   output_file     The file to print the outputs to
 * @param[in]   tree            The quad-tree to range query
*/
void 
range_query(FILE *output_file, qt_tree_t *tree) {

    char read[MAX_STR_LEN + 1];
    long double bl_x, bl_y, tr_x, tr_y;
    rectangle_t range;
    array_t *matches = NULL;
    char path[MAX_PATH_LENGTH + 1] = "";

    // STEP 1: Read the queries from STDIN
    while (scanf("%[^\n]\n", read) == 1) {
        assert(sscanf(read, "%Lf %Lf %Lf %Lf\n", 
            &bl_x, &bl_y, &tr_x, &tr_y) == 4);
        range = rectangle_init(
            point_2d_init(bl_x, bl_y), point_2d_init(tr_x, tr_y));

        // STEP 2: Query the quad-tree
        if ((matches = qt_range_query(tree, path, &range)) != NULL) {

            // STEP 3: Print the findings to the output
            fprintf(output_file, "%s\n", read);
            for (int i = 0; i < matches->logical_size; i++) {
                print_data_to_file(output_file, matches->data[i]);
            }

            // STEP 4: Print the data to STDOUT
            printf("%s -->", read);
            printf("%s\n", path);
            strcpy(path, "");

            // STEP 5: Free array_t to make way for the next query
            array_free(matches);
        }
    }
}