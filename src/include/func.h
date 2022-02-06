/* Header file : func.h
 * MUNOZ Melvyn, CAUSSE Raphael
 * CY TECH PREING 2 MI
**/

#ifndef FUNC_H
#define FUNC_H

#include "huffman.h"

/* Print usage and help information about project. */
void help();

/* Print version and authors of project. */
void version();

/* Open a file and create a new stream for it. */
FILE *open_file(const char *__filename, const char *__mode);

/* Copy in new data array only read characters and their frequence. */
void array_copy_only_data(data_t *array, data_t *cpy_array, short size);

/* Sort data array by insertion in ascending order. */
void array_sort(data_t *array, short size);

/* Push new node in priority queue.
   Return updated priority queue. */
ptrhqueue queue_push(ptrhqueue queue, ptrhtree tree);

/* Pop first node from priority queue.
   Return updated priority queue. */
ptrhqueue queue_pop(ptrhqueue queue);

/* Free allocated memory of tree node in each queue node. 
   Free the entire queue. */
void queue_free(ptrhqueue queue);

/* Create tree node with a character and frequence.
   Return the new tree node.*/
ptrhtree tree_create(unsigned char ch, unsigned freq);

/* Create a parent tree node with two nodes.
   Smaller node will always be on left branch.
   Return parent tree. */
ptrhtree tree_create_parent(ptrhtree tree1, ptrhtree tree2);

/* Free the entire binary tree. */
void tree_free(ptrhtree root);

#endif