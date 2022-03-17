//
// Created by andrewmhdb on 15/03/2022.
//

#include "huffman.h"
#include <stdio.h>
#include <malloc.h>

struct char_list * generateOccurrences(char *path) {
    FILE *fp;
    fp = fopen(path, "r");

    struct char_node *first_node;
    struct char_node *last_node;
    last_node = NULL;

    int character;
    while (!feof(fp)) {
        character = fgetc(fp);

        if (last_node == NULL) {
            // Create previous node if not exists
            first_node = malloc(sizeof(struct char_node));
            first_node->next = NULL;
            first_node->character = character;
            first_node->occurrences = 1;
            last_node = first_node;
        } else {
            struct char_node *node = getCharNodeByCharacter(first_node, character);

            if (node == NULL) {
                // Create node if character has no node
                struct char_node *new_node;
                new_node = malloc(sizeof(struct char_node));
                new_node->next = NULL;
                new_node->character = character;
                new_node->occurrences = 1;

                // add the pointer of the new node to the previous node
                last_node->next = new_node;
                // the previous node is now the new node
                last_node = new_node;

            } else {
                // Increment character occurrence if character already have a node
                node->occurrences++;
            }
        }


    }
    fclose(fp);

    struct char_list *char_list = malloc(sizeof (struct char_list));
    char_list->first_node = first_node;
    char_list->last_node = last_node;

    return char_list;
}

struct char_node * getCharNodeByCharacter(struct char_node *first_node, int character) {
    struct char_node *current_node = first_node;

    while (current_node->next != NULL) {
        if (current_node->character == character) {
            return current_node;
        }
        current_node = current_node->next;
    }

    return NULL;
}

void printCharList(struct char_list *char_list) {
    struct char_node *current_node = char_list->first_node;
    while (current_node->next != NULL) {
        printf("%c %i\n", current_node->character, current_node->occurrences);
        current_node = current_node->next;
    }
}

void sortCharList(struct char_list *char_list) {

}

void sortCharListByOcc(struct char_node *first_node) {

}

void sortCharListByASCIICode(struct char_node *first_node) {

}