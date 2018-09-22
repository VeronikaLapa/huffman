
#ifndef FILE_EXCEPTIONS_H
#define FILE_EXCEPTIONS_H
#include <exception>

class corrupt_file: public std::exception
{
public: virtual const char* what() const throw() {
        return "File was corrupted";
    }
};

class bad_operation: public std::exception
{
public: virtual const char* what() const throw() {
        return "tree was already built";
    }
};

class bit_string_out_of_bounds: public std::exception
{
public:    virtual const char* what() const throw() {
        return "Bit string out of bounds";
    }
};
class file_exc: public std::exception
{
public:    virtual const char* what() const throw() {
        return "File couldn't been opened";
    }
};
#endif //HUFFMAN_FILE_EXCEPTIONS_H
