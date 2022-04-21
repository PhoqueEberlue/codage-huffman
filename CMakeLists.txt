cmake_minimum_required(VERSION 3.22)
project(codage_huffman C)

set(CMAKE_C_STANDARD 99)

# Huffman files
set(huffman_files
        src/huffman.c
        src/huffman.h
        src/binary_tree.c
        src/binary_tree.h
        src/occurrence.c
        src/occurrence.h
        )

# Tests
set(tests_files
        tests/test_occurrence.c
        tests/test_occurrence.h
        )

add_executable(codage_huffman
        src/main.c
        ${huffman_files}
        )

add_executable(test_codage_huffman
        tests/main.c
        ${huffman_files}
        ${tests_files}
        )
