
#include <malloc.h>
#include "huffman.h"

int main() {
    // Generating occurrence list

    struct char_list *char_list = generateOccurrences("../textes/textesimple.txt");
    printOccurrenceList(char_list);

    sortCharListByOcc(char_list);
    printf("trié par fréquence\n");
    printOccurrenceList(char_list);

    sortCharListByASCIICode(char_list);
    printf("trié par fréquence et code ascii\n");
    printOccurrenceList(char_list);
    return 0;
}
