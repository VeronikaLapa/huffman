#include "code.h"
#include "bit_string.h"
bit_code::bit_code() : code(0), length(0) {}

bit_code::bit_code(char ch) :code(ch), length(8){}

void bit_code::add_bit(bool bit) {
    code += static_cast<int>(bit) << (length++);
}

void bit_code::erase_bit() {
    --length;
}

size_t bit_code::size() {
    return length;
}

bool bit_code::last_bit() {
    return code & (1 << (length - 1));
}

void bit_code::reverse() {
    bit_code ans;
    bit_code crnt = *this;
    int s = size();
    for (int i = 0; i < s; i++) {
        ans.add_bit(crnt.last_bit());
        crnt.erase_bit();
    }
    code = ans.code;
    length = ans.length;
}
