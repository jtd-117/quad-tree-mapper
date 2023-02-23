/**
 * @file    dynamic-array.h
 * @brief   A file for the implementation of a dynamic array
 * @author  Jude Thaddeau Data
 * @note    GitHub: https://github.com/jtd-117
*/
/* -------------------------------------------------------------------------- */

// LIBRARIES & RELEVANT HEADER FILES:
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "dynamic-array.h"

/* -------------------------------------------------------------------------- */

/**
 * @brief   INITIALISES the dynamic array on the heap
 * @return  A pointer to the newly heap allocated array
*/
array_t* 
array_init(void) {

    // STEP 1: Allocate space on the heap for the STRUCTURE itself
    array_t *new_array = malloc(sizeof(array_t));
    assert(new_array);

    // STEP 2: Allocate space on the heap for the DYNAMIC ARRAY
    new_array->data = malloc(sizeof(data_t *) * INIT_ARRAY_SIZE);
    assert(new_array->data);

    // STEP 3: Initialise the logical & physical space
    new_array->physical_size = INIT_ARRAY_SIZE;
    new_array->logical_size = 0;
    return new_array;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       REMOVES the array from the heap
 * @param[in]   array   A pointer to the array to be freed
*/
void 
array_free(array_t *array) {
        
    // Free the data & the array itself
    free(array->data);
    free(array);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       EXPANDS the array when the logical and physical sizes are EQUAL
 * @param[in]   array A pointer to the array to be expanded
*/
void 
array_expand(array_t *array) {

    // Array is now FULL: need to expand
    if (array->logical_size == array->physical_size) {
        array->physical_size *= REALLOC_FACTOR;
        array->data = 
            realloc(array->data, array->physical_size 
                * REALLOC_FACTOR * sizeof(data_t *));
        assert(array->data);
    }
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       ADDS new data to the dynamic array thereby:
 *              - Adding to it's logical size
 *              - Increasing it's physical size when necessary
 *              - Keeping the array in SORTED order from LOWEST to HIGHEST
 * @param[out]  array       An array pointer
 * @param[in]   new_data    The new data to be added
 * @note        Comparisons are based off the data->grade1in parameter
*/
void 
array_sort_append(array_t *array, data_t *new_data) {

    // STEP 1: Check & expand if the array needs to be expanded
    array_expand(array);

    // STEP 2: Need to check if the array needs to be sorted first
    int index;

    // CASE 1 - The array is NOT empty & sorted
    if (array->logical_size > 0) {
        int i;

        // Start from the end & traverse backwards
        for (i = array->logical_size - 1; i >= 0 && 
            cmp_int(get_foothpath_id(new_data), get_foothpath_id(array->data[i])) 
            == LESS; i--) {
            array->data[i + 1] = array->data[i];
        }
        index = i + 1;

    // CASE 2 - The array is EMPTY
    } else {
        index = array->logical_size;
    }

    // STEP 3: Assign the new data & updated the physical size
    array->data[index] = new_data;
    array->logical_size++;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       SEARCHES the array by using the BINARY SEARCH algorithm
 * @param[in]   array           An array pointer to the array to be QUERIED
 * @param[in]   key             The closest value binary search is querying for
 * @return      A long double from array that is closest to grade1in
*/
data_t* 
array_binary_search(array_t *array, int key) {

    // STEP 1: Initialise variables
    int comps = 0, lo = 0, mid, hi = array->logical_size - 1;
    data_t **data = array->data;
    data_t *result = NULL;

    // STEP 2: Keep traversing the array into the LEFT or RIGHT half
    while (lo <= hi) {
        mid = (lo + hi)/2;
		comps++;
        result = data[mid];
		int cmp = cmp_int(key, get_foothpath_id(result));

        // CASE 1: Found an exact match (return early)
		if (cmp == 0) return result;

        // CASE 2: Move to the LEFT side of the array
		if (cmp < 0){ 
			hi = mid - 1;

        // CASE 3: Move to the RIGHT side of the array
		} else {
			lo = mid + 1;
		}
    }
    return NULL;
}