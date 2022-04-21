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
    struct char_list *res = malloc(sizeof(struct char_list));

    // Allocate an array of char_elem with a size of 255
    res->char_elem_p = malloc(255 * sizeof(struct char_elem));
    res->last_index = -1;
    res->size = 255;

    while (!feof(fp)) {
        character = fgetc(fp);
        if (character == -1) {
            break;
        }

        struct char_elem *current_char = getCharNodeByCharacter(res, character);

        // if the current character isn't in the list
        if (current_char == NULL) {
            // create a new char_elem and adds it to the list
            res->last_index++;
            res->char_elem_p[res->last_index].character = character;
            res->char_elem_p[res->last_index].occurrences = 1;
            res->char_elem_p[res->last_index].code = NULL;
        } else {
            // Increment character occurrences if character already have a current_char
            current_char->occurrences++;
        }
    }

    fclose(fp);
    return res;
}

struct char_elem *getCharNodeByCharacter(struct char_list *char_list, int character) {
    /*
     * Returns the char_elem corresponding to a given character in a list
     * Returns NULL if the character hasn't been found
     */
    struct char_elem *current_char;

    for (int i = 0; i <= char_list->last_index; ++i) {
        current_char = &char_list->char_elem_p[i];
        // if the curent char is equal to the given char
        if (current_char->character == character) {
            return current_char;
        }
    }

    return NULL;
}

void printOccurrenceList(struct char_list *char_list) {
    /*
     * Prints the occurrences list
     */
    printf("Character | Character ASCII code | occurrences in the text");

    for (int i = 0; i <= char_list->last_index; ++i) {
        struct char_elem *current = &char_list->char_elem_p[i];

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

void sortCharListByOcc(struct char_list *char_list, bool asc) {
    /*
     * Sorts the char list by occurrences
     * Simple implementation of the bubble sort
     */
    bool has_changed = true;
    struct char_elem *char_elem_p = char_list->char_elem_p;

    // While at least one change was made through an iteration of the list
    while (has_changed) {
        has_changed = false;

        // iterate the list
        for (int i = 0; i < char_list->last_index; ++i) {

            bool condition;
            // if asc, sort by ascending values
            if (asc) {
                condition = char_elem_p[i].occurrences > char_elem_p[i + 1].occurrences;
            }
                // else, sort by descending values
            else {
                condition = char_elem_p[i].occurrences < char_elem_p[i + 1].occurrences;
            }
            if (condition) {
                // swap i and i + 1
                struct char_elem tmp = char_elem_p[i];
                char_elem_p[i] = char_elem_p[i + 1];
                char_elem_p[i + 1] = tmp;
                has_changed = true;
            }
        }
    }
}

void sortCharListByASCIICode(struct char_list *char_list, bool asc) {
    /*
     * Sorts the char list by ASCII code without changing the frequency order
     * Simple implementation of bubble sort
     */
    bool has_changed = true;
    struct char_elem *node_list = char_list->char_elem_p;

    // While at least one change was made through an iteration of the list
    while (has_changed) {
        has_changed = false;

        // iterate the list
        for (int i = 0; i < char_list->last_index; ++i) {

            bool condition;
            // if asc, sort by ascending values
            if (asc) {
                condition = node_list[i].character > node_list[i + 1].character &&
                            node_list[i].occurrences == node_list[i + 1].occurrences;
            }
                // else, sort by descending values
            else {
                condition = node_list[i].character < node_list[i + 1].character &&
                            node_list[i].occurrences == node_list[i + 1].occurrences;
            }
            if (condition) {
                // swap i and i + 1
                struct char_elem tmp = node_list[i];
                node_list[i] = node_list[i + 1];
                node_list[i + 1] = tmp;
                has_changed = true;
            }
        }
    }
}

void freeCharElems(struct char_elem *char_elem_p) {
    free(char_elem_p->code);
    free(char_elem_p);
}

void freeCharList(struct char_list *char_list) {
    freeCharElems(char_list->char_elem_p);
    free(char_list);
}
