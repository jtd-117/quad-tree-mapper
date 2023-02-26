/**
 * @file    sll.c
 * @brief   A file for the implementation for a singly linked-list (SLL)
 * @author  Jude Thaddeau Data
 * @note    GitHub: https://github.com/jtd-117
*/
/* -------------------------------------------------------------------------- */

// LIBRARIES & RELEVANT HEADER FILES:
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sll.h"

/* -------------------------------------------------------------------------- */

/**
 * @brief       CREATES a dictionary linked list (SLL)
 * @return      A pointer to the address of the new SLL 
*/
sll_t* 
sll_init(void) {

    // STEP 1: Create space for the SLL on the heap
    sll_t *new_sll;
    new_sll = (sll_t *)malloc(sizeof(sll_t));
    assert(new_sll != NULL);

    // STEP 2: Initialise paramerters & return list address
    new_sll->head = new_sll->tail = (sll_node_t *)NULL;
    return new_sll;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       DELETES a SLL by freeing the nodes & it's associated data
 * @param[in]   sll     The DSLLL to be deleted
*/
void 
sll_free(sll_t *sll) {

    // STEP 1: Temporary nodes to traverse the SLL
    sll_node_t *current_node = sll->head;
    sll_node_t *next_node;

    // STEP 2: Traverse the SLL from the start & free contents from the heap
    while (current_node != NULL) {

        next_node = current_node->next;

        if (current_node->data != NULL) {
            free_data(current_node->data);
        }

        free(current_node);
        current_node = next_node;
    }
    free(sll);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       CHECKS if a SLL has any nodes
 * @param[in]   sll     The SLL whose nodes are to be checked
 * @return      0 if SLL has ZERO node
 *              1 if SLL has at least ONE node
*/
int 
sll_is_empty(sll_t *sll) {
    assert(sll != NULL);
    return ((sll->head == NULL) && (sll->tail == NULL));
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       APPENDS a new node at the END of the SLL
 * @param[out]  sll         The SLL to be appended a new node
 * @param[in]   new_data    new_data    The address of the new data to be 
 *                          inserted as part of the SLL
 * @return      A pointer to the SLL with a newly added TAIL node
*/
sll_t* 
sll_insert_tail(sll_t *sll, data_t *new_data) {

    // STEP 1: Create a new node & allocate data
    sll_node_t *new_tail;
    new_tail = (sll_node_t *)malloc(sizeof(sll_node_t));
    assert((sll != NULL) && (new_tail != NULL));
    new_tail->data = new_data;
    new_tail->next = (sll_node_t *)NULL;

    // CASE 1: 1st insertion into the SLL
    if (sll->tail == NULL) {
        sll->head = sll->tail = new_tail;

    // CASE 2: NOT the 1st insertion into the SLL
    } else {
        sll->tail->next = new_tail;
        sll->tail = new_tail;
    }
    return sll;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       DELETES the LAST node from the SLLSLL
 * @param[out]  sll     The SLL whose LAST node is to be deleted
 * @return      The new TAIL node of the SLL
*/
sll_t* 
sll_delete_tail(sll_t *sll) {
    
    // STEP 1: INITIALISE the variables
    sll_node_t *old_tail, *tmp;
    assert((sll != NULL) && (sll->tail != NULL));
    tmp = sll->head;
    old_tail = sll->tail;

    // STEP 2: DELETE the data in the TAIL node:
    if (sll->tail->data != NULL) {
        free_data(sll->tail->data);
    }
    
    // EXCEPTION: Only ONE node remains
    if (tmp->next == NULL) {
        sll->head = sll->tail = (sll_node_t *)NULL;

    } else {
        
        // Iterate to the 2nd last node
        while (tmp->next != old_tail) {
            tmp = tmp->next;
        }
        tmp->next = (sll_node_t *)NULL;
        sll->tail = tmp;
    }
    free(old_tail);
    return sll;
}