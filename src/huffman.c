//
// Created by andrewmhdb on 15/03/2022.
//

#include "huffman.h"
#include <stdio.h>
#include <malloc.h>

void generateOccurrences(char *path) {
    FILE *fp;
    fp = fopen(path, "r");
    int character;

    struct char_node *first_node;
    struct char_node *last_node;
    last_node = NULL;

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

        printf("%c", character);
    }
    fclose(fp);
}

struct char_node *getCharNodeByCharacter(struct char_node *first_node, int character) {
    struct char_node *current_node = first_node;

    while (current_node->next != NULL) {
        if (first_node->character == character) {
            return current_node;
        }
        current_node = current_node->next;
    }

    printf("Le char %c n'a pas été trouvé\n", character);
    return NULL;
}