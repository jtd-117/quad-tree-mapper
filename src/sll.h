/**
 * @file    sll.h
 * @brief   A HEADER file for the implementation for a doubly linked-list (SLL)
 * @author  Jude Thaddeau Data
 * @note    GitHub: https://github.com/jtd-117
*/
/* -------------------------------------------------------------------------- */

// CONSTANT DEFINITIONS:
#ifndef _SLL_H_
#define _SLL_H_

/* -------------------------------------------------------------------------- */

// LIBRARIES & RELEVANT FILES
#include "data.h"

/* -------------------------------------------------------------------------- */

// STRUCTURE DEFINITIONS:

/**
 * @brief   A node when linked with others of the same type for a SLL
 * @param   data    Pointer to DATA associated with the SLL node
 * @param   next    Pointer to the next node in the SLL
*/
typedef struct sll_node sll_node_t;
struct sll_node {
    data_t          *data;
    sll_node_t      *next;
};

/**
 * @brief   A mechanism to interace with the SLL
 * @param   head    The node at the START of the SLL
 * @param   tail    The node at the END of the SLL
*/
typedef struct sll sll_t;
struct sll {
    sll_node_t     *head;
    sll_node_t     *tail;
};

/* -------------------------------------------------------------------------- */

// DOUBLY LINKED-LIST (SLL) OPERATIONS:

/**
 * @brief       CREATES a doubly linked list (SLL)
 * @param[in]   cmp     The comparison function for comparing SLL keys
 * @return      A pointer to the address of the new SLL 
*/
sll_t *sll_init(void);

/**
 * @brief       DELETES a SLL by removing itself & it's nodes from the heap
 * @param[in]   sll     The SLL to be deleted
*/
void sll_free(sll_t *sll);

/**
 * @brief       CHECKS if a SLL has any entries
 * @param[in]   sll     The SLL whose entries are to be checked
 * @return      0 if SLL has ZERO entries
 *              1 if SLL has at least ONE node
*/
int sll_is_empty(sll_t *sll);

/**
 * @brief       APPENDS a new node at the END of the SLL
 * @param[out]  sll         The SLL to be appended a new node
 * @param[in]   new_data    new_data    The address of the new data to be 
 *                          inserted as part of the SLL
 * @return      A pointer to the SLL with a newly added TAIL node
*/
sll_t *sll_insert_tail(sll_t *sll, data_t *new_data);

/**
 * @brief       DELETES the LAST node from the SLL
 * @param[out]  sll     The SLL whose LAST node is to be deleted
 * @return      The new TAIL node of the SLL
*/
sll_t *sll_delete_tail(sll_t *sll);

#endif