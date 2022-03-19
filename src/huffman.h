//
// Created by andrewmhdb on 15/03/2022.
//

// Comment the line bellow to deactivate prints
#define PRINT_MODE

#ifndef CODAGE_HUFFMAN_HUFFMAN_H
#define CODAGE_HUFFMAN_HUFFMAN_H

#include "binary_tree.h"
#include "occurrence.h"

struct huffman_data {
    struct char_list *char_list;
    struct tree_node *root;
    int *depth;
};

struct huffman_data *applyHuffmanOnFile(char *file_path);





#endif //CODAGE_HUFFMAN_HUFFMAN_H
