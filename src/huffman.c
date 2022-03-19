//
// Created by andrewmhdb on 15/03/2022.
//

#include <malloc.h>
#include "huffman.h"

struct huffman_data *applyHuffmanOnFile(char *file_path) {
    // Generating occurrences list
    struct char_list *char_list = generateOccurrences(file_path);

#ifdef PRINT_MODE
    printOccurrenceList(char_list);
    printf("\n");
#endif

    sortCharListByOcc(char_list);

#ifdef PRINT_MODE
    printf("Sorted by occurrences\n");
    printOccurrenceList(char_list);
    printf("\n");
#endif

    sortCharListByASCIICode(char_list);

#ifdef PRINT_MODE
    printf("Sorted by occurrences then ASCII code\n");
    printOccurrenceList(char_list);
    printf("\n");
#endif

    struct tree_node_list *tree_node_list = createLeaves(char_list);

    struct tree_node *root = createTree(tree_node_list);

#ifdef PRINT_MODE
    printf("Representation of the tree (left to right)\n");
    printTree2(root, 0);
    printf("\n");
#endif

    int *depth = malloc(sizeof(int));
    *depth = 0;

    getDepth(depth, root, 0);

#ifdef PRINT_MODE
    printf("Cumulated occurrences (Total number of characters in the text): ");
    printf("%i\n", root->occurrences);
    printf("Depth of the tree: ");
    printf("%i\n", *depth);
    printf("\n");
#endif

    char *code = malloc(*depth * sizeof(char));
    generateCodes(char_list, root, code, 0);

#ifdef PRINT_MODE
    printf("Character, Character ASCII code, occurrences in the text, huffman code\n");
    printOccurrenceList(char_list);
    printf("\n");
#endif

    struct huffman_data *huffman_data = malloc(sizeof(struct huffman_data));
    huffman_data->char_list = char_list;
    huffman_data->root = root;
    huffman_data->depth = depth;

    return huffman_data;
}