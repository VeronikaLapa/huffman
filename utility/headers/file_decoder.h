#ifndef FILE_DECODER_H
#define FILE_DECODER_H

#include "file_reader.h"
#include "file_writer.h"
#include "decoder.h"
class file_decoder
{
public:
    file_decoder(std::string in, std::string out);
    void decode_all();

private:
    file_reader input;
    file_writer output;
    decoder dec;
};

#endif //FILE_DECODER_H
