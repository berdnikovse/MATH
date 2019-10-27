#include <cmath>
#include "quaternion.h"

#include "standard_functions.h"
#include "standard_error_handling.h"

#define EPS 1e-12

void quaternion::to_regular()
{
	if (ABS(this->Re()) < EPS) this->real = 0;
	if (ABS(this->I()) < EPS) this->i_part = 0;
	if (ABS(this->J()) < EPS) this->j_part = 0;
	if (ABS(this->K()) < EPS) this->k_part = 0;
}

quaternion::quaternion(double new_real_part, double new_i_part, double new_j_part, double new_k_part) :
	real(new_real_part), i_part(new_i_part), j_part(new_j_part), k_part(new_k_part){
	this->to_regular();
}

quaternion::quaternion(const quaternion &to_be_copied)
{
	*this = to_be_copied;
}

quaternion::~quaternion() {}

double quaternion::Re() const
{
	return this->real;
}

double quaternion::I() const
{
	return this->i_part;
}

double quaternion::J() const
{
	return this->j_part;
}

double quaternion::K() const
{
	return this->k_part;
}

double quaternion::abs() const
{
	return sqrt(this->Re() * this->Re() + this->I() * this->I() + this->J() * this->J() + this->K() * this->K());
}

void quaternion::inverse()
{
	throw_exception(!(this->is_zero()), QUATERNION_DIVISION_BY_ZERO);
	this->conjugate();
	double this_abs = this->abs();
	this->real /= this_abs * this_abs;
	this->i_part /= this_abs * this_abs;
	this->j_part /= this_abs * this_abs;
	this->k_part /= this_abs * this_abs;
}

void quaternion::conjugate()
{
	this->i_part = -this->i_part;
	this->j_part = -this->j_part;
	this->k_part = -this->k_part;
}

bool quaternion::is_zero() const
{
	return this->abs() < EPS;
}

quaternion quaternion::get_inversed() const
{
	quaternion this_copy(*this);
	this_copy.inverse();
	return this_copy;
}

quaternion quaternion::get_conjugated() const
{
	quaternion this_copy(*this);
	this_copy.conjugate();
	return this_copy;
}

quaternion & quaternion::operator=(const quaternion &to_be_copied)
{
	this->real = to_be_copied.Re();
	this->i_part = to_be_copied.I();
	this->j_part = to_be_copied.J();
	this->k_part = to_be_copied.K();
	this->to_regular();
	return *this;
}

quaternion & quaternion::operator+=(const quaternion &to_be_added)
{
	this->real += to_be_added.Re();
	this->i_part += to_be_added.I();
	this->j_part += to_be_added.J();
	this->k_part += to_be_added.K();
	return *this;
}

quaternion & quaternion::operator-=(const quaternion &to_be_added)
{
	this->real -= to_be_added.Re();
	this->i_part -= to_be_added.I();
	this->j_part -= to_be_added.J();
	this->k_part -= to_be_added.K();
	return *this;
}

quaternion quaternion::operator-() const
{
	quaternion this_copy(*this);
	this_copy.real = -this_copy.Re();
	this_copy.i_part = -this_copy.I();
	this_copy.j_part = -this_copy.J();
	this_copy.k_part = -this_copy.K();
	return this_copy;
}

std::ostream & operator<<(std::ostream & output, const quaternion &to_be_printed)
{
	output << "(";
	output << to_be_printed.Re() << ", ";
	output << to_be_printed.I() << ", ";
	output << to_be_printed.J() << ", ";
	output << to_be_printed.K();
	output << ")";
	return output;
}

std::istream & operator>>(std::istream & input, quaternion &new_quaternion)
{
	input >> new_quaternion.real >> new_quaternion.i_part >> new_quaternion.j_part >> new_quaternion.k_part;
	return input;
}

bool operator==(const quaternion &A, const quaternion &B)
{
	return (A - B).is_zero();
}

bool operator !=(const quaternion &A, const quaternion &B)
{
	return !(A == B);
}

quaternion operator+(const quaternion &A, const quaternion &B)
{
	quaternion A_copy(A);
	A_copy += B;
	return A_copy;
}

quaternion operator-(const quaternion &A, const quaternion &B)
{
	quaternion A_copy = A;
	A_copy -= B;
	return A_copy;
}

quaternion operator*(const quaternion &A, const quaternion &B)
{
	double new_real = A.Re() * B.Re() - A.I() * B.I() - A.J() * B.J() - A.K() * B.K();
	double new_i_part = A.Re() * B.I() + A.I() * B.Re() + A.J() * B.K() - A.K() * B.J();
	double new_j_part = A.Re() * B.J() - A.I() * B.K() + A.J() * B.Re() + A.K() * B.I();
	double new_k_part = A.Re() * B.K() + A.I() * B.J() - A.J() * B.I() + A.K() * B.Re();
	return quaternion(new_real, new_i_part, new_j_part, new_k_part);
}

quaternion power(const quaternion &base, int deg)
{
	quaternion base_copy(base);
	if (deg < 0)
	{
		base_copy.inverse();
		deg *= -1;
	}
	quaternion result = quaternion(1, 0, 0, 0);
	while (deg > 0)
	{
		if (deg & 1)
		{
			result = result * base_copy;
			deg--;
		}
		else
		{
			base_copy = base_copy * base_copy;
			deg /= 2;
		}
	}
	return result;
}

quaternion & quaternion::operator^=(int deg)
{
	*this = power(*this, deg);
	return *this;
}

quaternion operator^(const quaternion &base, int deg)
{
	return power(base, deg);
}
