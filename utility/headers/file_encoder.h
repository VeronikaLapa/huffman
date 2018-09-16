#ifndef FILE_ENCODER_H
#define FILE_ENCODER_H
#include "file_reader.h"
#include "file_writer.h"
#include "encoder.h"

class file_encoder
{
public:
    file_encoder(std::string in, std::string out);
    void encode_all();

private:
    void count_char();
    file_reader input;
    file_writer output;
    encoder enc;
};
#endif //FILE_ENCODER_H
