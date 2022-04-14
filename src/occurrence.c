//
// Created by andrewmhdb on 19/03/2022.
//

#include "occurrence.h"
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

struct char_list *generateOccurrences(char *path) {
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
            res->node_list[index].character = character;
            res->node_list[index].occurrences = 1;
            res->node_list[index].code = NULL;

            res->last_index = index;
            ++index;
        } else {
            // Increment character occurrences if character already have a node
            node->occurrences++;
        }
    }

    fclose(fp);
    return res;
}

struct char_node *getCharNodeByCharacter(struct char_list *char_list, int character) {
    /*
     * Returns the char_node corresponding to a given character in a list
     * Returns NULL if the character hasn't been found
     */
    struct char_node *current_node;

    // last index + 1 because the index get updated after in generateOccurrences
    for (int i = 0; i < char_list->last_index + 1; ++i) {

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
    printf("Character | Character ASCII code | occurrences in the text");

    for (int i = 0; i < char_list->last_index; ++i) {
        struct char_node *current = &char_list->node_list[i];

        if (i == 0) {
            if (current->code != NULL) {
                printf(" | huffman code");
            }
            printf("\n");
        }

        if (current->character < 100) {
            printf("    %c     |          %i          |           %i             ", current->character,
                   current->character, current->occurrences);
        } else {
            printf("    %c     |          %i         |           %i             ", current->character,
                   current->character, current->occurrences);
        }

        if (current->code != NULL) {
            printf("|     ");
            for (int j = 0; j < current->code_size; ++j) {
                printf("%i", current->code[j]);
            }
        }

        printf("\n");
    }
}

void sortCharList(struct char_list *char_list) {
    sortCharListByOcc(char_list);
    sortCharListByASCIICode(char_list);
}

void sortCharListByOcc(struct char_list *char_list) {
    /*
     * Simple implementation of bubble sort
     */
    bool has_changed = true;
    struct char_node *node_list = char_list->node_list;

    // While at least one change was made through an iteration of the list
    while (has_changed) {
        has_changed = false;

        // iterate the list
        for (int i = 0; i < char_list->last_index - 1; ++i) {

            // if i < i + 1, swap two values
            if (node_list[i].occurrences < node_list[i + 1].occurrences) {
                struct char_node tmp = node_list[i];
                node_list[i] = node_list[i + 1];
                node_list[i + 1] = tmp;
                has_changed = true;
            }
        }
    }
}


void sortCharListByASCIICode(struct char_list *char_list) {
    /*
     * Simple implementation of bubble sort
     */
    bool has_changed = true;
    struct char_node *node_list = char_list->node_list;

    // While at least one change was made through an iteration of the list
    while (has_changed) {
        has_changed = false;

        // iterate the list
        for (int i = 0; i < char_list->last_index - 1; ++i) {

            // if char > char + 1 and occ == occ + 1, swap two values
            if (node_list[i].character > node_list[i + 1].character &&
                node_list[i].occurrences == node_list[i + 1].occurrences) {

                struct char_node tmp = node_list[i];
                node_list[i] = node_list[i + 1];
                node_list[i + 1] = tmp;
                has_changed = true;
            }
        }
    }
}

void freeCharNode(struct char_node *char_node) {
    free(char_node->code);
    free(char_node);
}

void freeCharList(struct char_list *char_list) {
    freeCharNode(char_list->node_list);
    free(char_list);
}
