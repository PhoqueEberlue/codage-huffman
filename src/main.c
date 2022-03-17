
#include <malloc.h>
#include "huffman.h"

int main() {
   // Generating occurrence list
    struct char_list *char_list = generateOccurrences("../textes/textesimple.txt");
    printOccurrenceList(char_list);
    return 0;
}
