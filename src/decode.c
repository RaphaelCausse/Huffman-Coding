/* Source file : decode.c
 * MUNOZ Melvyn, CAUSSE Raphael
 * CY TECH PREING 2 MI
**/

#include "include/func.h"
#include "include/encode.h"
#include "include/decode.h"

short get_nb_char(FILE *input_file) {
    short nb_char;
    /* Read number of different character at beginning of input_file. */
    fread(&nb_char, sizeof(short), 1, input_file);
    return nb_char;
}

void get_dico_from_binary_file(FILE *input_file, data_t *hdico, short size) {
    /* Read character and frequence at beginning of input_file. */
    for (short i = 0; i < size; i++) {
        fread(&hdico[i].charact, sizeof(char), 1, input_file);
        fread(&hdico[i].freq, sizeof(unsigned), 1, input_file);
    }
}

void get_huffman_code_in_tree(ptrhtree root, unsigned bin_code, unsigned nbits) {
    /* DFS preorder : go to left, bit 0 and go to right, bit 1. */ 
    if (!root->left && !root->right) {
        /* Store in tree node code and nbits of matching character. */
        root->hcode = bin_code; root->nbits = nbits;
        return;
    }
    /* Shift code 1 bit to the left, concat bit 0. Increment nbits. */
    if (root->left)        
        get_huffman_code_in_tree(root->left, (bin_code<<1), nbits+1);
    /* Shift code 1 bit to the left, concat bit 1. Increment nbits. */
    if (root->right)
        get_huffman_code_in_tree(root->right, (bin_code<<1)+1, nbits+1);
}

ptrhtree search_character_in_tree(ptrhtree tree, unsigned buffer, unsigned buffer_size, int nb_bits) {
    /* If there are not enough bits left in the buffer to find a character in tree. */
    if (nb_bits > buffer_size)
        return NULL;
    /* If leaf is reached, where data is. */
    if (!tree->left && !tree->right)
        return tree;
    /* Using AND "&" operator to compare bits per pair, to decide what branch of tree to go to. */
    /* Recursive search to left if the last bit, after right shift, is 0. */
    if (tree->left && ((buffer >> (buffer_size - nb_bits - 1)) & 1) == 0 )
        return search_character_in_tree(tree->left, buffer, buffer_size, nb_bits+1);
    /* Recursive search to right if the last bit, after right shift, is 1. */
    if (tree->right && ((buffer >> (buffer_size - nb_bits - 1)) & 1) == 1 )
        return search_character_in_tree(tree->right, buffer, buffer_size, nb_bits+1);
    /* If buffer does not match any character in huffman tree. */
    return NULL;
}

void decoding(FILE *input_file, FILE *output_file, ptrhtree root) {
    ptrhtree decoded_node;
    unsigned char c_bin = 0, c_write = 0;
    unsigned buffer = 0, buffer_size = 0, nb_total_char = 0;
    /* Get number of total character to write in output_file. */
    nb_total_char = root->freq;
    while (fread(&c_bin, sizeof(char), 1, input_file) > 0) {
        /* Shift buffer to left by 8 and concat in buffer read chunk of 8 bits,
           using OR "|" operator for binary mask. */
        buffer = (buffer << 8);
        buffer = (buffer | c_bin);
        buffer_size += 8;
        /* Search in tree character using buffer and comparing bits.
           Decrement count of total characters to write and write matching character. */
        while ((decoded_node = search_character_in_tree(root, buffer, buffer_size, 0)) && nb_total_char) {
            c_write = decoded_node->charact;
            fwrite(&c_write, sizeof(char), 1, output_file);
            nb_total_char--;
            buffer_size -= decoded_node->nbits;
        }
    }
    fclose(output_file);
    fclose(input_file);
}

void decompression(const char *__inputname, const char *__outputname) {
    clock_t start, end;
    double time_taken;
    FILE *input_file = NULL, *output_file = NULL;

    input_file = open_file(__inputname, "rb");
    output_file = fopen(__outputname, "w");
    printf("Decompressing [%s] ...\n", __inputname);
    start = clock();
    /* Collect dictionary to rebuild huffman tree. */
    short nb_char = get_nb_char(input_file);
    data_t hdico[nb_char];
    get_dico_from_binary_file(input_file, hdico, nb_char);
    array_sort(hdico, nb_char);
    ptrhqueue priority_queue = NULL;
    priority_queue = fill_queue_with_tree(priority_queue, hdico, nb_char);
    ptrhtree huffman_tree = NULL;
    huffman_tree = build_huffman_tree(priority_queue);
    get_huffman_code_in_tree(huffman_tree, 0, 0);
    decoding(input_file, output_file, huffman_tree);
    tree_free(huffman_tree);
    /* Time in seconds. */
    end = clock();
    time_taken = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Done in %.3f s.\n\n", time_taken);
}