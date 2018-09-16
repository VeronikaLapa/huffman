#include "file_decoder.h"

file_decoder::file_decoder(std::string in, std::string out): input(in), output(out), dec(){}

void file_decoder::decode_all() {
    bit_string str = input.get_bit_string();
    dec.decode(str);
    std::string res = "a";
    //output.write_string(res);
    while (res != "") {
        str = input.get_bit_string();
        res = dec.decode_string(str);
        output.write_string(res);
    }
}