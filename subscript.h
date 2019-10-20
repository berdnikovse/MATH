#pragma once
#include <algorithm>
#include <iostream>
#include "standard_error_handling.h"

#define MAX_STRING_SIZE 30

#define NULL_SUBSCRIPT cb((size_t)(-1), (size_t)(-1))

enum subscript_error {
	THE_STRING_IS_NOT_A_VALID_SUBSCRIPT = 1
};

const char *subscript_err_list[];

void catch_subscript_exception(subscript_error);

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