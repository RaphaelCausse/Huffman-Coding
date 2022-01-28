/**
 * Header file : huffman.h
 * MUNOZ Melvyn, CAUSSE Raphael
 * CY TECH PREING 2 MI
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

/* Max value for extended ASCII 0-255 */
#define NB_MAX_CHAR 256

/* Dictionary to store data from characters. */
typedef struct _data {
    unsigned char charact;  /* Initial character */
    unsigned freq;        	/* Character frequence */
	unsigned hcode;         /* Huffman code */
    unsigned nbits;         /* Number of bits needed for Huffman code */
} data_t;

/* Huffman tree nodes. */
typedef struct _htree {
    unsigned char charact;  /* Initial character */
    unsigned freq;        	/* Character frequence */
    unsigned hcode;         /* Huffman code */
    unsigned nbits;         /* Number of bits needed for Huffman code */
    struct _htree *left;    /* Left son in binary tree */
    struct _htree *right;   /* Right son in binary tree */
} htree_t, *ptrhtree;

/* Queue of tree nodes to build huffman tree. */
typedef struct _hqueue {
    ptrhtree tree;          /* Huffman tree node */
    struct _hqueue *next;   /* Next in queue */
} hqueue_t, *ptrhqueue;

#endif