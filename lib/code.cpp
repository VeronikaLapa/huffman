#include "code.h"
#include "bit_string.h"
bit_code::bit_code() : code(0), length(0) {}

//bit_code::bit_code(unsigned long long ncode, size_t nlength) : code(ncode), length(nlength) {}

bit_code::bit_code(char ch) :code(0), length(0){
    for (int i = 0; i < 8; i++) {
        add_bit(ch & 1);
        ch = ch >> 1;
    }
}

void bit_code::add_bit(bool bit) {
    //code += static_cast<int>(bit) << (length++);
    code = (code << 1) + static_cast<int>(bit);
    length++;
}

void bit_code::erase_bit() {
    --length;
    code = code >> 1;
}

size_t bit_code::size() {
    return length;
}

bool bit_code::last_bit() {
    //return code & (1 << (length - 1));
    return code & 1;
}
void bit_code::reverse() {
    bit_code ans;
    int s = size();
    for (int i = 0; i < s; i++) {
        ans.add_bit(code & 1);
        code = code >> 1;
    }
    code = ans.code;
    length = ans.length;
}