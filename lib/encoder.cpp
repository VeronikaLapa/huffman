#include "encoder.h"
#include <iostream>
using namespace std;
encoder::encoder() {}

void encoder::add_to_freq(string str) {
    for (char ch : str) {
        freq.add_char(ch);
    }
}

bit_string encoder::encode(string str) {
    tree = huff_tree(freq);
    bit_string ans = tree.to_string();
    bit_string enc_string = encode_string(str);
    ans.concat(enc_string);
    ans.to_debug_string();
    return ans;
}

bit_string encoder::encode_string(string str) {
    bit_string ans;
    for (char ch : str) {
        ans.add_code(tree.get_code(ch));
    }
    return ans;
}

bit_string encoder::encode_small(std::string str) {
    add_to_freq(str);
    return encode(str);
}