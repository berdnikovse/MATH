#pragma once
#include <algorithm>
#include <iostream>
#include "matrix_error_handling.h"
#include "standard_functions.h"


#ifndef SUBSCRIPT
#define SUBSCRIPT
#endif // !SUBSCRIPT

#define NULL_SUBSCRIPT cb((size_t)(-1), (size_t)(-1))

class subscript
{
public:
	size_t row_number;
	size_t column_number;

	subscript(size_t = 0, size_t = 0);

	friend std::istream& operator >> (std::istream &, subscript &);
	friend std::ostream& operator << (std::ostream &, subscript);

	subscript reflect();
};

subscript cb(size_t, size_t);

subscript string_to_subscript(const unsigned char str[]);

bool operator ==(subscript, subscript);
bool operator !=(subscript, subscript);
bool operator <(subscript, subscript);
bool operator <=(subscript, subscript);

subscript operator -(subscript, subscript);
subscript operator +(subscript, subscript);

bool string_is_subscript(const unsigned char str[]);