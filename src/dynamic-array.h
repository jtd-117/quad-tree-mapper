/**
 * @file    dynamic-array.h
 * @brief   A HEADER file for the implementation of a dynamic array
 * @author  Jude Thaddeau Data
 * @note    https://github.com/jtd-117
*/
/* -------------------------------------------------------------------------- */

// CONSTANT DEFINITIONS:
#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

#define INIT_ARRAY_SIZE 1
#define REALLOC_FACTOR 2
#define REMAINDER_SIZE 3

/* -------------------------------------------------------------------------- */

// LIBRARIES & RELEVANT FILES
#include "data.h"

/* -------------------------------------------------------------------------- */

// STRUCTURE DEFINITIONS:

/**
 * @brief   DYNAMIC ARRAY Structure
 * @param   data            A pointer to the data
 * @param   logical_size    The number of RECORDED items
 * @param   physical_size   The MAXIMUM CAPACITY of the dynamic array
*/
typedef struct array array_t;
struct array {
    data_t      **data;
    int         logical_size;
    int         physical_size;
};

/* -------------------------------------------------------------------------- */

// DYNAMIC ARRAY OPERATIONS
/**
 * @brief   INITIALISES the dynamic array on the heap
 * @return  A pointer to the newly heap allocated array
*/
array_t* array_init(void);

/**
 * @brief       REMOVES the array from the heap
 * @param[in]   array   A pointer to the array to be freed
*/
void array_free(array_t *array);

/**
 * @brief       EXPANDS the array when the logical and physical sizes are EQUAL
 * @param[in]   array A pointer to the array to be expanded
*/
void array_expand(array_t *array);

/**
 * @brief       ADDS new data to the dynamic array thereby:
 *              - Adding to it's logical size
 *              - Increasing it's physical size when necessary
 *              - Keeping the array in SORTED order from LOWEST to HIGHEST
 * @param[out]  array       An array pointer
 * @param[in]   new_data    The new data to be added
*/
void array_sort_append(array_t *array, data_t *new_data);

/**
 * @brief       SEARCHES the array by using the BINARY SEARCH algorithm
 * @param[in]   array           An array pointer to the array to be QUERIED
 * @param[in]   key             The closest value binary search is querying for
 * @return      A long double from array that is closest to grade1in
*/
data_t* array_binary_search(array_t *array, int key);

#endif