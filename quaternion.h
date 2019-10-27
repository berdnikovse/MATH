#pragma once

#include <iostream>
#include "quaternion_error_handling.h"
#include "standard_error_handling.h"

#define e 2.71828182845904523536
#define pi 3.1415926535897932384

class quaternion
{
private:
	double real;
	double i_part;
	double j_part;
	double k_part;
	void to_regular();
public:
	quaternion(double = 0, double = 0, double = 0, double = 0);
	quaternion(const quaternion &);
	~quaternion();

	double Re() const;
	double I() const;
	double J() const;
	double K() const;
	double abs() const;

	void inverse();
	void conjugate();

	bool is_zero() const;

	quaternion get_inversed() const;
	quaternion get_conjugated() const;

	quaternion &operator =(const quaternion &);
	quaternion &operator +=(const quaternion &);
	quaternion &operator -=(const quaternion &);
	quaternion operator -() const;

	quaternion &operator ^=(int);

	friend std::ostream &operator <<(std::ostream &output, const quaternion &);
	friend std::istream &operator >>(std::istream &input, quaternion &);
};

bool operator ==(const quaternion &, const quaternion &);
bool operator !=(const quaternion &, const quaternion &);

quaternion operator +(const quaternion &, const quaternion &);
quaternion operator -(const quaternion &, const quaternion &);
quaternion operator *(const quaternion &, const quaternion &);

quaternion power(const quaternion & base, int deg);
quaternion operator ^(const quaternion &, int);