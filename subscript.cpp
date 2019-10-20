#pragma once
#include <iostream>
#include "subscript.h"

subscript::subscript(size_t i, size_t j) : row_number(i), column_number(j) {}

subscript subscript::reflect()
{
	return subscript(column_number, row_number);
}

std::istream & operator>>(std::istream & input, subscript &new_subscript)
{
	unsigned char str_subscript[MAX_STRING_SIZE];
	input >> str_subscript;
	new_subscript = string_to_subscript(str_subscript);
	return input;
}

std::ostream & operator<<(std::ostream & output, subscript to_be_printed)
{
	output << "[" << to_be_printed.row_number << "][" << to_be_printed.column_number << "]\n";
	return output;
}

subscript cb(size_t i, size_t j)
{
	return subscript(i, j);
}

subscript string_to_subscript(const unsigned char str[])
{
	throw_exception(string_is_subscript(str), THE_STRING_IS_NOT_A_VALID_SUBSCRIPT);
	subscript result;
	size_t i = 1;
	for (; i < str[i] != '\0' && str[i] != ']'; i++)
	{
		result.row_number = result.row_number * 10 + str[i] - '0';
	}

	i += 2;

	for (; str[i] != '\0' && str[i] != ']'; i++)
	{
		result.column_number = result.column_number * 10 + str[i] - '0';
	}
	return result;
}

bool operator==(subscript R, subscript L)
{
	return (R.column_number == L.column_number) && (R.row_number == L.row_number);
}

bool operator!=(subscript R, subscript L)
{
	return !(R == L);
}

bool operator<(subscript R, subscript L)
{
	return R.row_number < L.row_number && R.column_number < L.column_number;
}

bool operator<=(subscript R, subscript L)
{
	return R.row_number <= L.row_number && R.column_number <= L.column_number;
}

subscript operator-(subscript R, subscript L)
{
	return cb(R.row_number - L.row_number, R.column_number - L.column_number);
}

subscript operator+(subscript R, subscript L)
{
	return cb(R.row_number + L.row_number, R.column_number + L.column_number);
}

bool is_digit(unsigned char c)
{
	return (c >= '0') && (c <= '9');
}

bool string_is_subscript(const unsigned char str[])
{
	if (str[0] != '[') return false;

	size_t i = 1;
	for (; i < MAX_STRING_SIZE; i++)
	{
		if (str[i] == ']')
		{
			if (i == 1) return false;
			break;
		}
		if (!is_digit(str[i])) return false;
		if (i + 1 == MAX_STRING_SIZE) return false;
	}
	
	if (str[++i] != '[') return false;

	size_t bracket_pos = i++;

	for (; i < MAX_STRING_SIZE; i++)
	{
		if (str[i] == ']')
		{
			if (i == bracket_pos + 1) return false;
			break;
		}
		if (!is_digit(str[i])) return false;
		if (i + 1 == MAX_STRING_SIZE) return false;
	}
	if (str[++i] != '\0') return false;
	return true;
}
