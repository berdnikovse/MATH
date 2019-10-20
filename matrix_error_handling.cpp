#pragma once
#include "matrix_error_handling.h"

const char *matrix_err_list[] = {
	"unknown error :(",
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
	"corner subscripts of the submatrix are invaild!",
	"matrix is void!",
	"the string is not a valid subscript!",
	"minor should be square!",
	"minor is void!",
	"minor row subscript is invalid!",
	"minor column subscript is invalid!",
	"minor pattern is not suitable for the matrix"
};

void catch_matrix_exception(matrix_error err_num)
{
	std::cout << "An error occurred during the execution: ";
	std::cout << matrix_err_list[err_num] << '\n';
}

