#include "minor.h"

minor::minor(size_t *rows_begin, size_t *rows_end, size_t *columns_begin, size_t *columns_end)
{
	throw_exception(rows_begin < rows_end && columns_begin < columns_end, MINOR_IS_VOID);
	throw_exception(rows_end - rows_begin == columns_end - columns_begin, MINOR_SHULD_BE_SQUARE);
	this->order = rows_end - rows_begin;
	this->rows = new size_t[this->order];
	this->columns = new size_t[this->order];
	for (size_t counter = 0; counter < this->order; counter++)
	{
		this->rows[counter] = rows_begin[counter];
		this->columns[counter] = columns_begin[counter];
	}
}

minor::minor(const minor & to_be_copied)
{
	size_t size = to_be_copied.get_order();
	(*this) = minor(to_be_copied.rows, to_be_copied.rows + size, to_be_copied.columns, to_be_copied.columns + size);
}

minor::minor() {}

minor::~minor()
{
	this->clear();
}

minor & minor::operator=(const minor & to_be_copied)
{
	this->clear();
	this->order = to_be_copied.get_order();
	this->rows = new size_t[this->order];
	this->columns = new size_t[this->order];
	for (int i = 0; i < this->order; i++)
	{
		this->rows[i] = to_be_copied.rows[i];
		this->columns[i] = to_be_copied.columns[i];
	}
	return *this;
}

size_t minor::get_order() const
{
	return this->order;
}

size_t minor::get_row_number(size_t number) const
{
	throw_exception(number < this->get_order(), MINOR_ROW_SUBSCRIPT_IS_INVALID);
	return this->rows[number];
}

size_t minor::get_column_number(size_t number) const
{
	throw_exception(number < this->get_order(), MINOR_COLUMN_SUBSCRIPT_IS_INVALID);
	return this->columns[number];
}

void minor::clear()
{
	if (this->order == 0) return;
	delete[] this->rows;
	delete[] this->columns;
	rows = NULL;
	columns = NULL;
	this->order = 0;
}

std::ostream & operator <<(std::ostream &output, const minor &to_be_printed)
{
	output << "\n";
	for (size_t i = 0; i < to_be_printed.get_order(); i++)
	{
		output << to_be_printed.get_row_number(i) << " ";
	}
	output << "\n";
	for (size_t i = 0; i < to_be_printed.get_order(); i++)
	{
		output << to_be_printed.get_column_number(i) << " ";
	}
	output << "\n";
	return output;
}
