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

std::string file_reader::get_string() {
    if (input_file.eof()) {
        return "";
    }
    int BUFFER_SIZE = 1024;
    char *buffer = new char[BUFFER_SIZE];
    input_file.read(buffer, BUFFER_SIZE);
    std::string ans(buffer, input_file.gcount());
    delete[] buffer;
    return ans;

}

bit_string file_reader::get_bit_string() {
    char size_buffer[3] = {0, 0, 0};
    input_file.read(size_buffer, 3);
    if (input_file.gcount() != 3) {
        return bit_string();
    }
    size_t s = (static_cast<unsigned char>(size_buffer[0])<< 8) + static_cast<unsigned char>(size_buffer[1]);
    char *buffer = new char[s];
    input_file.read(buffer, s);
    bit_string ans(string(buffer, input_file.gcount()), static_cast<unsigned char>(size_buffer[2]));
    delete[] buffer;
    return ans;
}

void file_reader::move_to_begin() {
    input_file.clear();
    input_file.seekg(input_file.beg);
}