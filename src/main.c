#include <stdio.h>
#include <malloc.h>
#include "binary_tree.h"
#include "huffman.h"

int main() {
    // Generating occurrences list

    struct char_list *char_list = generateOccurrences("../textes/alice.txt");
    //printOccurrenceList(char_list);

    sortCharListByOcc(char_list);
    //printf("trié par fréquence\n");
    //printOccurrenceList(char_list);

    sortCharListByASCIICode(char_list);
    //printf("trié par fréquence et code ascii\n");
    //printOccurrenceList(char_list);

    struct tree_list *tree_list = createLeaves(char_list);


    /*
    for (int i = 0; i < tree_list->size; ++i) {
        printf("%c %i\n", tree_list->node_list[i].character, tree_list->node_list[i].occurrences);
    }
    */


    struct tree_node *root = createTree(tree_list);
    // printf("%i\n", root->occurrences);

    printTree2(root, 0);
    return 0;
}
