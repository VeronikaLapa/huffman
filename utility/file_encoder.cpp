#include "file_encoder.h"
void file_encoder::encode_all() {
    std::string str = "a";
    bit_string res = enc.encode("");
    output.write_bit_string(res);
    while (str != "") {
        str = input.get_string();
        bit_string res = enc.encode_string(str);
        output.write_bit_string(res);
    }
}

file_encoder::file_encoder(std::string in, std::string out): input(in), output(out) {
    count_char();
}

void file_encoder::count_char() {
    std::string str = input.get_string();
    while (str != "") {
        enc.add_to_freq(str);
        str = input.get_string();
    }
    input.move_to_begin();
}