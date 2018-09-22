#ifndef DECODER_H
#define DECODER_H

#include "tree.h"
#include "code.h"

class decoder {
public:
    decoder();
    std::string decode(bit_string);
private:
    std::string decode_string(bit_string&, size_t ind = 0);
    huff_tree tree;
};

#endif //DECODER_H
