#pragma once

#include <iostream>
#include "complex_error_handling.h"

#define e 2.71828182845904523536
#define pi 3.1415926535897932384

class complex
{
private:
	double real;
	double imaginary;
	void to_regular();
public:
	complex(double = 0, double = 0);
	complex(const complex &);
	~complex();

	double Re() const;
	double Im() const;
	double arg() const;
	double abs() const;

	void inverse();
	void conjugate();

	bool is_zero() const;

	complex get_inversed() const;
	complex get_conjugated() const;

	complex &operator =(const complex &);
	complex &operator +=(const complex &);
	complex &operator -=(const complex &);
	complex &operator *=(const complex &);
	complex &operator /=(const complex &);
	complex operator -() const;
	complex &operator ^=(const complex &);

	friend std::ostream &operator <<(std::ostream &output, const complex &);
	friend std::istream &operator >>(std::istream &input, complex &);
};

bool operator ==(const complex &, const complex &);
bool operator !=(const complex &, const complex &);

complex operator +(const complex &, const complex &);
complex operator -(const complex &, const complex &);
complex operator *(const complex &, const complex &);
complex operator /(const complex &, const complex &);
complex operator ^(const complex &, const complex &);

complex from_trig_form(double new_abs, double new_arg);
complex complex_exp(const complex &);
complex complex_log_e(const complex &);
complex complex_power(const complex &, const complex &);