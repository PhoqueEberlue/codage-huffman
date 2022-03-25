#include "huffman.h"

int main() {
    struct huffman_data *huffman_data = applyHuffmanOnFile("../textes/textesimple.txt");
    generateFile(huffman_data, "../textes/textesimple.bin");
    return 0;
}
