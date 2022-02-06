/* Header file : encode.h
 * MUNOZ Melvyn, CAUSSE Raphael
 * CY TECH PREING 2 MI
**/

#ifndef ENCODE_H
#define ENCODE_H

#include "huffman.h"

/* Get frequence of characters from input_file and store them in dictionary.
   Return number of different characters read from input_file. */
short get_char_freq_in_file(FILE *input_file, data_t *hdico);

/* Fill queue with tree nodes created from data array. */
ptrhqueue fill_queue_with_tree(ptrhqueue queue, data_t *array, short size);

/* Build Huffman tree using priority queue method.
   Return pointer to tree in the last node : root of huffman binary tree. */
ptrhtree build_huffman_tree(ptrhqueue queue);

/* Get Huffman code and nbits of each characters.
   Store them in dico at character index. */
void get_huffman_code_in_dico(ptrhtree root, data_t *hdico, unsigned code, unsigned nbits);

/* Write huffman dictionary at beginning of output file. */
void write_dico_in_binary_file(FILE *output_file, data_t *hdico, short size);

/* Encode input file into binary output file.
   Write binary huffman code of each charaters from input file in output file. */
void encoding(const char *__inputname, const char *__outputname, data_t *hdico, short size);

/* Compress input file (.txt) into binary output file (.hff). */
void compression(const char *__inputname, const char *__outputname);

#endif