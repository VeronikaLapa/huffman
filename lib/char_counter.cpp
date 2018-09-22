#include "char_counter.h"

char_counter::char_counter() {
    //data = std::vector<unsigned long long>(256, 0);
    for (size_t i = 0; i < 256; i++) {
        data[i] = 0;
    }
}

void char_counter::add_char(unsigned char ch) {
    ++data[ch];
}

unsigned long long char_counter::char_amt(unsigned char ch) {
    return data[ch];
}