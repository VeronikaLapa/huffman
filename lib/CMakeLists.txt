cmake_minimum_required(VERSION 2.8)

project(HUFFMAN_LIB)


include_directories(${HUFFMAN_LIB_SOURCE_DIR}/headers)

set(LIB_HEADERS headers/code.h headers/bit_string.h
        headers/tree.h headers/char_counter.h
        headers/encoder.h headers/decoder.h
        headers/file_exceptions.h
        )

set(LIB_SOURCES code.cpp bit_string.cpp
        tree.cpp char_counter.cpp
        encoder.cpp decoder.cpp)

add_library(huf_lib ${LIB_HEADERS} ${LIB_SOURCES})