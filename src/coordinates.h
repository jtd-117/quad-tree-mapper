/**
 * @file    coordinates.h
 * @brief   A HEADER file for implementing code for cartesian coordinates
 * @author  Jude Thaddeau Data
 * @note    GitHub: https://github.com/jtd-117
*/
/* -------------------------------------------------------------------------- */

// CONSTANT DEFINITIONS:
#ifndef _CARTESIAN_COORDINATES_H_
#define _CARTESIAN_COORDINATES_H_

/* -------------------------------------------------------------------------- */

// RELEVANT HEADER FILES:
#include "cmp.h"

/* -------------------------------------------------------------------------- */

// STRUCTURE DEFINITIONS:

/**
 * @brief   A 2D point on the xy plane
 * @param   x   The HORIZONTAL component
 * @param   y   The VERTICAL component
*/
typedef struct point_2d point_2d_t;
struct point_2d {
    long double     x;
    long double     y;
};

/**
 * @brief   Defines the dimensions & coordinates of a RECTANGLE
 * @param   bl      BOTTOM-LEFT coordinates of the rectangle
 * @param   tr      TOP-RIGHT coordinates of the rectangle
 * @param   ctr     CENTER coordinates of the rectangle
 * @param   hw      HALF-WIDTH of the rectangle
 * @param   hh      HALF-HEIGHT of the rectangle
*/
typedef struct rectangle rectangle_t;
struct rectangle {
    point_2d_t      bl;
    point_2d_t      tr;
    point_2d_t      ctr;
    long double     hw;
    long double     hh;
};

/* -------------------------------------------------------------------------- */

// FUNCTION PROTOTYPES:

/**
 * @brief       INITIALISES a 2D point
 * @param[in]   x    The HORIZONTAL component: x-coordinate
 * @param[in]   y    The VERTICAL component: y-coordinate
 * @return      A new point_2d_t
*/
point_2d_t point_2d_init(long double x, long double y);

/**
 * @brief       INTIALISES a 2D point on the HEAP
 * @param[in]   x    The HORIZONTAL component: x-coordinate
 * @param[in]   y    The VERTICAL component: y-coordinate
 * @return      A pointer to a new point_2d_t 
*/
point_2d_t* point_2d_malloc(long double x, long double y);

/**
 * @brief       CHECKS if TWO points are EQUAL
 * @param[in]   point1  1st point
 * @param[in]   point2  2nd point
 * @return      An INTEGER FLAG to check if the points are equal: 0 if points
 *              are UNEQUAL & 1 if points are equal
*/
int equal_point_2d(point_2d_t point1, point_2d_t point2);

/**
 * @brief       INITIALISES a Rectangle
 * @param[in]   bl      BOTTOM-LEFT coordinate
 * @param[in]   tr      TOP-RIGHT coordinate
 * @return      A new rectangle_t
*/
rectangle_t rectangle_init(point_2d_t bl, point_2d_t tr);

/**
 * @brief       CHECKS whether a xy point is WITHIN a rectangle
 * @param[in]   bounds      The rectangle bounds
 * @param[in]   point       The point to see if it is within bounds
 * @return      An INTEGER flag where: 0 indicates the point is NOT within
 *              bounds & 1 denotes the point is WITHIN bounds
 * 
 *              ACKNOWLEDGMENT
 *              See https://github.com/kutani/quadtree/blob/master/aabb.c on
 *              lines 21-27
*/
int rectangle_contains(rectangle_t bounds, point_2d_t point);

/**
 * @brief       CHECKS if two rectangles INTERSECT
 * @param[in]   r1  A pointer to the 1st rectangle
 * @param[in]   r2  A pointer to the 2nd rectangle
 * @return      An INTEGER flag where: 0 indicates that the rectangles DO NOT
 *              intersect & 1 indicates that the rectangles DO intersect
 * 
 *              ACKNOWLEDGEMENT
 *              See https://github.com/kutani/quadtree/blob/master/aabb.c on
 *              lines 29-33
*/
int rectangle_intersect(rectangle_t *r1, rectangle_t *r2);

#endif