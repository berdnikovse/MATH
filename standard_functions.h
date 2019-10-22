#pragma once

#include <algorithm>

bool is_digit(unsigned char c);

unsigned long long gcd(unsigned long long, unsigned long long);
void cancel__(unsigned long long &, unsigned long long &);

template <class T>
constexpr signed char SGN(T a)
{
	return a < 0 ? -1 : 1;
}

template <class T>
constexpr T ABS(T a)
{
	return a > 0 ? a : -a;
}

