/**
 * @file    quad-tree.c
 * @brief   A HEADER file for the implementation of a quad-tree
 * @author  Jude Thaddeau Data
 * @note    GitHub: https://github.com/jtd-117
 * 
 *          ACKNOWLEDGEMENT
 *          This code is based off the quad-tree implementation provided by
 *          https://en.wikipedia.org/wiki/Quadtree#Pseudocode
 * 
 *          Also where possible, a C quad-tree implementation from
 *          https://github.com/kutani/quadtree/blob/master/quadtree.c is 
 *          used to model some functions 
*/
/* -------------------------------------------------------------------------- */

// CONSTANT DEFINITIONS:
#ifndef _QUAD_TREE_H_
#define _QUAD_TREE_H_

#define WHITE 0     // Indicates that a quad-tree NODE has ZERO points
#define BLACK 1     // Indicates that a quad-tree NODE has ONE point
#define GREY 2      // Indicates that a quad-tree NODE is INTERNAL

#define UNSUCCESSFUL 0  // Indicates function terminated INCORRECTLY
#define SUCCESSFUL 1    // Indicates function terminated CORRECTLY

#define NW 0    // Flag to traverse to NORTH-WEST child node
#define NE 1    // Flag to traverse to NORTH-EAST child node
#define SW 2    // Flag to traverse to SOUTH-WEST child node
#define SE 3    // Flag to traverse to SOUTH-EAST child node

#define MAX_PATH_LENGTH 100000  // Maximum number of characters to add to path
#define APPEND_NW " NW"         // Adds NORTH-WEST string to the path
#define APPEND_NE " NE"         // Adds NORTH-EAST string to the path
#define APPEND_SW " SW"         // Adds SOUTH-WEST string to the path
#define APPEND_SE " SE"         // Adds SOUTH-EAST string to the path

/* -------------------------------------------------------------------------- */

// RELEVANT HEADER FILES:
#include "data.h"
#include "coordinates.h"
#include "dynamic-array.h"

/* -------------------------------------------------------------------------- */

// STRUCTURE DEFINITIONS:

/**
 * @brief   A quad-tree NODE
 * @param   color       Is either WHITE, BLACK or GREY
 * @param   bounds      The boundary for which a point is defined
 * @param   point       A point that is bound by the quad-tree node's bounds
 * @param   items       DATA associated with the point
 * @param   nw          NORTH-WEST child node
 * @param   ne          NORTH-EAST child node
 * @param   sw          SOUTH-WEST child node
 * @param   se          SOUTH-EAST child
*/
typedef struct qt_node qt_node_t;
struct qt_node {
    int             color;
    rectangle_t     bounds;
    point_2d_t      *point;
    array_t         *items;
    qt_node_t       *nw;
    qt_node_t       *ne;
    qt_node_t       *sw;
    qt_node_t       *se;
};

/**
 * @brief   A quad-tree INTERFACE
 * @param   root        The 1st node in the quad-tree
 * @param   node_count  The NUMBER of nodes stored in the quad-tree   
*/
typedef struct qt_tree qt_tree_t;
struct qt_tree {
    qt_node_t       *root;
    unsigned int    node_count;
};

/* -------------------------------------------------------------------------- */

// QUAD-TREE OPERATIONS:

/**
 * @brief       INITIALISES an EMPTY quad-tree NODE
 * @param[out]   tree    The quad-tree which will have a new node
 * @param[in]   bounds  The boundary for which the quad-tree node is defined
 * @return      A POINTER to a heap-allocated quad-tree NODE
*/
qt_node_t* qt_node_init(qt_tree_t *tree, rectangle_t bounds);

/**
 * @brief       INITIALISES a quad-tree INTERFACE
 * @param[in]   bounds  The boundary for which the quad-tree node is defined
 * @return      A POINTER to a heap-allocated quad-tree INTERFACE
*/
qt_tree_t* qt_tree_init(rectangle_t bounds);

/**
 * @brief       INSERTS a 2D point & new nodes into the quad-tree
 * @param[out]  tree    The quad-tree to insert new points & nodes into
 * @param[in]   point   The point to insert in the quad-tree
 * @param[in]   data    The DATA associated with the POINT
 * @return      An integer flag where: 0 means UNSUCCESSFUL insertion &
 *              1 means SUCCESSFUL insertion
*/
int qt_insert(qt_tree_t *tree, point_2d_t *point, data_t *data);

/**
 * @brief       AUXILLARY - RECURSIVELY INSERTS a 2D point into the quad-tree
 * @param[out]  tree    The quad-tree to insert new points & nodes into
 * @param[out]  root    The current root node of subtree
 * @param[in]   point   The point to insert in the quad-tree
 * @param[in]   data    The DATA associated with the POINT
 * @return      An integer flag where: 0 means UNSUCCESSFUL insertion &
 *              1 means SUCCESSFUL insertion
*/
int qt_recursive_insert(qt_tree_t *tree, qt_node_t *root, 
    point_2d_t *point, data_t *data);

/**
 * @brief       FINDS all the points within a bounded RANGE
 * @param[in]   tree    The quad-tree to query
 * @param[in]   path    A string of all the directions traversed in the search
 * @param[in]   range   The bounded rectangle that defines a range
 * @return      A pointer of type array_t with the matched query data
*/
array_t* qt_range_query(qt_tree_t *tree, char *path, rectangle_t *range);

/**
 * @brief       AUXILLARY - RECURSIVELY finds all the points within a range
 * @param[in]   root    The current subtree's root to find matching points
 * @param[in]   path    A string of all the directions traversed in the search
 * @param[in]   range   The bounded rectangle that defines a range
 * @param[in]   matches A pointer to all the matches
*/
void qt_recursive_range_query(qt_node_t *root, char *path, rectangle_t *range, array_t *matches);

/**
 * @brief       SEARCHES a quad-tree for a xy-point
 * @param[in]   tree    The quad-tree to be queried
 * @param[in]   point   The point to find in the quad-tree
 * @param[out]  path    The path of the point
 * @return      A pointer to a qt_node_t containing the point, & NULL otherwise
 * @note        Also PRINTS the path to STDOUT
*/
qt_node_t* qt_search(qt_tree_t *tree, point_2d_t *point, char *path);

/**
 * @brief       FREES a quad-tree INTERFACE from the heap
 * @param[out]  tree    The quad-tree to free
*/
void qt_free(qt_tree_t *tree);

/**
 * @brief       AUXILLARY - RECUSIVELY FREES a quad-tree NODE from the heap
 * @param[out]  tree    The quad-tree to free
 * @param[out]  root    The current root of a subtree to free
*/
void qt_recursive_free(qt_tree_t *tree, qt_node_t *root);

#endif