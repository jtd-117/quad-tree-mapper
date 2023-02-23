/**
 * @file    data.h
 * @brief   A HEADER file for the structure of the structure implementation
 *          for the Melbourne CSV data
 * @author  Jude Thaddeau Data
 * @note    GitHub: https://github.com/jtd-117
*/
/* -------------------------------------------------------------------------- */

// CONSTANT DEFINITIONS:
#ifndef _DATA_H_
#define _DATA_H_

#define MAX_STR_LEN 128     // Maximum length of a CSV field

#define COMMA ','           // Delimiter for a COMMA
#define DOUBLE_QUOTE '"'    // Delimiter for a DOUBLE QUOTE

#define EQUAL 0             // Variable 1 & 2 are equal
#define GREATER 1           // Variable 1 is GREATER than variable 2
#define LESS -1             // Variable 1 is LESS than variable 2

/* -------------------------------------------------------------------------- */

// LIBRARIES & RELEVANT FILES
#include "cmp.h"

/* -------------------------------------------------------------------------- */

// STRUCTURE DEFINITIONS:

/**
 * @brief   Data entries (in-order) from the Melbourne CSV file
 * @note    - 'char' can be EMPTY strings
 *          - 'char' can be no more than 128 characters
 *          - 'int' are always SPECIFIED & PRESENT
*/
typedef struct data data_t;
struct data {
    int             foothpath_id;
    char*           address;
    char*           clue_sa;
    char*           asset_type;
    long double     deltaz;
    long double     distance;
    long double     grade1in;
    long double     mcc_id;
    int             mccid_int;
    long double     rlmax;
    long double     rlmin;
    char*           segside;
    int             statusid;
    int             streetid;
    int             street_group;
    long double     start_lat;
    long double     start_lon;
    long double     end_lat;
    long double     end_lon;
};

/* -------------------------------------------------------------------------- */

// FUNCTION PROTOTYPES:

/**
 * @brief       UTILITY - SKIPS a line from an input file
 * @param[in]   file    The file whose line is to be SKIPPED
 * @note        ACKNOWLEDGEMENT
 *              Code used from COMP20003 Ed Discussion: W3.7's 
 *              data.c file
*/
void file_skip_line(FILE *file);

/**
 * @brief       UTILITY - Initialises the data structure
 * @return      A pointer to an initialised data in the heap
*/
data_t* data_init(void);

/**
 * @brief       UTILITY - returns a field from a csv line
 * @param[in]   input_file  The CSV file with cursor at a string
 * @param[out]  dest        The pointer where the string to be saved
 * @return      A pointer to a string from a CSV field
 * @note        ASSUMES the next field is a string
*/
char* get_csv_string(FILE *input_file, char *dest);

/**
 * @brief       UTILITY - Reads a single CSV line
 * @param[in]   file        The input CSV file to be read
 * @param[out]  new_data    New data to be inserted
 * @return      A pointer to the heap allocated data
*/
data_t* read_line_data(FILE *file, data_t *new_data);

/**
 * @brief       DELETES data_t from the heap's deallocated memory
 * @param[in]   data    The data to freed from the heap
*/
void free_data(data_t *data);

/**
 * @brief       PRINTS all fields in the structure data_t
 * @param[in]   data    The structure whose components are to be printed
*/
void print_data(data_t *data);

/**
 * @brief       UTILITY - Prints data that share (i.e. match) the same key
 * @param[in]   output_file     The file to store the matches
 * @param[in]   data            The data to be printed & redirected to output
*/
void print_data_to_file(FILE *output_file, data_t *data);


/**
 * @brief       COMPARES double variables by comparing which one is LARGER
 * @param[in]   d1  The 1st double variable
 * @param[in]   d2  The 2nd double variable
 * @return      Returns:
 *              0   if d1->grade1in & d2->grade1in are EQUAL
 *              1   if d1->grade1in is GREATER than d2->grade1in
 *             -1   if d1->grade1in is LESS than d2->grade1in
*/
int cmp_grade1in(long double d1, long double d2);

/**
 * @brief       GETTER function for 'footpath_id'
 * @param[in]   data    A pointer to data to retrieve it's 'footpath_id' field
 * @return      An INTEGER, data's footpath_id value
*/
int get_foothpath_id(data_t *data);


/**
 * @brief       GETTER function for 'grade1in'
 * @param[in]   data    A pointer to data to retrive it's 'grade1in' field
 * @return      A DOUBLE, data's grade1in value
*/
long double get_grade1in(data_t *data);

#endif