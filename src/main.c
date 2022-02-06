/* Source file : main.c
 * MUNOZ Melvyn, CAUSSE Raphael
 * CY TECH PREING 2 MI
**/

#include "include/func.h"
#include "include/encode.h"
#include "include/decode.h"

int main(int argc, char **argv) {
    /* Arguments management. */
    if (argc != 4) {
        if (argv[1] && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
            help();
        else if (argv[1] && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0))
            version();
        else {
            fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1munvalid arguments:\x1b[0m\n"
            "Run « huffman -h » or « huffman --help » for more information.\n\n");
            exit(EXIT_FAILURE);
        }
    }
    if (argv[1] && argv[2] && argv[3]) {
        if (strcmp(argv[1], "-c") == 0)
            compression(argv[2], argv[3]);
        else if (strcmp(argv[1], "-d") == 0)
            decompression(argv[2], argv[3]);
        else {
            fprintf(stderr, "\033[31m\x1b[1mError:\x1b[0m\033[0m \x1b[1munvalid arguments:\x1b[0m\n"
            "Run « huffman -h » or « huffman --help » for more information.\n\n");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}