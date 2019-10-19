#pragma once
#include <algorithm>
#include <iostream>

#define STRING_SIZE 30

#define NULL_SUBSCRIPT cb((size_t)(-1), (size_t)(-1))

class subscript
{
public:
	size_t row_number;
	size_t column_number;

	subscript(size_t = 0, size_t = 0);

	friend std::istream& operator >> (std::istream &input, subscript &new_subscript);
	friend std::ostream& operator << (std::ostream &output, subscript to_be_printed);

	subscript reflect();
};

subscript cb(size_t, size_t);

subscript string_to_subscript(unsigned char str[]);

bool operator ==(subscript, subscript);
bool operator !=(subscript, subscript);
bool operator <(subscript, subscript);
bool operator <=(subscript, subscript);

subscript operator -(subscript, subscript);
subscript operator +(subscript, subscript);