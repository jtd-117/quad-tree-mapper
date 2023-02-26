/**
 * @file    dll.h
 * @brief   A HEADER file for the implementation for a doubly linked-list (DLL)
 * @author  Jude Thaddeau Data
 * @note    GitHub: https://github.com/jtd-117
*/
/* -------------------------------------------------------------------------- */

// CONSTANT DEFINITIONS:
#ifndef _DLL_H_
#define _DLL_H_

/* -------------------------------------------------------------------------- */

// LIBRARIES & RELEVANT FILES
#include "data.h"

/* -------------------------------------------------------------------------- */

// STRUCTURE DEFINITIONS:

/**
 * @brief   A node when linked with others of the same type for a DLL
 * @param   data    Pointer to DATA associated with the DLL node
 * @param   next    Pointer to the next node in the DLL
*/
typedef struct dll_node dll_node_t;
struct dll_node {
    data_t          *data;
    dll_node_t      *next;
};

/**
 * @brief   A mechanism to interace with the DLL
 * @param   head    The node at the START of the DLL
 * @param   tail    The node at the END of the DLL
*/
typedef struct dll dll_t;
struct dll {
    dll_node_t     *head;
    dll_node_t     *tail;
};

/* -------------------------------------------------------------------------- */

// DOUBLY LINKED-LIST (DLL) OPERATIONS:

/**
 * @brief       CREATES a doubly linked list (DLL)
 * @param[in]   cmp     The comparison function for comparing dll keys
 * @return      A pointer to the address of the new DLL 
*/
dll_t *dll_init(void);

/**
 * @brief       DELETES a DLL by removing itself & it's nodes from the heap
 * @param[in]   dll     The DLL to be deleted
*/
void dll_free(dll_t *dll);

/**
 * @brief       CHECKS if a DLL has any entries
 * @param[in]   dll     The DLL whose entries are to be checked
 * @return      0 if DLL has ZERO entries
 *              1 if DLL has at least ONE node
*/
int dll_is_empty(dll_t *dll);

/**
 * @brief       APPENDS a new node at the END of the DLL
 * @param[out]  dll         The DLL to be appended a new node
 * @param[in]   new_data    new_data    The address of the new data to be 
 *                          inserted as part of the DLL
 * @return      A pointer to the DLL with a newly added TAIL node
*/
dll_t *dll_insert_tail(dll_t *dll, data_t *new_data);

/**
 * @brief       DELETES the LAST node from the DLL
 * @param[out]  dll     The DLL whose LAST node is to be deleted
 * @return      The new TAIL node of the DLL
*/
dll_t *dll_delete_tail(dll_t *dll);

#endif