#pragma once

#define catch_complex_errors catch (complex_error err_num) { catch_complex_exception(err_num); }

enum complex_error {
	COMPLEX_DIVISION_BY_ZERO = 1,
	ARGUMENT_OF_ZERO_IS_UNDEFINED,
	LOGARITHM_OF_ZERO_IS_UNDEFINED
};

extern const char *complex_err_list[];

void catch_complex_exception(complex_error err_num);