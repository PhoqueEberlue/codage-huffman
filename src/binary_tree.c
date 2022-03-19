//
// Created by andrewmhdb on 17/03/2022.
//

#include <malloc.h>
#include <stdbool.h>
#include "binary_tree.h"
#include "huffman.h"

struct tree_node_list *createLeaves(struct char_list *char_list) {
    /*
     * Create leaves (tree_node with no children) from a char_list
     */
    struct tree_node_list *tree_list = malloc(sizeof(struct tree_node_list));
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

void addNewNode(struct tree_node_list *tree_node_list, struct tree_node *new_node, int node_remaining) {
    /*
     * Add a new node created by `createLeaves` into the tree_node_list
     */
    // TODO: shift the list up to the index in createTree to avoid shifting nodes that have already been processed
    int index_to_insert;
    for (int i = 0; i < tree_node_list->size; ++i) {
        if (tree_node_list->node_list[i].occurrences <= new_node->occurrences) {
            index_to_insert = i;
            break;
        }
    }

    // shifts the list before adding the new node
    for (int i = node_remaining - 1; i >= index_to_insert; --i) {
        tree_node_list->node_list[i + 1] = tree_node_list->node_list[i];
    }

    tree_node_list->node_list[index_to_insert] = *new_node;
}

struct tree_node *createTree(struct tree_node_list *tree_node_list) {
    /*
     * Creates a tree from a tree_node_list
     */
    int index = tree_node_list->size - 1;
    int processed_node_count = 0;

    struct tree_node *node_list = tree_node_list->node_list;
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

        new_node->occurrences = new_node->left->occurrences + new_node->right->occurrences;
        new_node->character = -1;

#ifdef PRINT_MODE
        if (index == tree_node_list->size - 1) {
            printf("Queue state: (red nodes are the non-character nodes\n");
        }

        for (int i = 0; i < index; ++i) {
            if (node_list[i].character == -1) {
                printf("\033[0;31m   %i|", node_list[i].occurrences);
            }
            else {
                printf("\033[0;37m %c %i|", node_list[i].character, node_list[i].occurrences);
            }
        }

        printf("\033[0;37m\n");
#endif
        addNewNode(tree_node_list, new_node, index);

        processed_node_count = processed_node_count + 2;
        index = index - 1;
    }

#ifdef PRINT_MODE
    printf("%c %i|\n", node_list[0].character, node_list[0].occurrences);
    printf("\n");
#endif

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
    /*
     * Clean print of a tree
     */
    if (root == NULL)
        return;
    space += 1;
    printTree2(root->right, space);
    for (int i = 1; i < space; ++i)
        printf("\t");
    printf("%c %i\n", root->character, root->occurrences);
    printTree2(root->left, space);
}

void getDepth(int *res, struct tree_node *root, int depth) {
    /*
     * update the value `res` to get the maximum depth of the tree
     */
    bool is_leaf = true;
    // if left child exists
    if (root->left != NULL) {
        getDepth(res, root->left, depth + 1);
        is_leaf = false;
    }

    // if right child exists
    if (root->right != NULL) {
        getDepth(res, root->right, depth + 1);
        is_leaf = false;
    }

    // if current node is a leaf and the max depth is < to the current depth
    if (is_leaf && *res < depth) {
        *res = depth;
    }
}

void generateCodes(struct char_list *char_list, struct tree_node *root, char *code, int depth) {
    /*
     * Generate binary code for each character
     */
    bool is_leaf = true;
    // if left child exists
    if (root->left != NULL) {
        // left child = bit 0
        code[depth] = 0;
        ++depth;
        generateCodes(char_list, root->left, code, depth);
        --depth;
        is_leaf = false;
    }

    // if right child exists
    if (root->right != NULL) {
        // right child = bit 1
        code[depth] = 1;
        ++depth;
        generateCodes(char_list, root->right, code, depth);
        --depth;
        is_leaf = false;
    }

    // if current node is a leaf
    if (is_leaf) {
        // gets the corresponding char_node
        struct char_node *node = getCharNodeByCharacter(char_list, root->character);
        node->code = malloc(depth * sizeof(char));

        // make a copy of the actual code
        for (int i = 0; i < depth; ++i) {
            node->code[i] = code[i];
            node->code_size = depth;
        }
    }
}
