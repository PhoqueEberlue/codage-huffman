//
// Created by andrewmhdb on 15/03/2022.
//

#include "huffman.h"
#include <stdio.h>
#include <malloc.h>

struct char_list * generateOccurrences(char *path) {
    /*
     * Generates the list of character occurrences of a given text
     * Returns a char_list struct
     */
    FILE *fp;
    fp = fopen(path, "r");

    int character;
    int index = 0;
    struct char_list *res = malloc(sizeof(struct char_list));

    // Allocate an array of char_node with a size of 255
    res->node_list = malloc(255 * sizeof(struct char_node));
    res->size = 255;

    while (!feof(fp)) {
        character = fgetc(fp);
        struct char_node *node = getCharNodeByCharacter(res, character);

        if (node == NULL) {
            // Create node if character has no node
            struct char_node *new_node;
            new_node = malloc(sizeof(struct char_node));
            new_node->character = character;
            new_node->occurrences = 1;
            res->node_list[index] = *new_node;

            ++index;
            res->last_index = index;
        } else {
            // Increment character occurrence if character already have a node
            node->occurrences++;
        }
    }

    fclose(fp);
    return res;
}

struct char_node * getCharNodeByCharacter(struct char_list *char_list, int character) {
    /*
     * Returns the char_node corresponding to a given character in a list
     * Returns NULL if the character hasn't been found
     */
    struct char_node *current_node;

    for (int i = 0; i < char_list->last_index; ++i) {

        current_node = &char_list->node_list[i];
        if (current_node->character == character) {
            return current_node;
        }
    }

    return NULL;
}

void printOccurrenceList(struct char_list *char_list) {
    /*
     * Prints the occurrences list
     */
    for (int i = 0; i < char_list->last_index; ++i) {
        struct char_node current = char_list->node_list[i];
        printf("%c %i\n", current.character, current.occurrences);
    }
}

void sortCharList(struct char_list *char_list) {

}

void sortCharListByOcc(struct char_node *first_node) {

}

void sortCharListByASCIICode(struct char_node *first_node) {

}
