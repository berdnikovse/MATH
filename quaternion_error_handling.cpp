#include "standard_error_handling.h"
#include "quaternion_error_handling.h"

const char *quaternion_err_list[] = {
	"unknown error :(",
	"zero quaternion is non-invertible in the division ring of quaternions!",
};

void catch_quaternion_exception(quaternion_error err_num)
{
	std::cout << "An error occurred during the execution: ";
	std::cout << quaternion_err_list[err_num] << '\n';
}
