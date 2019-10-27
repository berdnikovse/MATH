#include "standard_error_handling.h"
#include "complex_error_handling.h"

const char *complex_err_list[] = {
	"unknown error :(",
	"complex division by zero!",
	"argument of zero is undefined!",
	"logarithm of zero is undefined!"
};

void catch_complex_exception(complex_error err_num)
{
	std::cout << "An error occurred during the execution: ";
	std::cout << complex_err_list[err_num] << '\n';
}
