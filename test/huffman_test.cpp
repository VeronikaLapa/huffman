#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <gtest/gtest.h>
#include "encoder.h"
#include "decoder.h"
#include "../utility/headers/file_decoder.h"
#include "../utility/headers/file_encoder.h"
#include <iostream>
TEST(correctness, easy)
{
    encoder en;
    decoder de;
    std::string str = "azazaza";
    bit_string res = en.encode_small(str);
    EXPECT_EQ(str, de.decode(res));
}
TEST(correctness, huffman)
{
    encoder en;
    decoder de;
    std::string str = "huffman";
    bit_string res = en.encode_small(str);
    EXPECT_EQ(str, de.decode(res));
}
TEST(correctness, big_text)
{
    encoder en;
    decoder de;
    std::string str = "Huffman coding uses a specific method for choosing the representation for each symbol, resulting in a prefix code (sometimes called prefix-free codes, that is, the bit string representing some particular symbol is never a prefix of the bit string representing any other symbol). Huffman coding is such a widespread method for creating prefix codes that the term Huffman code is widely used as a synonym for \"prefix code\" even when such a code is not produced by Huffman's algorithm.";
    bit_string res = en.encode_small(str);
    EXPECT_EQ(str, de.decode(res));
}
TEST(correctness, very_big_text)
{
    encoder en;
    decoder de;
    std::string str = "TEST(correctness, big_text)\n"
                      "{\n"
                      "    encoder en;\n"
                      "    decoder de;\n"
                      "    std::string str = \"Huffman coding uses a specific method for choosing the representation for each symbol, resulting in a prefix code (sometimes called prefix-free codes, that is, the bit string representing some particular symbol is never a prefix of the bit string representing any other symbol). Huffman coding is such a widespread method for creating prefix codes that the term Huffman code is widely used as a synonym for \\\"prefix code\\\" even when such a code is not produced by Huffman's algorithm.\";\n"
                      "    bit_string res = en.encode_small(str);\n"
                      "    EXPECT_EQ(str, de.decode(res));\n"
                      "}";
    bit_string res = en.encode_small(str);
    EXPECT_EQ(str, de.decode(res));
}
TEST(correctness, allch)
{
    encoder en;
    decoder de;
    std::string str = "";
    for (unsigned char i  = 0; i < 128; i++) {
        str.push_back(i);
    }
    bit_string res = en.encode_small(str);
    EXPECT_EQ(str, de.decode(res));
}
TEST(correctness, empty)
{
    encoder en;
    decoder de;
    std::string str = "";
    bit_string res = en.encode_small(str);
    EXPECT_EQ(str, de.decode(res));
}
TEST(correctness, one_symbol)
{
    encoder en;
    decoder de;
    std::string str = "";
    for (int i = 0; i < 100; i++) {
        str.push_back('a');
        EXPECT_EQ(str, de.decode(en.encode_small(str)));
    }
}

bool file_comp(std::string in, std::string out) {
    std::ifstream f1(in, std::ifstream::binary);
    std::ifstream f2(out, std::ifstream::binary);
    if (f1.fail() || f2.fail()) {
        std::cout << 1;
        return false; //file problem
    }
    char* buffer1 = new char[100];
    char* buffer2 = new char[100];
    while(!f1.eof() && !f2.eof()) {
        f1.read(buffer1, 100);
        f2.read(buffer2, 100);
        if (memcmp(buffer1, buffer2, f1.gcount()) != 0) {
            f1.close();
            f2.close();
            delete [] buffer1;
            delete [] buffer2;
            std::cout << 2;
            return false;
        }
    }
    if (!f1.eof() || !f2.eof()) {
        f1.close();
        f2.close();
        delete [] buffer1;
        delete [] buffer2;
        std::cout << 3;
        return false;
    }
    f1.close();
    f2.close();
    delete [] buffer1;
    delete [] buffer2;
    return true;
}

TEST(correctness, easy_file) {
    {
        file_encoder enc("1.in", "1.out");
        enc.encode_all();
    }
    {
        file_decoder dec("1.out", "1.res");
        dec.decode_all();
    }
    EXPECT_TRUE(file_comp("1.in", "1.res"));
}

TEST(correctness, easy_file2) {
    {
        file_encoder enc("2.jpg", "2.out");
        enc.encode_all();
    }
    {
        file_decoder dec("2.out", "2.res");
        dec.decode_all();
    }
    EXPECT_TRUE(file_comp("2.jpg", "2.res"));
}

TEST(correctness, big_file) {
    {
        file_encoder enc("2.txt", "2.out");
        enc.encode_all();
    }
    {
        file_decoder dec("2.out", "2.res");
        dec.decode_all();
    }
    EXPECT_TRUE(file_comp("2.txt", "2.res"));
}

TEST(correctness, big_file2) {
    {
        file_encoder enc("3.pdf", "3.out");
        enc.encode_all();
    }
    {
        file_decoder dec("3.out", "3.res");
        dec.decode_all();
    }
    EXPECT_TRUE(file_comp("3.pdf", "3.res"));
}


TEST(correctness, big_file4) {
    {
        file_encoder enc("4.txt", "4.out");
        enc.encode_all();
    }
    {
        file_decoder dec("4.out", "4.res");
        dec.decode_all();
    }
    EXPECT_TRUE(file_comp("4.txt", "4.res"));
}

TEST(correctness, empty_file) {
    {
        file_encoder enc("empty.in", "empty.out");
        enc.encode_all();
    }
    {
        file_decoder dec("empty.out", "empty.res");
        dec.decode_all();
    }
    EXPECT_TRUE(file_comp("empty.in", "empty.res"));
}


