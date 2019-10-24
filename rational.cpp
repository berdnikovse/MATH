#include "rational.h"

#define MAX_STRING_SIZE 50

bool operator==(const rational & L, const rational & R)
{
	return L.get_numerator() == R.get_numerator() && L.get_denominator() == R.get_denominator() && L.get_sign() == R.get_sign();
}

bool operator!=(const rational & L, const rational & R)
{
	return !(L == R);
}

bool is_rational(char_t str[])
{
	size_t i = 0;
	if (str[i] == '-')
	{
		i++;
	}
	for (; i < MAX_STRING_SIZE; i++)
	{
		if (!is_digit(str[i]))
		{
			break_if_invalid(str[i] != '/');
			if (str[i] == '\0') return true;
			return false;
		}
		if (i + 1 == MAX_STRING_SIZE) return false;
	}
	for (++i; i < MAX_STRING_SIZE; i++)
	{
		if (!is_digit(str[i]))
		{
			if (str[i - 1] == '/') return false;
			break_if_invalid(str[i] != '\0');
			return false;
		}
		if (i + 1 == MAX_STRING_SIZE) return false;
	}
	return true;
}

basic_t rational::get_num() const
{
	return this->numerator;
}

basic_t rational::get_denom() const
{
	return this->denominator;
}

void rational::change_sign()
{
	sign *= -1;
}

void rational::simplify()
{
	throw_exception(this->get_denom() != 0, RATIONAL_DIVISION_BY_ZERO);
	cancel__(this->numerator, this->denominator);
	if (this->get_num() == 0) this->sign = 1;
}

rational::rational(const rational &to_copy) :
	numerator(to_copy.numerator), denominator(to_copy.denominator), sign(to_copy.sign) {
	this->simplify();
}

rational::rational(front_t new_numerator, front_t new_denominator) :
	numerator(ABS(new_numerator)), denominator(ABS(new_denominator)), sign(SGN(new_numerator) * SGN(new_denominator)) {
	this->simplify();
}

rational::rational(basic_t new_numerator, basic_t new_denominator, sign_t pseudo_sign) :
	numerator(new_numerator), denominator(new_denominator), sign(SGN(pseudo_sign)) {
	this->simplify();
}

rational::rational(front_t new_numerator) :
	numerator(ABS(new_numerator)), denominator(1), sign(SGN(new_numerator)) {}

rational::~rational() {}

rational & rational::operator=(const rational &to_be_copied)
{
	this->sign = to_be_copied.get_sign();
	this->numerator = to_be_copied.get_num();
	this-> denominator = to_be_copied.get_denom();
	this->simplify();
	return *this;
}

rational rational::operator-() const
{
	rational this_copy(*this);
	this_copy.change_sign();
	return this_copy;
}

std::istream & operator>>(std::istream & input, rational & new_rational)
{
	char_t new_rational_str[MAX_STRING_SIZE];
	input >> new_rational_str;
	new_rational = string_to_rational(new_rational_str);
	return input;
}

std::ostream & operator<<(std::ostream & output, const rational & to_be_printed)
{
	output << to_be_printed.get_numerator();
	if (to_be_printed.get_denominator() > 1)
	{
		output << "/" << to_be_printed.get_denominator();
	}
	return output;
}

rational & rational::operator +=(const rational &to_be_added)
{
	basic_t common_denominator = lcm(this->get_denom(), to_be_added.get_denom());
	basic_t new_numerator;
	rational this_abs = this->absolute_value();
	rational to_be_added_abs = to_be_added.absolute_value();
	sign_t eventual_sign = this->get_sign();

	if (this->get_sign() != to_be_added.get_sign())
	{
		if (this_abs < to_be_added_abs)
		{
			new_numerator = common_denominator / to_be_added.get_denom() * to_be_added.get_num() - common_denominator / this->get_denom() * this->get_num();
			eventual_sign *= -1;
		}
		else new_numerator = common_denominator / this->get_denom() * this->get_num() - common_denominator / to_be_added.get_denom() * to_be_added.get_num();
	}
	else new_numerator = common_denominator / this->get_denom() * this->get_num() + common_denominator / to_be_added.get_denom() * to_be_added.get_num();
	(*this) = rational(new_numerator, common_denominator, eventual_sign);
	return *this;
}

rational & rational::operator -=(const rational & to_be_subtracted)
{
	rational to_be_subtracted_copy = -to_be_subtracted;
	(*this) += to_be_subtracted_copy;
	return *this;
}

rational & rational::operator *=(const rational & to_be_multiplied)
{
	basic_t to_be_multiplied_num = to_be_multiplied.get_num();
	basic_t to_be_multiplied_denom = to_be_multiplied.get_denom();
	cancel__(this->numerator, to_be_multiplied_denom);
	cancel__(this->denominator, to_be_multiplied_num);
	this->numerator *= to_be_multiplied_num;
	this->denominator *= to_be_multiplied_denom;
	this->sign *= to_be_multiplied.get_sign();
	return *this;
}

rational & rational::operator/=(const rational & to_be_divided)
{
	basic_t to_be_divided_num = to_be_divided.get_num();
	basic_t to_be_divided_denom = to_be_divided.get_denom();
	cancel__(this->numerator, to_be_divided_num);
	cancel__(this->denominator, to_be_divided_denom);
	this->numerator *= to_be_divided_denom;
	this->denominator *= to_be_divided_num;
	this->sign *= to_be_divided.get_sign();
	return *this;
}

sign_t rational::get_sign() const
{
	return this->sign;
}

front_t rational::get_numerator() const
{
	return this->get_sign() * this->get_num();
}

front_t rational::get_denominator() const
{
	return this->get_denom();
}

rational rational::absolute_value() const
{
	rational result(*this);
	if (result.get_sign() < 0) result.change_sign();
	return result;
}

rational operator+(rational A, rational B)
{
	A += B;
	return A;
}

rational operator-(rational A, rational B)
{
	A -= B;
	return A;
}

rational operator*(rational A, rational B)
{
	A *= B;
	return A;
}

rational operator/(rational A, rational B)
{
	A /= B;
	return A;
}

bool operator<(const rational & L, const rational & R)
{
	if (L.get_sign() < R.get_sign()) return true;
	if (L.get_sign() > R.get_sign()) return true;
	basic_t common_denominator = lcm(L.get_denominator(), R.get_denominator());
	return common_denominator / L.get_denominator() * L.get_numerator() < common_denominator / R.get_denominator() * R.get_numerator();
}

inline bool operator>(const rational & L, const rational & R)
{
	return R < L;
}

inline bool operator<=(const rational & L, const rational & R)
{
	return !(R < L);
}

inline bool operator>=(const rational & L, const rational & R)
{
	return !(L < R);
}

rational string_to_rational(char_t str[])
{
	throw_exception(is_rational(str), STRING_IS_NOT_A_FRACTION);
	size_t i = 0;
	basic_t new_numerator = 0;
	basic_t new_denominator = 0;
	sign_t new_sign = 1;
	if (str[i] == '-')
	{
		i++;
		new_sign *= -1;
	}
	if (str[i] == '/') new_numerator = 1;
	for (; str[i] != '\0' && str[i] != '/'; i++)
	{
		new_numerator = new_numerator * 10 + str[i] - '0';
	}
	if (str[i] == '\0') return rational(new_numerator, 1, new_sign);
	i++;
	for (; str[i] != '\0' && str[i] != '/'; i++)
	{
		new_denominator = new_denominator * 10 + str[i] - '0';
	}
	return rational(new_numerator, new_denominator, new_sign);
}
