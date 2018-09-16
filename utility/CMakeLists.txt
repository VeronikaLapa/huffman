cmake_minimum_required(VERSION 2.8)

project(HUFFMAN_UTILITY)

include_directories(${HUFFMAN_LIB_SOURCE_DIR}/headers ${HUFFMAN_UTILITY_SOURCE_DIR}/headers)

set(UTILITY_HEADERS headers/file_writer.h headers/file_reader.h
        headers/file_encoder.h headers/file_decoder.h headers/main.h
        )

set(UTILITY_SOURCES main.cpp file_writer.cpp file_reader.cpp
        file_encoder.cpp file_decoder.cpp)

add_executable(huffman_utility ${UTILITY_SOURCES})

add_library(huf_util ${UTILITY_HEADERS} ${UTILITY_SOURCES})
target_link_libraries(huffman_utility huf_lib)