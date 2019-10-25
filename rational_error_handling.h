#pragma once
#include "standard_error_handling.h"

#define catch_rational_errors catch (rational_error err_num) { catch_rational_exception(err_num); }

enum rational_error{
	RATIONAL_DIVISION_BY_ZERO = 1,
	STRING_IS_NOT_A_FRACTION
};

extern const char *rational_err_list[];

void catch_rational_exception(rational_error err_num);
