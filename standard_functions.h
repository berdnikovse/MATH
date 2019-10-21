#pragma once

#ifndef __STDFUNC___
#define __STDFUNC___
#endif // !__STDFUNC___

bool is_digit(unsigned char c);

template <class T>
constexpr signed char SGN(T a)
{
	return a < 0 ? -1 : 1;
}

template <class T>
constexpr T ABS(T a)
{
	return a > 0 ? a : -a;
}

