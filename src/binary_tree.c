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

    // creates the list data structure
    struct tree_node_list *tree_list = malloc(sizeof(struct tree_node_list));

    // creates the list itself
    tree_list->node_list = malloc(char_list->last_index * sizeof(struct tree_node));
    tree_list->size = char_list->last_index;

    for (int i = 0; i < char_list->last_index; ++i) {
        tree_list->node_list[i].character = char_list->node_list[i].character;
        tree_list->node_list[i].occurrences = char_list->node_list[i].occurrences;
        tree_list->node_list[i].left = NULL;
        tree_list->node_list[i].right = NULL;
    }

    return tree_list;
}

void printListsStates(struct tree_node *no_char_node_list, struct tree_node_list *tree_node_list,
                      int index_leaves, int index_nodes_r, int index_nodes_w) {
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < tree_node_list->size; ++i) {
        if (i == index_leaves) {
            printf("\033[0;31m");
        } else if (i > index_leaves) {
            printf("\033[0;32m");
        } else {
            printf("\033[0;37m");
        }
        printf("%c %i|", tree_node_list->node_list[i].character, tree_node_list->node_list[i].occurrences);
    }
    printf("\033[0;37m\n");
    printf("    ");
    for (int i = 0; i < tree_node_list->size - 1; ++i) {
        if (i == index_nodes_r) {
            printf("\033[0;31m");
        } else if (i == index_nodes_w) {
            printf("\033[0;35m");
        } else if (i > index_nodes_r) {
            printf("\033[0;32m");
        } else {
            printf("\033[0;37m");
        }
        printf("  %i|", no_char_node_list[i].occurrences);
    }
    printf("\033[0;37m\n");
}

struct tree_node *createTree(struct tree_node_list *tree_node_list) {
    /*
     * Creates a tree from a tree_node_list
     */

    // Creating the list that stores the nodes without characters.
    // The number of nodes without character is always: Nb char node - 1
    struct tree_node *no_char_node_list = malloc(sizeof(struct tree_node) * tree_node_list->size - 1);
    struct tree_node *leaves_list = tree_node_list->node_list;

    // the current index of the tree node list
    int index_leaves = tree_node_list->size - 1;

    // the current write index of the no char node list
    int index_nodes_w = tree_node_list->size - 2;
    // the current read index of the no char node list
    int index_nodes_r = tree_node_list->size - 2;

    struct tree_node *left;
    struct tree_node *right;

    while (index_leaves != -1 || index_nodes_r != 0) {

#ifdef PRINT_MODE
        printListsStates(no_char_node_list, tree_node_list, index_leaves, index_nodes_r, index_nodes_w);
#endif
        // if the leaves queue is empty OR if the actual leave have a greater occurrence than the next two no char node
        if (index_leaves == -1 || (no_char_node_list[index_nodes_r].occurrences != 0 &&
                                   no_char_node_list[index_nodes_r - 1].occurrences != 0 &&
                                   leaves_list[index_leaves].occurrences > no_char_node_list[index_nodes_r].occurrences)
                                  && leaves_list[index_leaves].occurrences >
                                     no_char_node_list[index_nodes_r - 1].occurrences) {

            // take the next two no char node
            left = &no_char_node_list[index_nodes_r];
            right = &no_char_node_list[index_nodes_r - 1];
            index_nodes_r = index_nodes_r - 2;
        }

        // if there is only one leaf remaining OR if the next no char node exists and is lesser than the actual leaf
        else if (index_leaves == 0 || (no_char_node_list[index_nodes_r].character != 0
                   && leaves_list[index_leaves - 1].occurrences > no_char_node_list[index_nodes_r].occurrences)) {

            // take one leaf and one no char node
            if (no_char_node_list[index_nodes_r].occurrences > leaves_list[index_leaves].occurrences) {
                left = &leaves_list[index_leaves];
                right = &no_char_node_list[index_nodes_r];
            } else {
                right = &leaves_list[index_leaves];
                left = &no_char_node_list[index_nodes_r];
            }
            index_nodes_r--;
            index_leaves--;

        } else {
            // Take two leaves
            left = &leaves_list[index_leaves];
            right = &leaves_list[index_leaves - 1];
            index_leaves = index_leaves - 2;
        }

        no_char_node_list[index_nodes_w].character = -1;
        // sum the two nodes
        no_char_node_list[index_nodes_w].occurrences = left->occurrences + right->occurrences;
        // stores the pointer of the two nodes into left and right
        no_char_node_list[index_nodes_w].left = left;
        no_char_node_list[index_nodes_w].right = right;
        index_nodes_w--;
    }

#ifdef PRINT_MODE
    printListsStates(no_char_node_list, tree_node_list, index_leaves, index_nodes_r, index_nodes_w);
#endif

    return &no_char_node_list[0];
}

void printTree(struct tree_node *root) {
    if (root == NULL) {
        return;
    }
    printTree(root->left);
    printf("%c %i\n", root->character, root->occurrences);
    printTree(root->right);
}


void printTree2(struct tree_node *root, int space) {
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


//TODO: change bool is_leaf to a condition is current node code == -1
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

float getMeanCodeSize(struct char_list *char_list) {
    /*
     * Gets the mean size of the codes
     */
    int sum_code_sizes = 0;

    for (int i = 0; i < char_list->last_index; ++i) {
        sum_code_sizes += char_list->node_list[i].code_size;
    }
    return sum_code_sizes / char_list->last_index;
}

void freeTree(struct tree_node *root) {
    /*
     * Free recursively every node of a given tree
     */
    if (root->character != -1) {
        freeTree(root->left);
        freeTree(root->right);
    }
    free(root);
}