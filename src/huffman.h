//
// Created by andrewmhdb on 15/03/2022.
//

// Comment the line bellow to deactivate prints
#define PRINT_MODE

#ifndef CODAGE_HUFFMAN_HUFFMAN_H
#define CODAGE_HUFFMAN_HUFFMAN_H

#include "binary_tree.h"
#include "occurrence.h"

// Struct used to store all data related to huffman
struct huffman_data {
    struct char_list *char_list;
    struct tree_node_list *tree_node_list;
    struct tree_node *no_char_node_list;
    struct tree_node *root;
    int depth;
    unsigned long byte_count;
    unsigned long byte_count_base_file;
    char *file_path;
};

struct huffman_data *applyHuffmanOnFile(char *file_path);

void generateFreqFile(struct huffman_data *huffman_data, char *file_path);

void generateCompressedFile(struct huffman_data *huffman_data, char *file_path);

void printHuffmanData(struct huffman_data *huffman_data);

void freeHuffman(struct huffman_data *huffman_data);

struct huffman_data *mainHuffman(char *file_path);

#endif //CODAGE_HUFFMAN_HUFFMAN_H
