#ifndef CHAR_COUNTER_H
#define CHAR_COUNTER_H

#include <vector>

const unsigned int MAX_CHAR = 256;


class char_counter{
public:
    char_counter();
    void add_char(unsigned char ch);
    unsigned long long char_amt(unsigned char ch);
private:
    unsigned long long data[256];
};
#endif //CHAR_COUNTER_H
