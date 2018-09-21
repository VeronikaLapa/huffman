#include "file_writer.h"
#include "file_exceptions.h"
using namespace std;

file_writer::file_writer(std::string name) :output_file(name, std::ofstream::binary){
    if (!output_file) {
        throw file_exc();
    }
}
file_writer::~file_writer() {
    output_file.close();
}

void file_writer::write_string(std::string& str) {
    output_file.write(str.c_str(), str.size());
}

void file_writer::write_bit_string(bit_string& str) {
    if (str.size() > 0) {
        std::string data = str.to_string();
        std::string size_str;
        size_str.push_back(data.size() >> 8);
        size_str.push_back(data.size() & 255);
        size_str.push_back(static_cast<unsigned char>(str.get_last_length()));
        output_file.write(size_str.c_str(), 3);
        output_file.write(data.c_str(), data.size());
    }
}