/* Source file : encode.c
 * MUNOZ Melvyn, CAUSSE Raphael
 * CY TECH PREING 2 MI
**/

#include "include/func.h"
#include "include/encode.h"

short get_char_freq_in_file(FILE *input_file, data_t *hdico) {
    /* Read each character from input file and increment in array their frequence.
       Array index are their numeric value. */
    unsigned char c = 0;
    while (fread(&c, sizeof(char), 1, input_file) > 0) {
        hdico[c].charact = c;
        hdico[c].freq++;
    }
    /* Return number of different characters. */
    short nb_char = 0;
    for (short i = 0; i < NB_MAX_CHAR; i++) {
        if (hdico[i].freq == 0) continue;
        nb_char++;
    }
    fclose(input_file);
    return nb_char;
}

ptrhqueue fill_queue_with_tree(ptrhqueue queue, data_t *array, short size) {
    /* Fill queue only if is empty at first. */
    if (!queue) {
        ptrhtree node = NULL;
        for (short i = 0; i < size; i++) {
            /* Create tree node from data array. Enqueue in queue. */
            node = tree_create(array[i].charact, array[i].freq);
            queue = queue_push(queue, node);
        }
        return queue;
    }
    return NULL;
}

ptrhtree build_huffman_tree(ptrhqueue priority_queue) {
    ptrhtree node1 = NULL, node2 = NULL;
    /* Create parent tree node with first two nodes of priority queue. Pop priority queue 
       twice and push parent tree node in it. Repeat until ir remains one node in priority queue.
       Return root of huffman tree. */
    while (priority_queue && priority_queue->next) {
        node1 = priority_queue->tree; node2 = priority_queue->next->tree;
        priority_queue = queue_pop(priority_queue); priority_queue = queue_pop(priority_queue);
        priority_queue = queue_push(priority_queue, tree_create_parent(node1, node2));
    }
    ptrhtree root = priority_queue->tree;
    /* Free last node of priority queue to prevent memory leaks. */
    priority_queue = queue_pop(priority_queue);
    return root;
}

void get_huffman_code_in_dico(ptrhtree root, data_t *hdico, unsigned bin_code, unsigned nbits) {
    /* DFS preorder : go to left, bit 0 and go to right, bit 1. */ 
    if (!root->left && !root->right) {
        /* Store in dictionary at character index code and nbits of character. */
        hdico[root->charact].hcode = bin_code;
        hdico[root->charact].nbits = nbits;
        return;
    }
    /* Shift code 1 bit to the left, concat bit 0. Increment the nbits (depth). */
    if (root->left)        
        get_huffman_code_in_dico(root->left, hdico, (bin_code<<1), nbits+1);
    /* Shift code 1 bit to the left, concat bit 1. Increment the nbits (depth). */
    if (root->right)
        get_huffman_code_in_dico(root->right, hdico, (bin_code<<1)+1, nbits+1);
}

void write_dico_in_binary_file(FILE *output_file, data_t *hdico, short size) {
    fwrite(&size, sizeof(short), 1, output_file);
    /* Write character and frequence at beginning of output_file. */
    for (short i = 0; i < NB_MAX_CHAR; i++){
        if (hdico[i].freq == 0) continue;
        fwrite(&hdico[i].charact, sizeof(char), 1, output_file);
        fwrite(&hdico[i].freq, sizeof(unsigned), 1, output_file);
    }
}

void encoding(const char *__inputname, const char *__outputname, data_t *hdico, short size) {
    float nbits_input = 0, nbits_output = 0; 
    FILE *input_file = NULL, *output_file = NULL;
    input_file = open_file(__inputname, "r");
    output_file = fopen(__outputname, "wb");
    write_dico_in_binary_file(output_file, hdico, size);
    /* Read each character from input_file and write matching huffman code in output_file. */
    unsigned char read_char = 0;
    unsigned char c_bin = 0;
    unsigned buffer = 0, buffer_size = 0; 
    while (fread(&read_char, sizeof(char), 1, input_file) > 0) {
        /* Shift buffer to left by nbits needed for the read character and concat bits of
           huffman code of the read character, using OR "|" operator for binary mask. */
        buffer = (buffer << hdico[read_char].nbits);
        buffer = (buffer | hdico[read_char].hcode);
        buffer_size += hdico[read_char].nbits;
        /* When buffer contains at least 8 bits, write those 8 bits in output_file. */
        while (buffer_size >= 8) {
            buffer_size -= 8;
            c_bin = (buffer >> buffer_size);
            fwrite(&c_bin, sizeof(char), 1, output_file);
            nbits_output += 8;
        }
        nbits_input += 8;
    }
    /* If buffer ends up not full (under 8), concat bits 0 to fulfill it, then write it. */
    if (buffer_size && buffer_size < 8) {
        c_bin = (buffer << (8-buffer_size));
        fwrite(&c_bin, sizeof(char), 1, output_file);
        nbits_output += 8;
    }
    /* Compression efficiency. */
    printf("%.f kb compressed to %.f kb [%.1f %%].\n", nbits_input/1000, nbits_output/1000,
    100-((nbits_output/nbits_input)*100));
    fclose(output_file);
    fclose(input_file);
}

void compression(const char *__inputname, const char *__outputname) {
    clock_t start, end;
    double time_taken;
    FILE *input_file = NULL;
    
    input_file = open_file(__inputname, "r");
    printf("Compressing [%s] ...\n", __inputname);
    start = clock();
    data_t hdico[NB_MAX_CHAR] = {{0},{0},{0},{0}};
    short nb_char = get_char_freq_in_file(input_file, hdico);
    data_t only_char[nb_char];
    array_copy_only_data(hdico, only_char, nb_char);
    array_sort(only_char, nb_char);
    /* Using priority queue to build huffman tree. */
    ptrhqueue priority_queue = NULL;
    priority_queue = fill_queue_with_tree(priority_queue, only_char, nb_char);
    ptrhtree huffman_tree = NULL;
    huffman_tree = build_huffman_tree(priority_queue);
    get_huffman_code_in_dico(huffman_tree, hdico, 0, 0);
    encoding(__inputname, __outputname, hdico, nb_char);
    tree_free(huffman_tree);
    /* Time in seconds. */
    end = clock();
    time_taken = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Done in %.3f s.\n\n", time_taken);
}