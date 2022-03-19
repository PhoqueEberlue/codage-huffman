//
// Created by andrewmhdb on 17/03/2022.
//

#include <malloc.h>
#include "binary_tree.h"

struct tree_list *createLeaves(struct char_list *char_list) {
    struct tree_list *tree_list = malloc(sizeof(struct tree_list));
    tree_list->node_list = malloc(char_list->last_index * sizeof(struct tree_node));
    tree_list->size = char_list->last_index;

    for (int i = 0; i < char_list->last_index; ++i) {
        struct tree_node *new_node = malloc(sizeof(struct tree_node));
        new_node->character = char_list->node_list[i].character;
        new_node->occurrences = char_list->node_list[i].occurrences;
        new_node->left = NULL;
        new_node->right = NULL;
        tree_list->node_list[i] = *new_node;
    }

    return tree_list;
}

void addNewNode(struct tree_list *tree_list, struct tree_node *new_node, int node_remaining) {
    // TODO: shift the list up to the index in createTree to avoid shifting nodes that have already been processed
    int index_to_insert;
    for (int i = 0; i < tree_list->size; ++i) {
        if (tree_list->node_list[i].occurrences <= new_node->occurrences) {
            index_to_insert = i;
            break;
        }
    }

    // shifts the list before adding the new node
    for (int i = node_remaining - 1; i >= index_to_insert; --i) {
        tree_list->node_list[i + 1] = tree_list->node_list[i];
    }

    tree_list->node_list[index_to_insert] = *new_node;
}

struct tree_node *createTree(struct tree_list *tree_list) {
    int index = tree_list->size - 1;
    int processed_node_count = 0;

    printf("%i\n", index);
    struct tree_node *node_list = tree_list->node_list;
    // TODO: find a way to compute the exact size we need for the array
    struct tree_node *node_list_processed = malloc(255 * sizeof(struct tree_node));

    while (index != 0) {
        struct tree_node *left = &node_list[index];
        struct tree_node *right = &node_list[index - 1];

        node_list_processed[processed_node_count] = *left;
        node_list_processed[processed_node_count + 1] = *right;

        struct tree_node *new_node = malloc(sizeof(struct tree_node));
        new_node->left = &node_list_processed[processed_node_count];
        new_node->right = &node_list_processed[processed_node_count + 1];

        // Fix un problème d'addition des occurrences
        new_node->occurrences = new_node->left->occurrences + new_node->right->occurrences;
        new_node->character = -1;


        for (int i = 0; i < index; ++i) {
            if (node_list[i].character == -1) {
                printf("\033[0;31m %c %i|", node_list[i].character, node_list[i].occurrences);
            }
            else {

                printf("\033[0;37m %c %i|", node_list[i].character, node_list[i].occurrences);
            }
        }


        printf("\n");
        addNewNode(tree_list, new_node, index);

        processed_node_count = processed_node_count + 2;
        index = index - 1;
    }
    printf("%c %i|\n", node_list[0].character, node_list[0].occurrences);
    return &node_list[0];
}

void printTree(struct tree_node *root) {
    if (root == NULL) {
        return;
    }
    printTree(root->left);
    printf("%c %i\n", root->character, root->occurrences);
    printTree(root->right);
}


void printTree2(struct tree_node *root, int space){
    if (root == NULL)
        return;
    space += 1;
    printTree2(root->right, space);
    for (int i = 1; i < space; ++i)
        printf("\t");
    printf("%c %i\n", root->character, root->occurrences);
    printTree2(root->left, space);
}