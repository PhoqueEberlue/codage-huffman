//
// Created by andrewmhdb on 19/03/2022.
//

#ifndef CODAGE_HUFFMAN_OCCURRENCE_H
#define CODAGE_HUFFMAN_OCCURRENCE_H

// List of char node
struct char_list {
    struct char_node *node_list;
    int last_index;
    int size;
};

// A char and its occurrences
struct char_node {
    int character;
    int occurrences;
    char *code;
    int code_size;
};


struct char_list *generateOccurrences(char *path);

struct char_node *getCharNodeByCharacter(struct char_list *char_list, int character);

void printOccurrenceList(struct char_list *char_list);

void sortCharList(struct char_list *char_list);

void sortCharListByOcc(struct char_list *char_list);

void sortCharListByASCIICode(struct char_list *char_list);

#endif //CODAGE_HUFFMAN_OCCURRENCE_H
