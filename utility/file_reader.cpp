#include "file_reader.h"
#include "file_exceptions.h"

using namespace std;

file_reader::file_reader(std::string name) : input_file(name, std::ifstream::binary) {
    if (!input_file) {
        throw file_exc();
    }
}

file_reader::~file_reader() {
    input_file.close();
}

buffer::buffer(size_t n): buf(new char[n]){};
buffer::~buffer() {
    delete[](buf);
}
char* buffer::get() {
        return buf;
};

std::string file_reader::get_string() {
    if (input_file.eof()) {
        return "";
    }
    size_t BUFFER_SIZE = 1024;
    buffer b = buffer(BUFFER_SIZE);
    input_file.read(b.get(), BUFFER_SIZE);
    std::string ans(b.get(), input_file.gcount());

    return ans;

}

bit_string file_reader::get_bit_string() {
    char size_buffer[3] = {0, 0, 0};
    input_file.read(size_buffer, 3);
    if (input_file.gcount() != 3) {
        return bit_string();
    }
    size_t s = (static_cast<unsigned char>(size_buffer[0])<< 8) + static_cast<unsigned char>(size_buffer[1]);
    buffer b = buffer(s);
    input_file.read(b.get(), s);
    bit_string ans(string(b.get(), input_file.gcount()), static_cast<unsigned char>(size_buffer[2]));
    return ans;
}

void file_reader::move_to_begin() {
    input_file.clear();
    input_file.seekg(input_file.beg);
}