#include "huffman.h"

int main() {
    struct huffman_data *huffman_data = applyHuffmanOnFile("../textes/alice.txt");
    generateFile(huffman_data, "../textes/alice.bin");
    printHuffmanData(huffman_data);
    freeHuffman(huffman_data);
    return 0;
}
