//
// Created by andrewmhdb on 17/03/2022.
//

#ifndef CODAGE_HUFFMAN_BINARY_TREE_H
#define CODAGE_HUFFMAN_BINARY_TREE_H

#include "occurrence.h"

struct tree_node_list {
    struct tree_node *node_list;
    int last_index;
    int size;
};

struct tree_node {
    struct tree_node *left;
    struct tree_node *right;
    int character;
    int occurrences;
};

struct tree_node_list *createLeaves(struct char_list *char_list);

struct tree_node *createTree(struct tree_node_list *tree_node_list);

void printTree(struct tree_node *root);

void printTree2(struct tree_node *root, int space);

void getDepth(int *res, struct tree_node *root, int depth);

void generateCodes(struct char_list *char_list, struct tree_node *root, char *code, int depth);

float getMeanCodeSize(struct char_list *char_list);

void freeTree(struct tree_node *root);

#endif //CODAGE_HUFFMAN_BINARY_TREE_H
