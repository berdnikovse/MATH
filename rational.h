#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>
#include "rational_error_handling.h"
#include "standard_functions.h"

typedef signed long long front_t;
typedef unsigned long long basic_t;
typedef signed char sign_t;
typedef unsigned char char_t;

class rational
{
private:
	sign_t sign = 1;
	basic_t numerator = 0;
	basic_t denominator = 1;

	basic_t get_num() const;
	basic_t get_denom() const;
	void change_sign();
	void simplify();
public:
	rational(const rational &);
	rational(front_t, front_t);
	rational(basic_t, basic_t, sign_t);
	rational(front_t = 0);
	~rational();

	rational &operator =(const rational &);
	rational &operator +=(const rational &);
	rational &operator -=(const rational &);
	rational &operator *=(const rational &);
	rational &operator /=(const rational &);
	rational operator -() const;

	friend std::istream & operator >> (std::istream &, rational &);
	friend std::ostream & operator << (std::ostream &, const rational &);

	sign_t get_sign() const;
	front_t get_numerator() const;
	front_t get_denominator() const;
	rational absolute_value() const;
};

rational operator +(rational, rational);
rational operator -(rational, rational);
rational operator *(rational, rational);
rational operator /(rational, rational);

bool operator <(const rational &, const rational &);
bool operator >(const rational &, const rational &);
bool operator <=(const rational &, const rational &);
bool operator >=(const rational &, const rational &);
bool operator ==(const rational &, const rational &);
bool operator !=(const rational &, const rational &);

bool is_rational(char_t str[]);
rational string_to_rational(char_t str[]);