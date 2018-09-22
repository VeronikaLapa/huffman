#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include "bit_string.h"
#include <fstream>

class file_reader {
public:
    file_reader(std::string& name);
    ~file_reader();
    std::string get_string();
    bit_string get_bit_string();
    void move_to_begin();
    size_t BUFFER_SIZE = 1024;
private:
    std::ifstream input_file;
    char buffer[2048];
};
#endif //FILE_READER_H
