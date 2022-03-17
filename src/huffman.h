//
// Created by andrewmhdb on 15/03/2022.
//

#ifndef CODAGE_HUFFMAN_HUFFMAN_H
#define CODAGE_HUFFMAN_HUFFMAN_H

struct char_list {
    struct char_node *first_node;
    struct char_node *last_node;
};

struct char_node {
    struct char_node *next;
    int character;
    int occurrences;
};


struct char_list * generateOccurrences(char *path);
struct char_node * getCharNodeByCharacter(struct char_node *first_node, int character);
void printCharList(struct char_list *char_list);
void sortCharList(struct char_list *char_list);

#endif //CODAGE_HUFFMAN_HUFFMAN_H
