#include "standard_functions.h"

bool is_digit(unsigned char c)
{
	return (c >= '0') && (c <= '9');
}

unsigned long long gcd(unsigned long long a, unsigned long long b)
{
	while (b) a %= b, std::swap(a, b);
	return a;
}

unsigned long long lcm(unsigned long long a, unsigned long long b)
{
	a /= gcd(a, b);
	return a * b;
}

void cancel__(unsigned long long &a, unsigned long long &b)
{
	unsigned long long common_factor = gcd(a, b);
	a /= common_factor, b /= common_factor;
}
