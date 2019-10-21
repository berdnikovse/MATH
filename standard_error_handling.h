#pragma once
#include <iostream>

#define catch_standard_errors catch (int err_num) { catch_non_std_exception(err_num); }

#define throw_exception(is_valid, err_num) if(!(is_valid)) throw err_num
#define stop_if_invalid(is_valid) if(!(is_valid)) return
#define break_if_invalid(is_valid) if(!(is_valid)) break
#define continue_if_invalid(is_valid) if(!(is_valid)) continue

void catch_non_std_exception(int);