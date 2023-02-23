/**
 * @file    data.c
 * @brief   Contains the structure implementation for the Melbourne City
 *          CSV data
 * @author  Jude Thaddeau Data
 * @note    GitHub: https://github.com/jtd-117
*/
/* -------------------------------------------------------------------------- */

// LIBRARIES & RELEVANT HEADER FILES:
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "data.h"

/* -------------------------------------------------------------------------- */

/**
 * @brief       UTILITY - SKIPS a line from an input file
 * @param[in]   file    The file whose line is to be SKIPPED
 * @note        ACKNOWLEDGEMENT
 *              Code used from COMP20003 Ed Discussion: W3.7's 
 *              data.c file
*/
void 
file_skip_line(FILE *file) {
    while (fgetc(file) != '\n');
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       UTILITY - Initialises the data structure
 * @return      A pointer to an initialised data in the heap
*/
data_t *data_init(void) {

    // Allocate to the heap & ensure it exists
    data_t *new_data = (data_t *)malloc(sizeof(data_t));
    assert(new_data != NULL);
    new_data->address = new_data->clue_sa = 
        new_data->asset_type = new_data->segside = NULL;
    return new_data;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       UTILITY - returns a field from a csv line
 * @param[in]   input_file  The CSV file with cursor at a string
 * @param[out]  dest        The pointer where the string to be saved
 * @return      A pointer to a string from a CSV field
 * @note        ASSUMES the next field is a string
*/
char* 
get_csv_string(FILE *input_file, char *dest) {

    // STEP 1: Ensure the file is NOT empty
    assert(input_file != NULL);

    // STEP 2: Initialise the variables
    char string_field[MAX_STR_LEN + 1];
    int index = 0;
    char delim;

    // STEP 3: Need to pick our delimiter value based off the first character
    int character = fgetc(input_file);
    if (feof(input_file)) return NULL;

    // CASE 1 - 1st character is a DOUBLE quote (i.e. string encased in "quote")
    if (character == DOUBLE_QUOTE) {
        delim = DOUBLE_QUOTE;
        character = fgetc(input_file);
        string_field[index++] = character;

    // CASE 2 - 1st string is a COMMA (i.e. field is EMPTY)
    } else if (character == COMMA) {
        dest = (char *)malloc(sizeof(char));
        *dest = '\0';
        return dest;

    // CASE 3 - 1st string is non-of-the-above (i.e. stop at next COMMA)
    } else {
        delim = COMMA;
        string_field[index++] = character;
    }

    // STEP 4: Keep saving each valid character into a temporary array
    while ((character = fgetc(input_file)) != delim) {

        // Need to ensure we have not reached EOF
        if (feof(input_file)) return NULL;
        string_field[index++] = character;
    }
    string_field[index] = '\0';

    // STEP 5: Can now save space on the heap to allocare it dynamically
    dest = (char *)malloc((sizeof(char) * strlen(string_field)) + 1);
    assert(dest != NULL);
    strcpy(dest, string_field);

    // EXCEPTION: Remove the delimiter for the next field
    if (delim == DOUBLE_QUOTE) {
        character = fgetc(input_file);
    }
    return dest;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       UTILITY - Reads a single CSV line
 * @param[in]   file        The input CSV file to be read
 * @param[out]  new_data    New data to be inserted
 * @return      A pointer to the heap allocated data
*/
data_t* 
read_line_data(FILE *file, data_t *new_data) {

    new_data = data_init();

    // STEP 1: Read CSV entries one-by-one
    if (fscanf(file, "%d,", &new_data->foothpath_id) != 1) {
        free_data(new_data);
        return NULL;
    }

    // STEP 2: Read the data one-by-one
    new_data->address = get_csv_string(file, new_data->address);
    new_data->clue_sa = get_csv_string(file, new_data->clue_sa);
    new_data->asset_type = get_csv_string(file, new_data->asset_type);

    if (fscanf(file, "%Lf,%Lf,%Lf,%Lf,%d.0,%Lf,%Lf,", 
        &new_data->deltaz, &new_data->distance, &new_data->grade1in, 
        &new_data->mcc_id, &new_data->mccid_int, &new_data->rlmax, 
        &new_data->rlmin) != 7) {
        free_data(new_data);
        return NULL;
    }
    
    new_data->segside = get_csv_string(file, new_data->segside);

    if (fscanf(file, "%d.0,%d.0,%d.0,%Lf,%Lf,%Lf,%Lf\n", 
        &new_data->statusid, &new_data->streetid, &new_data->street_group, 
        &new_data->start_lat, &new_data->start_lon, &new_data->end_lat, 
        &new_data->end_lon) != 7) {
            free_data(new_data);
            return NULL;
    }
    return new_data;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       DELETES data_t from the heap's deallocated memory
 * @param[in]   data    The data to freed from the heap
*/
void 
free_data(data_t *data) {

    // STEP 1: Need to ensure data_t exists on the heap
    if (data == NULL) {
        return;
    }
    // STEP 2: Need to check all the string arguments
    if (data->address) free(data->address);
    if (data->clue_sa) free(data->clue_sa);
    if (data->asset_type) free(data->asset_type);
    if (data->segside) free(data->segside);

    // STEP 3: Can now free the entire data_t structure
    free(data);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       PRINTS all fields in the structure data_t
 * @param[in]   data    The structure whose components are to be printed
*/
void 
print_data(data_t *data) {
    printf("\n%d,%s,%s,%s,%Lf,%Lf,%Lf,%Lf,%d,%Lf,%Lf,",
        data->foothpath_id, data->address, data->clue_sa, data->asset_type,
        data->deltaz, data->distance, data->grade1in, data->mcc_id,
        data->mccid_int, data->rlmax, data->rlmin);
    printf("%s,%d,%d,%d,%Lf,%Lf,%Lf,%Lf\n", 
        data->segside, data->statusid, data->streetid, data->street_group, 
        data->start_lat, data->start_lon, data->end_lat, data->end_lon);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       UTILITY - Prints data that share (i.e. match) the same key
 * @param[in]   output_file     The file to store the matches
 * @param[in]   data            The data to be printed & redirected to output
*/
void 
print_data_to_file(FILE *output_file, data_t *data) {
    fprintf(output_file, "--> footpath_id: %d || address: %s ||", 
        data->foothpath_id, data->address); 
    fprintf(output_file, " clue_sa: %s || asset_type: %s ||", 
        data->clue_sa, data->asset_type);
    fprintf(output_file, " deltaz: %0.2Lf ||", 
        data->deltaz);
    fprintf(output_file, " distance: %0.2Lf ||", 
        data->distance);
    fprintf(output_file, " grade1in: %0.1Lf || mcc_id: %0.0Lf ||", 
        data->grade1in, data->mcc_id);
    fprintf(output_file, " mccid_int: %d || rlmax: %0.2Lf ||", 
        data->mccid_int, data->rlmax);
    fprintf(output_file, " rlmin: %0.2Lf || segside: %s ||", 
        data->rlmin, data->segside);
    fprintf(output_file, " statusid: %d || streetid: %d ||", 
        data->statusid, data->streetid);
    fprintf(output_file, " street_group: %d ||", 
        data->street_group);
    fprintf(output_file, " start_lat: %0.6Lf ||", 
        data->start_lat);
    fprintf(output_file, " start_lon: %0.6Lf ||", 
        data->start_lon);
    fprintf(output_file, " end_lat: %0.6Lf ||", 
        data->end_lat);
    fprintf(output_file, " end_lon: %0.6Lf || \n", 
        data->end_lon);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       GETTER function for 'footpath_id'
 * @param[in]   data    A pointer to data to retrieve it's 'footpath_id' field
 * @return      An INTEGER, data's footpath_id value
*/
int 
get_foothpath_id(data_t *data) {
    return data->foothpath_id;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       GETTER function for retrieving 'grade1in'
 * @param[in]   data    A pointer to data to retrive it's 'grade1in' field
 * @return      A double, data's grade1in value
*/
long double 
get_grade1in(data_t *data) {
    return data->grade1in;
}