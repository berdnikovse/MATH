#pragma once

class minor
{
	size_t order;
	size_t *rows;
	size_t *columns;
	minor(size_t *, size_t *, size_t *, size_t *);
};