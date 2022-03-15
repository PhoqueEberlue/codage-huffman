//
// Created by andrewmhdb on 15/03/2022.
//

#ifndef CODAGE_HUFFMAN_HUFFMAN_H
#define CODAGE_HUFFMAN_HUFFMAN_H

struct char_node {
    struct char_node *next;
    int character;
    int occurrences;
};


void generateOccurrences(char *path);
struct char_node *getCharNodeByCharacter(struct char_node *first_node, int character);

#endif //CODAGE_HUFFMAN_HUFFMAN_H
