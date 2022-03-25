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
    printOccurrenceList(char_list);
    printf("\n");
#endif

    struct huffman_data *huffman_data = malloc(sizeof(struct huffman_data));
    huffman_data->char_list = char_list;
    huffman_data->root = root;
    huffman_data->depth = depth;
    huffman_data->file_path = file_path;

    return huffman_data;
}


void generateFile(struct huffman_data *huffman_data, char *file_path) {
    FILE *base_file;
    base_file = fopen(huffman_data->file_path, "r");

    FILE *res_file;
    res_file = fopen(file_path, "wb");

    int character;
    short num_bit = 0;
    unsigned long number;

    while (!feof(base_file)) {
        character = fgetc(base_file);
        struct char_node *node = getCharNodeByCharacter(huffman_data->char_list, character);

        printf("%c: ", node->character);

        for (int i = 0; i < node->code_size; ++i) {
            printf("%i", node->code[i]);
            number ^= (-node->code[i] ^ number) & (1UL << num_bit);

            if (num_bit == 7) {
                fwrite(&number, 1, 1, res_file);
                num_bit = 0;
            } else {
                ++num_bit;
            }
        }
        printf("\n");
    }
    if (num_bit != 0) {
        for (int i = num_bit; i < 8; ++i) {
            // https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
            number ^= (-0 ^ number) & (1UL << num_bit);
        }
    }
    fwrite(&number, 1, 1, res_file);

    fclose(base_file);
    fclose(res_file);

}