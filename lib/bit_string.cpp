#include "bit_string.h"
#include "file_exceptions.h"

bit_string::bit_string() : data(), last_char_length(0) {}

bit_string::bit_string(bit_code& code) : data(), last_char_length(0) {
    add_code(code);
}

void bit_string::add_code(bit_code code) {

    while (code.size() > 0) {
        add_bit(code.last_bit());
        code.erase_bit();
    }

/*
    unsigned long long value  = code.get_value();
    if (last_char_length == 0) {
        data.push_back(0);
    }
    while (value != 0) {
        data[data.size() - 1] = data[data.size() - 1] | (value & (255 - (1<< last_char_length - 1)));
        value = value >> (8 - last_char_length);
        data.push_back((1<< last_char_length - 1) & value);
    }
    last_char_length = (code.size() - last_char_length) % 8;
*/
 }

void bit_string::add_bit(bool bit) {
    char b = static_cast<char>(bit);
    if (last_char_length == CHAR_SIZE || data.empty()) {
        data.push_back(b);
        last_char_length = 1;
    } else {
        data[data.size() - 1] = data[data.size() - 1] + (b << last_char_length);
        ++last_char_length;
    }
}

void bit_string::erase_bit() {
    if (last_char_length > 0) {
        --last_char_length;
    } else {
        data.pop_back();
        last_char_length = CHAR_SIZE - 1;
    }
}

void bit_string::concat(bit_string& str) {
    for (size_t i = 0; i < str.size(); i++) {
        add_bit(str.get_bit(i));
    }
}

size_t bit_string::size() {
    if (!data.empty()) {
        return ((data.size() - 1) * CHAR_SIZE + last_char_length);
    } else {
        return 0;
    }
}

bool bit_string::get_bit(size_t i) {
    if (i >= size()) {
        throw bit_string_out_of_bounds();
    } else {
        size_t char_ind = i / CHAR_SIZE;
        size_t char_pos = i % CHAR_SIZE;
        return ((data[char_ind] & (1 << char_pos))!= 0);
    }
}

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

bit_string::bit_string(std::string str, int length) : data(std::move(str)), last_char_length(length) {}

std::string bit_string::to_string() {
    return data;
}
int bit_string::get_last_length() {
    return last_char_length;
}