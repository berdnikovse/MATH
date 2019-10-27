#pragma once

#define catch_quaternion_errors catch (quaternion_error err_num) { catch_quaternion_exception(err_num); }

enum quaternion_error {
	QUATERNION_DIVISION_BY_ZERO = 1
};

extern const char *quaternion_err_list[];

void catch_quaternion_exception(quaternion_error err_num);