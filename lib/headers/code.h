#ifndef BIT_CODE_H
#define BIT_CODE_H

#include <cstddef>

struct bit_code {
public:
	bit_code();
	bit_code(char ch);
//	bit_code(unsigned long long code, size_t  length);
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