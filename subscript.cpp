#pragma once
#include "subscript.h"

subscript::subscript(size_t i, size_t j) : row_number(i), column_number(j) {}

subscript subscript::reflect()
{
	return subscript(column_number, row_number);
}

std::istream & operator>>(std::istream & input, subscript &new_subscript)
{
	unsigned char str_subscript[STRING_SIZE];
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

subscript string_to_subscript(unsigned char str[])
{
	subscript result;
	size_t i = 1;
	for (; i < STRING_SIZE && str[i] != '\0' && str[i] != ']'; i++)
	{
		result.row_number = result.row_number * 10 + str[i] - '0';
	}

	i += 2;

	for (; i < STRING_SIZE && str[i] != '\0' && str[i] != ']'; i++)
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
