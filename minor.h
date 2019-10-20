#pragma once

#include "matrix_error_handling.h"

#ifndef MINOR
#define MINOR
#endif // !MINOR


class minor
{
private:
	size_t order = 0;
	size_t *rows = NULL;
	size_t *columns = NULL;
public:
	minor(size_t *, size_t *, size_t *, size_t *);
	minor(const minor &);
	minor();
	~minor();

	friend std::ostream &operator <<(std::ostream &, const minor &);

	minor &operator =(const minor &);

	size_t get_order() const;
	size_t get_row_number(size_t) const;
	size_t get_column_number(size_t) const;
	void clear();
};