#include <cmath>
#include "complex.h"

#include "standard_functions.h"
#include "standard_error_handling.h"

#define EPS 1e-12

void complex::to_regular()
{
	if (ABS(this->Re()) < EPS) this->real = 0;
	if (ABS(this->Im()) < EPS) this->imaginary = 0;
}

complex::complex(double new_real, double new_imaginary) : real(new_real), imaginary(new_imaginary)
{
	this->to_regular();
}

complex::complex(const complex &to_be_copied)
{
	*this = to_be_copied;
}

complex::~complex() {}

double complex::Re() const
{
	return this->real;
}

double complex::Im() const
{
	return this->imaginary;
}

double complex::arg() const
{
	throw_exception(!(this->is_zero()), ARGUMENT_OF_ZERO_IS_UNDEFINED);
	if (this->Im() > 0) return acos(this->Re() / this->abs());
	return 2 * pi - acos(this->Re() / this->abs());
}

double complex::abs() const
{
	return sqrt(this->Re() * this->Re() + this->Im() * this->Im());
}

void complex::inverse()
{
	throw_exception(!(this->is_zero()), COMPLEX_DIVISION_BY_ZERO);
	this->conjugate();
	double this_abs = this->abs();
	this->real /= this_abs * this_abs;
	this->imaginary /= this_abs * this_abs;
}

void complex::conjugate()
{
	this->imaginary = -this->imaginary;
}

bool complex::is_zero() const
{
	return this->abs() < EPS;
}

complex complex::get_inversed() const
{
	complex this_copy(*this);
	this_copy.inverse();
	return this_copy;
}

complex complex::get_conjugated() const
{
	complex this_copy(*this);
	this_copy.conjugate();
	return this_copy;
}

complex & complex::operator=(const complex &to_be_copied)
{
	this->real = to_be_copied.Re();
	this->imaginary = to_be_copied.Im();
	this->to_regular();
	return *this;
}

complex & complex::operator+=(const complex &to_be_added)
{
	this->real += to_be_added.Re();
	this->imaginary += to_be_added.Im();
	return *this;
}

complex & complex::operator-=(const complex &to_be_added)
{
	this->real -= to_be_added.Re();
	this->imaginary -= to_be_added.Im();
	return *this;
}

complex & complex::operator*=(const complex &to_be_multiplied)
{
	*this = *this * to_be_multiplied;
	return *this;
}

complex & complex::operator/=(const complex &to_be_divided_by)
{
	(*this) *= to_be_divided_by.get_inversed();
	return *this;
}

complex complex::operator-() const
{
	complex this_copy(*this);
	this_copy.real = -this_copy.real;
	this_copy.imaginary = -this_copy.imaginary;
	return this_copy;
}

complex & complex::operator^=(const complex &deg)
{
	*this = complex_power(*this, deg);
}

std::ostream & operator<<(std::ostream & output, const complex &to_be_printed)
{
	if (ABS(to_be_printed.Im()) < EPS)
	{
		output << to_be_printed.Re();
		return output;
	}
	if (ABS(to_be_printed.Re()) < EPS)
	{
		output << to_be_printed.Im() << "i";
		return output;
	}
	output << to_be_printed.Re() << " ";
	if (to_be_printed.Im() > 0)
	{
		output << "+ " << to_be_printed.Im() << "i";
	}
	else output << "- " << -to_be_printed.Im() << "i";
	return output;
}

std::istream & operator>>(std::istream & input, complex &new_complex)
{
	input >> new_complex.real >> new_complex.imaginary;
	return input;
}

bool operator==(const complex &A, const complex &B)
{
	return (A - B).is_zero();
}

bool operator!=(const complex &A, const complex &B)
{
	return !(A == B);
}

complex operator+(const complex &A, const complex &B)
{
	complex A_copy = A;
	A_copy += B;
	return A_copy;
}

complex operator-(const complex &A, const complex &B)
{
	complex A_copy = A;
	A_copy -= B;
	return A_copy;
}

complex operator*(const complex &A, const complex &B)
{
	return complex(A.Re() * B.Re() - A.Im() * B.Im(), A.Re() * B.Im() + A.Im() * B.Re());
}

complex operator/(const complex &A, const complex &B)
{
	return A * B.get_inversed();
}

complex operator^(const complex &base, const complex &deg)
{
	return complex_power(base, deg);
}

complex from_trig_form(double new_abs, double new_arg)
{
	return complex(new_abs * cos(new_arg), new_abs * sin(new_arg));
}

complex complex_exp(const complex &deg)
{
	double new_abs = pow(e, deg.Re());
	double new_arg = deg.Im();
	return from_trig_form(new_abs, new_arg);
}

complex complex_log_e(const complex &z)
{
	throw_exception(!z.is_zero(), LOGARITHM_OF_ZERO_IS_UNDEFINED);
	return complex(log(z.abs()), z.arg());
}

complex complex_power(const complex &base, const complex &deg)
{
	return complex_exp(deg * complex_log_e(base));
}
