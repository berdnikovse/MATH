#include "rational_error_handling.h"

const char *rational_err_list[] = {
	"unknown error :(",
	"rational division by zero!",
	"string is not a fraction!"
};

void catch_rational_exception(rational_error err_num)
{
	std::cout << "An error occurred during the execution: ";
	std::cout << rational_err_list[err_num] << '\n';
}
