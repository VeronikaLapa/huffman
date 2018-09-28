#ifndef BIT_CODE_H
#define BIT_CODE_H

#include <cstddef>

struct bit_code {
public:
	bit_code();
	bit_code(unsigned char ch);
	unsigned long long get_value() {return code;}
	bit_code(unsigned long long c, size_t  l): code(c), length(l){};
	void add_bit(bool bit);
	void erase_bit();
	size_t size();
	bool last_bit();
	void reverse();
private:
	unsigned long long code;
	size_t length;
};
#endif