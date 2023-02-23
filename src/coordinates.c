/**
 * @file    coordinates.c
 * @brief   A file for implementing code for cartesian coordinates
 * @author  Jude Thaddeau Data
 * @note    GitHub: https://github.com/jtd-117
*/
/* -------------------------------------------------------------------------- */

// LIBRARIES & RELEVANT HEADER FILES:
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "coordinates.h"

/* -------------------------------------------------------------------------- */

/**
 * @brief       INITIALISES a 2D point
 * @param[in]   x    The HORIZONTAL component: x-coordinate
 * @param[in]   y    The VERTICAL component: y-coordinate
 * @return      A new point_2d_t
*/
point_2d_t 
point_2d_init(long double x, long double y) {

    point_2d_t new_point;
    new_point.x = x;
    new_point.y = y;
    return new_point;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       INTIALISES a 2D point on the HEAP
 * @param[in]   x    The HORIZONTAL component: x-coordinate
 * @param[in]   y    The VERTICAL component: y-coordinate
 * @return      A pointer to a new point_2d_t 
*/
point_2d_t* 
point_2d_malloc(long double x, long double y) {

    point_2d_t *new_point = (point_2d_t *)malloc(sizeof(point_2d_t));
    assert(new_point);

    new_point->x = x;
    new_point->y = y;
    return new_point;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       CHECKS if TWO points are EQUAL
 * @param[in]   point1  1st point
 * @param[in]   point2  2nd point
 * @return      An INTEGER FLAG to check if the points are equal: 0 if points
 *              are UNEQUAL & 1 if points are equal
*/
int 
equal_point_2d(point_2d_t point1, point_2d_t point2) {
    
    return ((cmp_long_double(point1.x, point2.x) == EQUAL) 
        && (cmp_long_double(point1.y, point2.y) == EQUAL));
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       INITIALISES a Rectangle
 * @param[in]   bl      BOTTOM-LEFT coordinate
 * @param[in]   tr      TOP-RIGHT coordinate
 * @return      A new rectangle_t
*/
rectangle_t rectangle_init(point_2d_t bl, point_2d_t tr) {

    rectangle_t new_rectangle;
    new_rectangle.bl = bl;
    new_rectangle.tr = tr;
    new_rectangle.hw = fabsl(tr.x - bl.x)/2.0;
    new_rectangle.hh = fabsl(tr.y - bl.y)/2.0;
    new_rectangle.ctr.x = tr.x - new_rectangle.hw;
    new_rectangle.ctr.y = tr.y - new_rectangle.hh;
    return new_rectangle;
}

/* -------------------------------------------------------------------------- */

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
int 
rectangle_contains(rectangle_t bounds, point_2d_t point) {

    return (((point.x > bounds.ctr.x - bounds.hw) 
        && (point.x <= bounds.ctr.x + bounds.hw)) 
        && ((point.y >= bounds.ctr.y - bounds.hh) 
        && (point.y < bounds.ctr.y + bounds.hh)));
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       CHECKS if two rectangles INTERSECT
 * @param[in]   r1  The 1st rectangle
 * @param[in]   r2  The 2nd rectangle
 * @return      An INTEGER flag where: 0 indicates that the rectangles DO NOT
 *              intersect & 1 indicates that the rectangles DO intersect
 * 
 *              ACKNOWLEDGEMENT
 *              See https://github.com/kutani/quadtree/blob/master/aabb.c on
 *              lines 29-33
*/
int 
rectangle_intersect(rectangle_t *r1, rectangle_t *r2) {

    return ((fabsl(r1->ctr.x - r2->ctr.x) <= 
        (r1->hw + r2->hw)) && ((fabsl(r1->ctr.y - r2->ctr.y)) <= 
        (r1->hh + r2->hh)));
}