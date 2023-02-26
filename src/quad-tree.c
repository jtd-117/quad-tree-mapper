/**
 * @file    quad-tree.c
 * @brief   A file for the implementation of a quad-tree
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

// LIBRARIES & RELEVANT HEADER FILES:
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "quad-tree.h"

/* -------------------------------------------------------------------------- */

/**
 * @brief       INITIALISES an EMPTY quad-tree NODE
 * @param[out]  tree    The quad-tree which will have a new node
 * @param[in]   bounds  The boundary for which the quad-tree node is defined
 * @return      A POINTER to a heap-allocated quad-tree NODE
*/
qt_node_t* 
qt_node_init(qt_tree_t *tree, rectangle_t bounds) {

    qt_node_t *new_node = (qt_node_t *)malloc(sizeof(qt_node_t));
    assert(new_node != NULL);

    // NOTE: we do not initialise 'point' as new nodes are WHITE (i.e. empty)
    new_node->color = WHITE;
    new_node->bounds = bounds;
    new_node->point = NULL;
    new_node->items = NULL;
    new_node->ne = new_node->nw = new_node->se = new_node->sw = NULL;

    tree->node_count++;
    return new_node;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       INITIALISES a quad-tree INTERFACE
 * @param[in]   bounds  The boundary for which the quad-tree node is defined
 * @return      A POINTER to a heap-allocated quad-tree INTERFACE
*/
qt_tree_t* 
qt_tree_init(rectangle_t bounds) {

    qt_tree_t *new_tree = (qt_tree_t *)malloc(sizeof(qt_tree_t));
    assert(new_tree != NULL);

    new_tree->node_count = 0;
    new_tree->root = qt_node_init(new_tree, bounds);
    return new_tree;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       INSERTS a 2D point & new nodes into the quad-tree
 * @param[out]  tree    The quad-tree to insert new points & nodes into
 * @param[in]   point   The point to insert in the quad-tree
 * @param[in]   data    The DATA associated with the POINT
 * @return      An integer flag where: 0 means UNSUCCESSFUL insertion &
 *              1 means SUCCESSFUL insertion
*/
int 
qt_insert(qt_tree_t *tree, point_2d_t *point, data_t *data) {
    assert(tree != NULL);
    int integer_flag;
    integer_flag = qt_recursive_insert(tree, tree->root, point, data);
    return integer_flag;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       AUXILLARY - RECURSIVELY INSERTS a 2D point into the quad-tree
 * @param[out]  tree    The quad-tree to insert new points & nodes into
 * @param[out]  root    The current root node of subtree
 * @param[in]   point   The point to insert in the quad-tree
 * @param[in]   data    The DATA associated with the POINT
 * @return      An integer flag where: 0 means UNSUCCESSFUL insertion &
 *              1 means SUCCESSFUL insertion
*/
int 
qt_recursive_insert(qt_tree_t *tree, 
    qt_node_t *root, point_2d_t *point, data_t *data) {

    // STEP 1: Check if node is within bounds
    if (! rectangle_contains(root->bounds, *point)) {
        free(point);
        return UNSUCCESSFUL;
    }

    // STEP 2: We have an EMPTY (i.e. WHITE) node 
    if (root->color == WHITE) {
        root->color = BLACK;
        root->point = point;
        root->items = array_init();
        array_sort_append(root->items, data);
        return SUCCESSFUL;
    }

    // STEP 3: We have a node with 1 point (i.e. BLACK)
    if (root->color == BLACK) {

        // CASE 3A: Points are the SAME
        if (equal_point_2d(*root->point, *point)) {
            array_sort_append(root->items, data);
            free(point);
            return SUCCESSFUL;

        // CASE 3B: Points are NOT the same
        } else {
            root->color = GREY;
            qt_subdivide(tree, root);
            qt_repair_internal(root);
        }
    }

    // STEP 4: We have to traverse to the next valid node (i.e. GREY)
    if (root->color == GREY) {

        // STEP 4A: Determine which quadrant to traverse to
        int child_flag = qt_determine_quadrant(root, point);

        // STEP 4B: traverse the the next node
        if (child_flag == NW) {
            return qt_recursive_insert(tree, root->nw, point, data);
        }
        if (child_flag == NE) {
            return qt_recursive_insert(tree, root->ne, point, data);
        }
        if (child_flag == SW) {
            return qt_recursive_insert(tree, root->sw, point, data);
        }
        if (child_flag == SE) {
            return qt_recursive_insert(tree, root->se, point, data);
        }
    }
    exit(EXIT_FAILURE);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       SEARCHES a quad-tree for a xy-point
 * @param[in]   tree    The quad-tree to be queried
 * @param[in]   point   The point to find in the quad-tree
 * @return      A pointer to a qt_node_t containing the point, & NULL otherwise
 * @note        Also PRINTS the path to STDOUT
*/
qt_node_t* 
qt_search(qt_tree_t *tree, point_2d_t *point, char *path) {
    
    qt_node_t *search = tree->root;
    int child_flag;

    // STEP 1: Check if the point lies in the boundary
    if (! rectangle_contains(tree->root->bounds, *point)) {
        return NULL;
    }

    // STEP 2: Keep travsering the quad-tree
    while (search->color == GREY) {
        
        // STEP 3: Need to figure out which quadrant to traverse
        child_flag = qt_determine_quadrant(search, point);

        // STEP 4: Traverse to the appropriate quadrant
        if (child_flag == NW) {
            strcat(path, APPEND_NW);
            search = search->nw;
        }
        if (child_flag == NE) {
            strcat(path, APPEND_NE);
            search = search->ne;
        }
        if (child_flag == SW) {
            strcat(path, APPEND_SW);
            search = search->sw;
        }
        if (child_flag == SE) {
            strcat(path, APPEND_SE);
            search = search->se;
        }
    }

    // STEP 5: Check if the points are equivalent:
    if ((search->color == BLACK) 
        && (equal_point_2d(*search->point, *point))) {
        return search;
    }
    return NULL;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       FINDS all the points within a bounded RANGE
 * @param[in]   tree    The quad-tree to query
 * @param[in]   path    A string of all the directions traversed in the search
 * @param[in]   range   The bounded rectangle that defines a range
 * @return      A pointer of type array_t with the matched query data
*/
array_t* 
qt_range_query(qt_tree_t *tree, char *path, rectangle_t *range) {

    // STEP 1: Initialises the container to store the matches
    assert(tree != NULL);
    array_t *matches = array_init();

    // STEP 2: Recursively search for the points in the quad-tree
    if (tree->root) {
        qt_recursive_range_query(tree->root, path, range, matches);
    }

    // STEP 3: Ensure that the matches has entries
    if (! matches->logical_size) {
        return NULL;
    }
    return matches;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       AUXILLARY - RECURSIVELY finds all the points within a range
 * @param[in]   root    The current subtree's root to find matching points
 * @param[in]   path    A string of all the directions traversed in the search
 * @param[in]   range   The bounded rectangle that defines a range
 * @param[in]   matches A pointer to all the matches
*/
void 
qt_recursive_range_query(qt_node_t *root, char *path, rectangle_t *range, 
    array_t *matches) {

    // STEP 1: Check if this root's boundary intersects with query range
    if (! rectangle_intersect(&root->bounds, range)) {
        return;
    }

    // STEP 2: Check if the points at this current root lie within the range
    if ((root->color == BLACK) && (rectangle_contains(*range, *root->point))) {
        for (int i = 0; i < root->items->logical_size; i++) {

            // NOTE: we do NOT add DUPLICATE values
            if (array_binary_search(matches, 
                get_foothpath_id(root->items->data[i])) == NULL) {
                array_sort_append(matches, root->items->data[i]);
            }
        }
    }

    // STEP 4: Stop here if we have reached a LEAF node
    if (root->color != GREY) {
        return;
    }

    // STEP 5: Otherwise traverse to ONLY BLACK nodes
    if ((root->sw->color != WHITE) 
        && rectangle_intersect(&root->sw->bounds, range)) {
        strcat(path, APPEND_SW);
        qt_recursive_range_query(root->sw, path, range, matches);
    }
    if ((root->nw->color != WHITE) 
        && rectangle_intersect(&root->nw->bounds, range)) {
        strcat(path, APPEND_NW);
        qt_recursive_range_query(root->nw, path, range, matches);
    }
    if ((root->ne->color != WHITE) 
        && rectangle_intersect(&root->ne->bounds, range)) {
        strcat(path, APPEND_NE);
        qt_recursive_range_query(root->ne, path, range, matches);
    }
    if ((root->se->color != WHITE) 
        && rectangle_intersect(&root->se->bounds, range)) {
        strcat(path, APPEND_SE);
        qt_recursive_range_query(root->se, path, range, matches);
    }
    return;
}   

/* -------------------------------------------------------------------------- */

/**
 * @brief       FREES a quad-tree INTERFACE from the heap
 * @param[out]  tree    The quad-tree to free
*/
void 
qt_free(qt_tree_t *tree) {

    // Free ALL the tree's nodes & finally the tree itself
    if (tree->root != NULL) qt_recursive_free(tree, tree->root);
    free(tree);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       AUXILLARY - RECUSIVELY FREES a quad-tree NODE from the heap
 * @param[out]  tree    The quad-tree to free
 * @param[out]  root    The current root of a subtree to free
*/
void 
qt_recursive_free(qt_tree_t *tree, qt_node_t *root) {
    
    // STEP 1: Free any heap-allocated components
    if (root->point != NULL) free(root->point);
    //if (root->items != NULL) array_free(root->items);

    // STEP 2: Traverse to existing child nodes to free them too
    if (root->nw != NULL) {
        qt_recursive_free(tree, root->nw);
        qt_recursive_free(tree, root->ne);
        qt_recursive_free(tree, root->sw);
        qt_recursive_free(tree, root->se);
    }

    // STEP 3: Free the node itself
    free(root);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       AUXILLARY - SUBDIVIDES a quad-tree's node into more children
 * @param[out]  tree    The quad-tree where node subdivision occurs
 * @param[out]  root    The root of a subtree that will have 4 new children
*/
void 
qt_subdivide(qt_tree_t *tree, qt_node_t *root) {

    long double ctr_x = root->bounds.ctr.x;
    long double ctr_y = root->bounds.ctr.y;
    long double hw = root->bounds.hw;
    long double hh = root->bounds.hh;

    // Initialising the NORTH-WEST node
    point_2d_t nw_bl = point_2d_init(ctr_x - hw, ctr_y);
    point_2d_t nw_tr = point_2d_init(ctr_x, ctr_y + hh);
    rectangle_t nw_bounds = rectangle_init(nw_bl, nw_tr);
    root->nw = qt_node_init(tree, nw_bounds);

    // Initialising the NORTH-EAST node
    point_2d_t ne_bl = point_2d_init(ctr_x, ctr_y);
    point_2d_t ne_tr = point_2d_init(ctr_x + hw, ctr_y + hh);
    rectangle_t ne_bounds = rectangle_init(ne_bl, ne_tr);
    root->ne = qt_node_init(tree, ne_bounds);

    // Initialising the SOUTH-WEST node
    point_2d_t sw_bl = point_2d_init(ctr_x - hw, ctr_y - hh);
    point_2d_t sw_tr = point_2d_init(ctr_x, ctr_y);
    rectangle_t sw_bounds = rectangle_init(sw_bl, sw_tr);
    root->sw = qt_node_init(tree, sw_bounds);

    // Initialising the SOUTH-EAST node
    point_2d_t se_bl = point_2d_init(ctr_x, ctr_y - hh);
    point_2d_t se_tr = point_2d_init(ctr_x + hw, ctr_y);
    rectangle_t se_bounds = rectangle_init(se_bl, se_tr);
    root->se = qt_node_init(tree, se_bounds);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       AUXILLARY - DETERMINES which quadrant a point belongs to
 * @param[in]   root    The current node at the traversal
 * @param[in]   point   The point we try to determine where it belongs
 * @return      An INTEGER FLAG where: 0 indicates NW node, 1 indicates NE
 *              node, 2 indicates SW node & 3 indicates the SE node
*/
int 
qt_determine_quadrant(qt_node_t *root, point_2d_t *point) {
    
    // STEP 1: Need to ensure child nodes exist
    assert((root->nw) && (root->ne) && (root->sw) && (root->se));

    // STEP 2: Test the point with each subchild
    if (rectangle_contains(root->nw->bounds, *point)) return NW;
    if (rectangle_contains(root->ne->bounds, *point)) return NE;
    if (rectangle_contains(root->sw->bounds, *point)) return SW;
    if (rectangle_contains(root->se->bounds, *point)) return SE;

    // EXCEPTION: does not belong in any bounds
    exit(EXIT_FAILURE);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       AUXILLARY - REPAIRS a grey node by TRANSFERRING it's data into
 *              one of it's recently SUBDIVIDED child nodes.
 * @param[out]  root    The GREY root node to repair
*/
void 
qt_repair_internal(qt_node_t *root) {

    // STEP 1: Ensure the root is an INTERNAL (i.e. GREY) node
    assert(root->color == GREY);

    // STEP 2: Determine the new quadrant the grey nodes's point belongs to
    int child_flag = qt_determine_quadrant(root, root->point);

    // STEP 3: Assign the node pointer to the appropriate child quadrant
    qt_node_t *child = NULL;
    if (child_flag == NW) child = root->nw;
    if (child_flag == NE) child = root->ne;
    if (child_flag == SW) child = root->sw;
    if (child_flag == SE) child = root->se;

    // STEP 4: TRANSFER the points accordingly
    child->color = BLACK;
    child->point = root->point;
    child->items = root->items;

    // STEP 5: Assign NULL values to grey node
    root->point = NULL;
    root->items = NULL;
}