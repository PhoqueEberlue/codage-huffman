#include <stdio.h>
#include <malloc.h>
#include "binary_tree.h"
#include "huffman.h"
#include "occurrence.h"

int main() {
    // Generating occurrences list

    struct char_list *char_list = generateOccurrences("../textes/textesimple.txt");
    //printOccurrenceList(char_list);

    sortCharListByOcc(char_list);
    //printf("trié par fréquence\n");
    //printOccurrenceList(char_list);

    sortCharListByASCIICode(char_list);
    //printf("trié par fréquence et code ascii\n");
    //printOccurrenceList(char_list);

    struct tree_node_list *tree_list = createLeaves(char_list);


    /*
    for (int i = 0; i < tree_node_list->size; ++i) {
        printf("%c %i\n", tree_node_list->node_list[i].character, tree_node_list->node_list[i].occurrences);
    }
    */


    struct tree_node *root = createTree(tree_list);
    // printf("%i\n", root->occurrences);

    printTree2(root, 0);

    int *depth = malloc(sizeof(int));
    *depth = 0;

    getDepth(depth, root, 0);
    printf("%i\n", *depth);


    char *code = malloc(*depth * sizeof(char));
    generateCode(char_list, root, code, 0);

    printOccurrenceList(char_list);
    return 0;
}
