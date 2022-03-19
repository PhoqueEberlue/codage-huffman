//
// Created by andrewmhdb on 17/03/2022.
//

#include "occurrence.h"

#ifndef CODAGE_HUFFMAN_BINARY_TREE_H
#define CODAGE_HUFFMAN_BINARY_TREE_H

struct tree_list {
    struct tree_node *node_list;
    int size;
};

struct tree_node {
    struct tree_node *left;
    struct tree_node *right;
    int character;
    int occurrences;
};

struct tree_list *createLeaves(struct char_list *char_list);

struct tree_node *createTree(struct tree_list *tree_list);

void printTree(struct tree_node *root);

void printTree2(struct tree_node *root, int space);

#endif //CODAGE_HUFFMAN_BINARY_TREE_H
