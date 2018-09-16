#ifndef ENCODER_H
#define ENCODER_H

#include "tree.h"
#include "char_counter.h"
class encoder {
public:
    encoder();

    bit_string encode_small(std::string);
    bit_string encode(std::string);

    bit_string encode_string(std::string);

    void add_to_freq(std::string);

private:
    char_counter freq;
    huff_tree tree;
};

#endif //ENCODER_H
