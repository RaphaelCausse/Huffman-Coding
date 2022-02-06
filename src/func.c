/* Source file : func.c
 * MUNOZ Melvyn, CAUSSE Raphael
 * CY TECH PREING 2 MI
**/

#include "include/func.h"

void help() {
    printf("\x1b[1mHUFFMAN CODING\x1b[0m\n\thuffman - C project - implementation of Huffman algorithm\n\n"
    "\x1b[1mUSAGE\x1b[0m:\n\thuffman [-h|--help|-c|-d] [input_file] [output_file]\n\n"
    "\x1b[1mOPTIONS:\x1b[0m\n"
    "\t\x1b[1m-c\x1b[0m\t\tCompress input file into binary output file.\n"
    "\t\x1b[1m-d\x1b[0m\t\tDecompress binary input file.\n"
    "\t\x1b[1m-h, --help\x1b[0m\tPrint usage and this help message and exit.\n"
    "\t\x1b[1m-v, --version\x1b[0m\tPrint version and authors and exit.\n\n"
    "\x1b[1mDESCRIPTION:\x1b[0m\n"
    "\thuffman -c file encoded\n"
    "\thuffman -d encoded decoded\n\n");
    exit(EXIT_SUCCESS);
}

void version() {
    printf("huffman v1.0 - Copyright (c) 2021 by Melvyn MUNOZ, Raphael CAUSSE"
    " - CY TECH PREING 2 MI\n\n");
    exit(EXIT_SUCCESS);
}

FILE *open_file(const char *__filename, const char *__mode) {
    /* Open file and create a new stream for it. */
    FILE *file = fopen(__filename, __mode);
    if (file == NULL) {
        fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1m%s:\x1b[0m %s.\n\n", __filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return file;
}

void array_copy_only_data(data_t *array, data_t *cpy_array, short size) {
    for (short i = 0, j = 0; i < NB_MAX_CHAR && j < size; i++) {
        /* Copy only if there is an frequence in array. */
        if (array[i].freq == 0) continue;
        cpy_array[j].charact = array[i].charact;
        cpy_array[j].freq = array[i].freq;
        j++;
    }
}

void array_sort(data_t *array, short size) {
    /* Insertion sort in ascending order. */
    short j;
    data_t tmp;
    for (short i = 1; i < size; i++) {
        tmp = array[i];
        j = i-1;
        while ((j >= 0) && (tmp.freq < array[j].freq)) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = tmp;
    }
}

ptrhqueue queue_push(ptrhqueue queue, ptrhtree tree) {
    /* Memory allocation. */
    ptrhqueue new = calloc(1, sizeof(hqueue_t));
    if (!new) {
        fprintf(stderr, "\x1b[1m%s:\x1b[0m In function '%s':\n"
        "\033[31m%s:%i: error: calloc failed\033[0m\n",__FILE__ ,__func__ ,__FILE__ ,((__LINE__)-3));
        exit(EXIT_FAILURE);
    }
    /* Initialize new element. */
    new->tree = tree; new->next = NULL; 
    if (!queue)
        return new;
    /* Push node in the priority queue. */
    ptrhqueue tmp = queue;
    while (tmp->next && tmp->next->tree->freq < new->tree->freq)
        tmp = tmp->next;
    new->next = tmp->next;
    tmp->next = new;
    return queue;
}

ptrhqueue queue_pop(ptrhqueue queue) {
    /* Pop out first node of priority queue. */
    if (!queue)
        return NULL;
    ptrhqueue tmp = queue->next;
    queue->next = NULL;
    free(queue);
    return tmp;
}

void queue_free(ptrhqueue queue) {
    while (queue) {
        /* Free allocated memory for tree node then for queue node. */ 
        tree_free(queue->tree);
        queue = queue_pop(queue);
    }
}

ptrhtree tree_create(unsigned char ch, unsigned freq) {
    /* Memory allocation. */
    ptrhtree new = calloc(1, sizeof(htree_t));
    if (!new) {
        fprintf(stderr, "\x1b[1m%s:\x1b[0m In function '%s':\n"
        "\033[31m%s:%i: error: calloc failed\033[0m\n",__FILE__ ,__func__ ,__FILE__ ,((__LINE__)-3));
        exit(EXIT_FAILURE);
    }
    /* Initialize new element. */
    new->charact = ch; new->freq = freq;
    new->hcode = 0; new->nbits = 0;
    new->left = NULL; new->right = NULL;
    return new;
}

ptrhtree tree_create_parent(ptrhtree tree1, ptrhtree tree2) {
    /* Create parent node with two sons. '$' is neutral for internal nodes. */
    ptrhtree parent = tree_create('$', tree1->freq + tree2->freq);
    if (tree1->freq <= tree2->freq) {
        parent->left = tree1;
        parent->right = tree2;
    } else {
        parent->left = tree2;
        parent->right = tree1;
    }
    return parent;
}

void tree_free(ptrhtree root) {
    if (root) {
        /* DFS postorder, free the entire tree. */
        tree_free(root->left);
        tree_free(root->right);
        free(root);
        root = NULL;
    }
}