/* Header file : decode.h
 * MUNOZ Melvyn, CAUSSE Raphael
 * CY TECH PREING 2 MI
**/

#ifndef DECODE_H
#define DECODE_H

#include "huffman.h"

/* Get number of different characters for size of dictionary. */
short get_nb_char(FILE *input_file);

/* Get dictionary at beginning of binary input_file. */
void get_dico_from_binary_file(FILE *input_file, data_t *hdico, short size);

/* Get Huffman code and nbits of each characters.
   Store them in leaf corresponding to character. */
void get_huffman_code_in_tree(ptrhtree root, unsigned bin_code, unsigned nbits);

/* Scan huffman tree (DFS preorder) with buffer until leaf is reached.
   Return leaf that match with bit sequence from buffer. */
ptrhtree search_character_in_tree(ptrhtree tree, unsigned buffer, unsigned buffer_size, int nb_bits);

/* Decode binary input file into output file. */
void decoding(FILE *input_file, FILE *output_file, ptrhtree root);

/* Decompress binary input file (.hff) into output file (.txt). */
void decompression(const char *__inputname, const char *__outputname);

#endif