
#include "huffman.h"

int main() {
    struct char_node *first_node = generateOccurrences("../textes/textesimple.txt");
    printOccurrenceList(first_node);
    return 0;
}
