#pragma once
#include <iostream>

#define throw_exception(is_valid, err_num) if(!(is_valid)) throw err_num
#define stop_if_invalid(is_valid) if(!(is_valid)) return

void catch_non_std_exception(int);