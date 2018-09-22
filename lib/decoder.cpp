#include "decoder.h"
#include "file_exceptions.h"
decoder::decoder(){}

std::string decoder::decode(bit_string str) {
    size_t ind = 0;
    if (tree.is_empty()) {
        tree = huff_tree(str, ind);
    }
    return decode_string(str, ind);
}

std::string decoder::decode_string(bit_string& str, size_t ind) {
    std::string ans = "";
    while (ind < str.size()) {
        try {
            ans.push_back(tree.get_char(str, ind));
        } catch (bit_string_out_of_bounds& e) {
            throw corrupt_file();
        }
    }
    return ans;
}
