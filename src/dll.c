/**
 * @file    dll.c
 * @brief   A file for the implementation for a doubly linked-list (DLL)
 * @author  Jude Thaddeau Data
 * @note    GitHub: https://github.com/jtd-117
*/
/* -------------------------------------------------------------------------- */

// LIBRARIES & RELEVANT HEADER FILES:
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dll.h"

/* -------------------------------------------------------------------------- */

/**
 * @brief       CREATES a dictionary linked list (DLL)
 * @return      A pointer to the address of the new DLL 
*/
dll_t* 
dll_init(void) {

    // STEP 1: Create space for the DLL on the heap
    dll_t *new_dll;
    new_dll = (dll_t *)malloc(sizeof(dll_t));
    assert(new_dll != NULL);

    // STEP 2: Initialise paramerters & return list address
    new_dll->head = new_dll->tail = (dll_node_t *)NULL;
    return new_dll;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       DELETES a DLL by freeing the nodes & it's associated data
 * @param[in]   dll     The DLL to be deleted
*/
void 
dll_free(dll_t *dll) {

    // STEP 1: Temporary nodes to traverse the DLL
    dll_node_t *current_node = dll->head;
    dll_node_t *next_node;

    // STEP 2: Traverse the DLL from the start & free contents from the heap
    while (current_node != NULL) {

        next_node = current_node->next;

        if (current_node->data != NULL) {
            free_data(current_node->data);
        }

        free(current_node);
        current_node = next_node;
    }
    free(dll);
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       CHECKS if a DLL has any nodes
 * @param[in]   dll     The DLL whose nodes are to be checked
 * @return      0 if DLL has ZERO node
 *              1 if DLL has at least ONE node
*/
int 
dll_is_empty(dll_t *dll) {
    assert(dll != NULL);
    return ((dll->head == NULL) && (dll->tail == NULL));
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       APPENDS a new node at the END of the DLL
 * @param[out]  dll         The DLL to be appended a new node
 * @param[in]   new_data    new_data    The address of the new data to be 
 *                          inserted as part of the SLL
 * @return      A pointer to the DLL with a newly added TAIL node
*/
dll_t* 
dll_insert_tail(dll_t *dll, data_t *new_data) {

    // STEP 1: Create a new node & allocate data
    dll_node_t *new_tail;
    new_tail = (dll_node_t *)malloc(sizeof(dll_node_t));
    assert((dll != NULL) && (new_tail != NULL));
    new_tail->data = new_data;
    new_tail->next = (dll_node_t *)NULL;

    // CASE 1: 1st insertion into the DLL
    if (dll->tail == NULL) {
        dll->head = dll->tail = new_tail;

    // CASE 2: NOT the 1st insertion into the DLL
    } else {
        dll->tail->next = new_tail;
        dll->tail = new_tail;
    }
    return dll;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief       DELETES the LAST node from the DLL
 * @param[out]  dll     The DLL whose LAST node is to be deleted
 * @return      The new TAIL node of the DLL
*/
dll_t* 
dll_delete_tail(dll_t *dll) {
    
    // STEP 1: INITIALISE the variables
    dll_node_t *old_tail, *tmp;
    assert((dll != NULL) && (dll->tail != NULL));
    tmp = dll->head;
    old_tail = dll->tail;

    // STEP 2: DELETE the data in the TAIL node:
    if (dll->tail->data != NULL) {
        free_data(dll->tail->data);
    }
    
    // EXCEPTION: Only ONE node remains
    if (tmp->next == NULL) {
        dll->head = dll->tail = (dll_node_t *)NULL;

    } else {
        
        // Iterate to the 2nd last node
        while (tmp->next != old_tail) {
            tmp = tmp->next;
        }
        tmp->next = (dll_node_t *)NULL;
        dll->tail = tmp;
    }
    free(old_tail);
    return dll;
}