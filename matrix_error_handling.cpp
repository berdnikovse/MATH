#include "matrix.h"

const char *err_list[] = {
	"unknown error.",
	"matrices are not compatible for addition!",
	"element subscript is invalid!",
	"row subscript is invalid!",
	"column subscript is invalid!",
	"row width is invalid!",
	"column height is invalid!",
	"matrix is not square!",
	"matrices are not compatible for mutliplication!",
	"division by zero!",
	"matrices are not compatible for horizontal attachment!",
	"matrices are not compatible for vertical attachment!",
	"matrix is singular!",
	"corner subscripts of the submatrix are incorrect!"
};

void catch_std_exception(errors_enum err_num)
{
	std::cout << "An error occurred during the execution: ";
	std::cout << err_list[err_num] << '\n';
}

void catch_non_std_exception(int err_num)
{
	std::cout << "An error occurred during the execution: ";
	std::cout << err_list[0] << '\n';
}
