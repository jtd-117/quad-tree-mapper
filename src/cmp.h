/**
 * @file    cmp.c
 * @brief   A HEADER file for COMPARISON functions
 * @author  Jude Thaddeau Data
 * @note    GitHub: https://github.com/jtd-117
*/
/* -------------------------------------------------------------------------- */

// CONSTANT DEFINITIONS:
#ifndef _CMP_H_
#define _CMP_H_

#define EQUAL 0             // Variable 1 & 2 are equal
#define GREATER 1           // Variable 1 is GREATER than variable 2
#define LESS -1             // Variable 1 is LESS than variable 2

#define MY_DBL_EPSILON  0.000001            // Custom EPSILON for doubles
#define MY_LDBL_EPSILON 0.000000000001      // Custom EPSILON for long doubles

/* -------------------------------------------------------------------------- */

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
int cmp_int(int v1, int v2);

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
int cmp_double(double v1, double v2);

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
int cmp_long_double(long double v1, long double v2);

#endif