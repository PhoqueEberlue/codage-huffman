//
// Created by andrewmhdb on 17/03/2022.
//

#include <malloc.h>
#include "binary_tree.h"
#include "huffman.h"

struct tree_node_list *createLeaves(struct char_list *char_list) {
    /*
     * Create leaves (tree_node with no children) from a char_list
     */

    // creates the list data structure
    struct tree_node_list *tree_list = malloc(sizeof(struct tree_node_list));

    // creates the list itself
    tree_list->node_list = malloc((char_list->last_index + 1) * sizeof(struct tree_node));
    tree_list->size = char_list->last_index + 1;
    tree_list->last_index = char_list->last_index;

    for (int i = 0; i <= char_list->last_index; ++i) {
        tree_list->node_list[i].character = char_list->char_elem_p[i].character;
        tree_list->node_list[i].occurrences = char_list->char_elem_p[i].occurrences;
        tree_list->node_list[i].left = NULL;
        tree_list->node_list[i].right = NULL;
    }

    return tree_list;
}

void removeTwoNodes(struct tree_node_list *tree_node_list) {
    // i <= last_index -2 because we access i + 2
    for (int i = 0; i <= tree_node_list->last_index - 2; i++) {
        tree_node_list->node_list[i] = tree_node_list->node_list[i + 2];
    }
    tree_node_list->last_index = tree_node_list->last_index - 2;
}

void addNewNode(struct tree_node_list *tree_node_list, struct tree_node *new_node) {
    /*
     * Add a new node created by `createLeaves` into the tree_node_list
     */
    int index_to_insert;

    if (tree_node_list->node_list[tree_node_list->last_index].occurrences < new_node->occurrences) {
        index_to_insert = tree_node_list->last_index + 1;
    } else {
        for (int i = 0; i <= tree_node_list->last_index; ++i) {
            // if the current node occ is greater than or equal to the new node occ
            if (tree_node_list->node_list[i].occurrences >= new_node->occurrences) {
                index_to_insert = i;
                break;
            }
        }
    }

    tree_node_list->last_index++;
    // shifts the list before adding the new node
    // i < last_index because we access i + 1
    for (int i = tree_node_list->last_index; i >= index_to_insert; --i) {
        tree_node_list->node_list[i] = tree_node_list->node_list[i - 1];
    }
    tree_node_list->node_list[index_to_insert] = *new_node;
}

void printTreeNodeList(struct tree_node_list *tree_node_list) {
    for (int i = 0; i <= tree_node_list->last_index; ++i) {
        if (tree_node_list->node_list[i].character == -1) {
            printf("\033[0;31m   %i|", tree_node_list->node_list[i].occurrences);
        } else {
            printf("\033[0;37m %c %i|", tree_node_list->node_list[i].character,
                   tree_node_list->node_list[i].occurrences);
        }
    }

    printf("\033[0;37m\n");
}

struct tree_node *createTree(struct tree_node_list *tree_node_list) {
    /*
     * Creates a tree from a tree_node_list
     */
    int processed_node_count = 0;

    struct tree_node *node_list = tree_node_list->node_list;
    // Creates a new table to store nodes as we will delete them from node list
    // The total number of nodes in the tree is always: Nb leaf * 2 - 1
    struct tree_node *node_list_processed = malloc((tree_node_list->size * 2 - 1) * sizeof(struct tree_node));

#ifdef PRINT_MODE
    printf("Queue state: (red nodes are the non-character nodes)\n");
#endif

    while (tree_node_list->last_index != 0) {
#ifdef PRINT_MODE
        printTreeNodeList(tree_node_list);
#endif
        // Saves the two first nodes of the list
        node_list_processed[processed_node_count] = node_list[0];
        node_list_processed[processed_node_count + 1] = node_list[1];

        removeTwoNodes(tree_node_list);

        struct tree_node *new_node = malloc(sizeof(struct tree_node));

        new_node->left = &node_list_processed[processed_node_count];
        new_node->right = &node_list_processed[processed_node_count + 1];

        new_node->occurrences = new_node->left->occurrences + new_node->right->occurrences;
        new_node->character = -1;

        addNewNode(tree_node_list, new_node);
        processed_node_count = processed_node_count + 2;
    }
    node_list_processed[processed_node_count] = node_list[0];

#ifdef PRINT_MODE
    printf("\033[0;31m %i|\n", node_list[0].occurrences);
    printf("\033[0;37m\n");
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
    // if the current node is a no char node
    if (root->character == -1) {
        getDepth(res, root->left, depth + 1);
        getDepth(res, root->right, depth + 1);
    }
        // if current node is a leaf and the max depth is < to the current depth
    else if (*res < depth) {
        *res = depth;
    }
}

void generateCodes(struct char_list *char_list, struct tree_node *root, char *code, int depth) {
    /*
     * Generate binary code for each character
     */
    // if the current node is a no char node
    if (root->character == -1) {
        code[depth] = 0;
        ++depth;
        generateCodes(char_list, root->left, code, depth);
        --depth;

        code[depth] = 1;
        ++depth;
        generateCodes(char_list, root->right, code, depth);
        --depth;
    } else {
        // gets the corresponding char_elem
        struct char_elem *node = getCharNodeByCharacter(char_list, root->character);
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
        sum_code_sizes += char_list->char_elem_p[i].code_size;
    }
    return (float)sum_code_sizes / (float)char_list->last_index;
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