//
// Created by andrewmhdb on 19/03/2022.
//

#ifndef CODAGE_HUFFMAN_OCCURRENCE_H
#define CODAGE_HUFFMAN_OCCURRENCE_H

#include <stdbool.h>

// List of char node
struct char_list {
    struct char_elem *char_elem_p;
    int last_index;
    int size;
};

// A char and its occurrences
struct char_elem {
    int character;
    int occurrences;
    char *code;
    int code_size;
};


struct char_list *generateOccurrences(char *path);

struct char_elem *getCharNodeByCharacter(struct char_list *char_list, int character);

void printOccurrenceList(struct char_list *char_list);

void sortCharListByOcc(struct char_list *char_list, bool asc);

void sortCharListByASCIICode(struct char_list *char_list, bool asc);

void freeCharList(struct char_list *char_list);

#endif //CODAGE_HUFFMAN_OCCURRENCE_H
