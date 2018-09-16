cmake_minimum_required(VERSION 2.8)

project(HUFFMAN_TESTS)

include_directories(${HUFFMAN_LIB_SOURCE_DIR}/headers
					${HUFFMAN_TESTS_SOURCE_DIR}
					${HUFFMAN_UTILITY_SOURCE_DIR}/headers
					${HUFFMAN_UTILITY_SOURCE_DIR})
					
set(TEST_FILES gtest/gtest_main.cc
        gtest/gtest-all.cc
        gtest/gtest.h
        huffman_test.cpp)

add_executable(huffman_tests ${TEST_FILES})
target_link_libraries(huffman_tests huf_lib)
target_link_libraries(huffman_tests huf_util)

