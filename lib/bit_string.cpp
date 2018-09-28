#include <bit_string.h>
#include "bit_string.h"
#include "file_exceptions.h"


bit_string::bit_string() : data(1, 0), last_char_length(0) {};

bit_string::bit_string(bit_code &code) : data(1, code.get_value()), last_char_length(code.size()) {};

bit_string::bit_string(std::string str, int last_ch) : last_char_length(last_ch) {
    for (int i = 0; i < str.size(); i += 8) {
        uint64_t el = 0;
        for (int j = 0; j < 7; j++) {
            if (i + j < str.size()) {
                el += static_cast<unsigned char>(str[i + j]);
            }
            el <<= 8;
        }
        el += static_cast<unsigned char>(str[i + 7]);
        data.push_back(el);
    }
}

void bit_string::add_code(bit_code code) {
    if (code.size() + last_char_length < EL_SIZE) {
        data[data.size() - 1] += code.get_value() << last_char_length;
        last_char_length += code.size();
    } else if (code.size() + last_char_length == EL_SIZE) {
        data[data.size() - 1] += code.get_value() << last_char_length;
        data.push_back(0);
        last_char_length = 0;
    } else {
        data[data.size() - 1] += code.get_value() << last_char_length;
        data.push_back(code.get_value() >> (EL_SIZE - last_char_length));
        last_char_length = code.size() - (EL_SIZE - last_char_length);
    }
}

void bit_string::add_bit(bool bit) {
    uint64_t b = static_cast<uint64_t>(bit);
    data[data.size() - 1] = data[data.size() - 1] + (b << last_char_length);
    ++last_char_length;
    if (last_char_length == EL_SIZE) {
        data.push_back(0);
        last_char_length = 0;
    }
}

void bit_string::concat(bit_string &str) {
    for (int i = 0; i < str.data.size() - 1; i++) {
        add_code(bit_code(str.data[i], 64));
    }
    add_code(bit_code(str.data[str.data.size() - 1], str.last_char_length));
}

bool bit_string::get_bit(size_t i) {
    if (i >= size()) {
        throw bit_string_out_of_bounds();
    } else {
        size_t char_ind = i / EL_SIZE;
        size_t char_pos = i % EL_SIZE;
        return ((data[char_ind] & ((unsigned long long)1 << char_pos)) != 0);
    }
}

size_t bit_string::size() {
    return ((data.size() - 1) * EL_SIZE + last_char_length);
}

std::string bit_string::to_string() {
    std::string ans = "";
    for (uint64_t el : data) {
        uint64_t mask = 255;
        for (int i = 56; i > 0; i -= 8) {
            ans.push_back((unsigned char)((el & (mask << i)) >> i));
        }
        ans.push_back(el & mask);
    }
    return ans;
}

int bit_string::get_last_length() { return last_char_length; }
/*
std::string bit_string::to_debug_string() {
    std::string ans;
    for (size_t i = 0; i < size(); i++) {
        if (get_bit(i)) {
            ans.push_back('1');
        } else {
            ans.push_back('0');
        }

    }
    return ans;
}
*/