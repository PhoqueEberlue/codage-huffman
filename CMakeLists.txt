cmake_minimum_required(VERSION 3.22)
project(codage_huffman C)

set(CMAKE_C_STANDARD 99)

add_executable(codage_huffman src/main.c src/huffman.c src/huffman.h)
