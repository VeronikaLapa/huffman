#ifndef BIT_STRING_H
#define BIT_STRING_H

#include <vector>
#include "string"
#include "code.h"
const unsigned int CHAR_SIZE = 8;
class bit_string{
public:
    bit_string();
    bit_string(bit_code& code);
    bit_string(std::string, int last_char_length);
    void add_code(bit_code code);
    void add_bit(bool bit);
    void erase_bit();
    void concat(bit_string& str);
    bool get_bit(size_t i);
    size_t size();
    std::string to_debug_string();
    std::string to_string();
    int get_last_length();
private:
    std::string data;
    int last_char_length;
};
#endif //BIT_STRING_H
