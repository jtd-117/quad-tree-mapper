/**
 * @file    cmp.c
 * @brief   A file for COMPARISON functions
 * @author  Jude Thaddeau Data
 * @note    GitHub: https://github.com/jtd-117
*/
/* -------------------------------------------------------------------------- */

// LIBRARIES & RELEVANT HEADER FILES:
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cmp.h"

/* -------------------------------------------------------------------------- */

// NON-PLOYMORPHIC FUNCTIONS:

/**
 * @brief       Compares INTEGERS, checks if v1 is smaller, equal or
 *              larger than v2
 * @param[in]   v1  Variable 1
 * @param[in]   v2  Variable 2
 * @return      One of the following:
 *                  -1 where v1 is LESS THAN v2
 *                   0 where v1 is EQUAL to v2
 *                  +1 where v1 is GREATER THAN v3
*/
int 
cmp_int(int v1, int v2) {
    if (v1 < v2) return LESS;
    if (v1 > v2) return GREATER;
    return EQUAL;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       Compares DOUBLES, checks if v1 is smaller, equal or
 *              larger than v2
 * @param[in]   v1  Variable 1
 * @param[in]   v2  Variable 2
 * @return      One of the following:
 *                  -1 where v1 is LESS THAN v2
 *                   0 where v1 is EQUAL to v2
 *                  +1 where v1 is GREATER THAN v3
*/
int 
cmp_double(double v1, double v2) {
    if (fabs(v1 - v2) < MY_DBL_EPSILON) return EQUAL;
    if (v1 < v2) return LESS;
    return GREATER;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       Compares LONG DOUBLES, checks if v1 is smaller, equal or 
 *              larger than v2
 * @param[in]   v1  Variable 1
 * @param[in]   v2  Variable 2
 * @return      One of the following:
 *                  -1 where v1 is LESS THAN v2
 *                   0 where v1 is EQUAL to v2
 *                  +1 where v1 is GREATER THAN v3
*/
int 
cmp_long_double(long double v1, long double v2) {
    if (fabsl(v1 - v2) < MY_LDBL_EPSILON) return EQUAL;
    if (v1 < v2) return LESS;
    return GREATER;
}