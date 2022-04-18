//
// Created by andrewmhdb on 15/03/2022.
//

#include <malloc.h>
#include <string.h>
#include "huffman.h"

struct huffman_data *applyHuffmanOnFile(char *file_path) {
    /*
     * Call every function to compute the huffman codes
     */

    // Generating occurrences list
    struct char_list *char_list = generateOccurrences(file_path);

#ifdef PRINT_MODE
    printOccurrenceList(char_list);
    printf("\n");
#endif

    // Sorting by character occurrence
    sortCharListByOcc(char_list);

#ifdef PRINT_MODE
    printf("Sorted by occurrences\n");
    printOccurrenceList(char_list);
    printf("\n");
#endif

    // Sorting by ASCII code
    sortCharListByASCIICode(char_list);

#ifdef PRINT_MODE
    printf("Sorted by occurrences then ASCII code\n");
    printOccurrenceList(char_list);
    printf("\n");
#endif


    // Creating leaves
    struct tree_node_list *tree_node_list = createLeaves(char_list);

    // Creating tree
    struct tree_node *no_char_node_list = createTree(tree_node_list);
    struct tree_node *root = &no_char_node_list[0];

#ifdef PRINT_MODE
    printf("Representation of the tree (left to right)\n");
    printTree2(root, 0);
    printf("\n");
#endif

    int *depth = malloc(sizeof(int));
    *depth = 0;

    // Get the Depth
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

    // Creating huffman data struct
    struct huffman_data *huffman_data = malloc(sizeof(struct huffman_data));
    huffman_data->char_list = char_list;
    huffman_data->tree_node_list = tree_node_list;
    huffman_data->no_char_node_list = no_char_node_list;
    huffman_data->root = root;
    huffman_data->depth = *depth;
    huffman_data->file_path = file_path;

    return huffman_data;
}

void generateFreqFile(struct huffman_data *huffman_data, char *file_path) {
    FILE *res_file = fopen(file_path, "w");
    fprintf(res_file, "%i", huffman_data->root->occurrences);

    for (int i = 0; i < huffman_data->char_list->last_index; ++i) {
        fwrite("\n", 1, 1, res_file);
        fwrite(&huffman_data->char_list->node_list[i].character, 1, 1, res_file);
        fwrite(" ", 1, 1, res_file);
        fprintf(res_file, "%i", huffman_data->char_list->node_list[i].occurrences);
    }
    fclose(res_file);
}

void generateCompressedFile(struct huffman_data *huffman_data, char *file_path) {
    /*
     * Generate compressed file
     */
    char *freq_ext = "_freq.txt";
    char *comp_ext = "_comp.bin";

    char *file_path_freq;
    strncpy(file_path_freq, file_path, strlen(file_path) - 4);
    file_path_freq[strlen(file_path) - 4] = '\0';
    strcat(file_path_freq, freq_ext);

    generateFreqFile(huffman_data, file_path_freq);
    FILE *base_file;
    base_file = fopen(huffman_data->file_path, "r");

    char *file_path_comp;
    strncpy(file_path_comp, file_path, strlen(file_path) - 4);
    file_path_comp[strlen(file_path) - 4] = '\0';
    strcat(file_path_comp, comp_ext);

    FILE *res_file;
    res_file = fopen(file_path_comp, "wb");

    int character;
    short num_bit = 7;
    unsigned long byte_count = 0;
    unsigned long byte_count_base_file = 0;
    unsigned long number;

    // For each char in file
    while (!feof(base_file)) {
        byte_count_base_file++;
        character = fgetc(base_file);
        struct char_node *node = getCharNodeByCharacter(huffman_data->char_list, character);

// #ifdef PRINT_MODE
//        printf("%c: ", node->character);
// #endif
        for (int i = 0; i < node->code_size; ++i) {
// #ifdef PRINT_MODE
//            printf("%i", node->code[i]);
// #endif
            number ^= (-node->code[i] ^ number) & (1UL << num_bit);

            if (num_bit == 0) {
                byte_count++;
                fwrite(&number, 1, 1, res_file);
                num_bit = 7;
            } else {
                --num_bit;
            }
        }
// #ifdef PRINT_MODE
//        printf("\n");
// #endif
    }

    // treat the last remaining bits
    if (num_bit != 7) {
        for (int i = num_bit; i > 0; --i) {
            // https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
            number ^= (-0 ^ number) & (1UL << num_bit);
        }
        fwrite(&number, 1, 1, res_file);
    }

    fclose(base_file);
    fclose(res_file);

    huffman_data->byte_count = byte_count;
    huffman_data->byte_count_base_file = byte_count_base_file;
}

void printHuffmanData(struct huffman_data *huffman_data) {
    /*
     * Print huffman related data
     */
    printf("Huffman data of the file: %s\n", huffman_data->file_path);
    printf("Depth of the tree: %i\n", huffman_data->depth);
    printf("Nb bytes of the new file: %lu\n", huffman_data->byte_count);
    printf("Nb of the base file: %lu\n", huffman_data->byte_count_base_file);
    printf("Compression ratio: %Lf\n",
           1 - ((long double) huffman_data->byte_count / huffman_data->byte_count_base_file));
    printf("Mean code size: %f\n", getMeanCodeSize(huffman_data->char_list));
}

void freeHuffman(struct huffman_data *huffman_data) {
    /*
     * Free variables used by huffman
     */
    freeCharList(huffman_data->char_list);
    // freeTree(huffman_data->root);
    // free(huffman_data->no_char_node_list);
    // free(huffman_data->tree_node_list->node_list);
    free(huffman_data->tree_node_list);
    free(huffman_data);
}

struct huffman_data *mainHuffman(char *file_path) {
    struct huffman_data *huffman_data = applyHuffmanOnFile(file_path);
    generateCompressedFile(huffman_data, file_path);
    printHuffmanData(huffman_data);
    freeHuffman(huffman_data);
}