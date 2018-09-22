#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <string>
#include "bit_string.h"
#include <fstream>

class file_writer {
public:
    file_writer(std::string& name);
    ~file_writer();
    void write_string(std::string&);
    void write_bit_string(bit_string&);
private:
    std::ofstream output_file;
};

#endif //FILE_WRITER_H
