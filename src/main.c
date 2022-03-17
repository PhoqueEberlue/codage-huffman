
#include <malloc.h>
#include "huffman.h"

int main() {
    struct char_list *char_list = generateOccurrences("../textes/textesimple.txt");
    printCharList(char_list);
    return 0;
}
