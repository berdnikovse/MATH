#pragma once

//"include" section
#include <vector>
#include <algorithm>
#include <cmath>
#include "subscript.h"
#include "minor.h"


//macroses and type-depending operations section
#define EPS 1e-6
#define ELEMENT_NULL 0
#define ELEMENT_ID 1

#define is_null(a) ((a) == 0)


//declaration section

//class matrix and it's member functions declaration
template <class element_type>
class matrix
{
private:
	//basic fields
	size_t height = 0;
	size_t width = 0;
	element_type **body = NULL;
	bool is_transposed = false;

	//additional fields
	minor base_minor;

	//basic private operations
	void assign_one_row_to_another(size_t, size_t);
	void assign_one_column_to_another(size_t, size_t);
	void change_sign();

public:
	//constructors
	matrix(size_t, size_t);
	matrix(size_t = 0);
	matrix(const matrix <element_type> &);
	matrix(const std::vector <element_type> &);
	matrix(const element_type * const * const _array, const size_t &, const size_t &);
	matrix(const element_type *_array, size_t new_height);

	//destructor
	~matrix();

	//basic get_ functions
	size_t get_height() const;
	size_t get_width() const;
	minor get_base_minor() const;

	//basic internal operators
	matrix <element_type> &operator =(const matrix <element_type> &);
	matrix <element_type> &operator +=(const matrix <element_type> &);
	matrix <element_type> &operator -=(const matrix <element_type> &);
	element_type &operator[] (subscript);
	element_type operator[] (subscript) const;

	template <class element_type>
	friend matrix <element_type> operator -(const matrix <element_type> &);

	//input/output operators
	template <class element_type>
	friend std::istream &operator >>(std::istream &, matrix <element_type> &);

	template <class element_type>
	friend std::ostream &operator <<(std::ostream &, const matrix <element_type> &);

	//basic checking operations
	bool is_void() const;
	bool row_is_void(size_t) const;
	bool column_is_void(size_t) const;
	bool is_compatible(const matrix <element_type> &) const;
	bool is_valid(subscript) const;
	bool row_is_valid(size_t) const;
	bool column_is_valid(size_t) const;
	bool is_suitable(const minor &) const;
	bool is_square() const;
	bool is_singular() const;

	//basic transforming operations
	void clear();
	void exchange_rows(size_t, size_t);
	void exchange_columns(size_t, size_t);
	void add_row(size_t, size_t, element_type);
	void multiply_row(size_t, element_type);
	void add_column(size_t, size_t, element_type);
	void multiply_column(size_t, element_type);
	void transpone();
	size_t to_diagonal();
	void to_diagonal_row();
	void inverse();
	void to_regular();

	//matrix operations
	matrix <element_type> get_inversed() const;
	matrix <element_type> get_transponed() const;
	matrix <element_type> get_diagonal() const;
	matrix <element_type> get_submatrix(subscript, subscript) const;
	matrix <element_type> get_submatrix(const minor &) const;
	element_type determinant() const;
	element_type get_sign() const;
	size_t rank() const;

	void copy_row(size_t, std::vector <element_type> &) const;
	void copy_column(size_t, std::vector <element_type> &) const;
	size_t copy_row(size_t, element_type*) const;
	size_t copy_column(size_t, element_type*) const;

	void asign_row(size_t, const std::vector <element_type> &);
	void assign_column(size_t, const std::vector <element_type> &);
	void assign_row(size_t, element_type*);
	void assign_column(size_t, element_type*);

	void attach_left(const matrix <element_type> &);
	void attach_right(const matrix <element_type> &);
	void attach_top(const matrix <element_type> &);
	void attach_bottom(const matrix <element_type> &);

	void move_element(subscript sourse, subscript adress);

	subscript find_first_non_zero(size_t, size_t);
};


//external operators and functions declaration

//pseudoconsructor
template <class element_type>
matrix <element_type> scalar(size_t, const element_type &);

template <class element_type>
matrix <element_type> E(size_t size);

template <class element_type>
matrix <element_type> power(matrix <element_type>, int);

template <class element_type>
bool operator == (const matrix <element_type> &, const matrix <element_type> &);

template <class element_type>
bool operator != (const matrix <element_type> &, const matrix <element_type> &);

template <class element_type>
matrix <element_type> operator +(const matrix <element_type> &, const matrix <element_type> &);

template <class element_type>
matrix <element_type> operator -(const matrix <element_type> &, const matrix <element_type> &);

template <class element_type>
matrix <element_type> operator *(const matrix <element_type> &, const matrix <element_type> &);

template <class element_type>
matrix <element_type> operator *(const matrix <element_type> &, const element_type &);

template <class element_type>
matrix <element_type> operator *(const element_type &, const matrix <element_type> &);

template <class element_type>
matrix <element_type> operator /(const matrix <element_type> &, const element_type &);

template <class element_type>
matrix <element_type> operator /(const element_type &, const matrix <element_type> &);

template <class element_type>
matrix <element_type> operator |(const matrix <element_type> &, const matrix <element_type> &);
//this operator attaches one matrix to another horizontally

template <class element_type>
matrix <element_type> operator /(const matrix <element_type> &, const matrix <element_type> &);
//this operator attaches one matrix to another vertically

template <class element_type>
matrix <element_type> operator &(const matrix <element_type> &, const matrix <element_type> &);
//this operator returns the direct sum of two matrices




//definition section

template<class element_type>
void matrix<element_type>::assign_one_row_to_another(size_t source_number, size_t copy_number)
{
	throw_exception(this->row_is_valid(source_number), ROW_SUBSCRIPT_IS_INVALID);
	throw_exception(this->row_is_valid(copy_number), ROW_SUBSCRIPT_IS_INVALID);
	for (size_t column_counter = 0; column_counter < this->width; column_counter++)
	{
		(*this)[cb(copy_number, column_counter)] = (*this)[cb(source_number, column_counter)];
	}
}

template<class element_type>
void matrix<element_type>::assign_one_column_to_another(size_t source_number, size_t copy_number)
{
	throw_exception(this->column_is_valid(source_number), COLUMN_SUBSCRIPT_IS_INVALID);
	throw_exception(this->column_is_valid(copy_number), COLUMN_SUBSCRIPT_IS_INVALID);
	for (size_t row_counter = 0; row_counter < this->height; row_counter++)
	{
		(*this)[cb(row_counter, copy_number)] = (*this)[cb(row_counter, source_number)];
	}
}

template<class element_type>
void matrix<element_type>::change_sign()
{
	for (size_t row_counter = 0; row_counter < this->get_height(); row_counter++)
	{
		for (size_t column_counter = 0; column_counter < this->get_width(); column_counter++)
		{
			(*this)[cb(row_counter, column_counter)] = -(*this)[cb(row_counter, column_counter)];
		}
	}
}

template<class element_type>
matrix<element_type>::matrix(size_t new_height, size_t new_width)
{
	this->clear();
	this->height = new_height;
	this->width = new_width;
	this->body = new element_type *[this->height];
	for (size_t row_counter = 0; row_counter < this->height; row_counter++)
	{
		this->body[row_counter] = new element_type[this->width];
		for (size_t column_counter = 0; column_counter < this->width; column_counter++)
		{
			(*this)[cb(row_counter, column_counter)] = ELEMENT_NULL;
		}
	}
}

template<class element_type>
matrix<element_type>::matrix(size_t size) : matrix(size, size)
{
	for (size_t i = 0; i < size; i++)
	{
		(*this)[cb(i, i)] = ELEMENT_ID;
	}
}

template<class element_type>
matrix<element_type>::matrix(const matrix<element_type>& to_copy) : matrix(to_copy.body, to_copy.height, to_copy.width) {}

template<class element_type>
matrix<element_type>::matrix(const std::vector<element_type>& to_copy) : matrix(to_copy.size(), 1)
{
	for (size_t row_counter = 0; row_counter < this->height; row_counter++)
	{
		(*this)[cb(row_counter, 0)] = to_copy[row_counter];
	}
}

template<class element_type>
matrix<element_type>::matrix(const element_type * const * const _array, const size_t &new_height, const size_t &new_width) : matrix(new_height, new_width)
{
	for (size_t row_counter = 0; row_counter < this->height; row_counter++)
	{
		for (size_t column_counter = 0; column_counter < this->width; column_counter++)
		{
			(*this)[cb(row_counter, column_counter)] = _array[row_counter][column_counter];
		}
	}
}

template<class element_type>
matrix<element_type>::matrix(const element_type * _array, size_t new_height) : matrix(new_height, 1)
{
	for (size_t row_counter = 0; row_counter < this->height; row_counter++)
	{
		(*this)[cb(row_counter, 0)] = _array[row_counter];
	}
}

template<class element_type>
matrix<element_type>::~matrix()
{
	this->clear();
}

template<class element_type>
size_t matrix<element_type>::get_height() const
{
	return this->height;
}

template<class element_type>
size_t matrix<element_type>::get_width() const
{
	return this->width;
}

template<class element_type>
minor matrix<element_type>::get_base_minor() const
{
	matrix <element_type> this_copy = (*this);
	this_copy.to_diagonal();
	return this_copy.base_minor;
}

template<class element_type>
matrix <element_type> &matrix<element_type>::operator =(const matrix <element_type> &to_copy)
{
	this->clear();
	this->height = to_copy.height;
	this->width = to_copy.width;
	this->body = new element_type *[this->height];
	for (size_t row_counter = 0; row_counter < this->height; row_counter++)
	{
		this->body[row_counter] = new element_type[this->width];
		for (size_t column_counter = 0; column_counter < this->width; column_counter++)
		{
			(*this)[cb(row_counter, column_counter)] = to_copy[cb(row_counter, column_counter)];
		}
	}
	return *this;
}

template<class element_type>
matrix<element_type>& matrix<element_type>::operator += (const matrix<element_type>& to_add)
{
	throw_exception(this->is_compatible(to_add), MATRICES_ARE_NOT_COMPATIBLE_FOR_ADDITION);
	for (size_t row_counter = 0; row_counter < this->height; row_counter++)
	{
		for (size_t column_counter = 0; column_counter < this->width; column_counter++)
		{
			(*this)[cb(row_counter, column_counter)] += to_add[cb(row_counter, column_counter)];
		}
	}
	return *this;
}

template<class element_type>
matrix<element_type>& matrix<element_type>::operator -= (const matrix<element_type>& to_add)
{
	throw_exception(this->is_compatible(to_add), MATRICES_ARE_NOT_COMPATIBLE_FOR_ADDITION);
	for (size_t row_counter = 0; row_counter < this->height; row_counter++)
	{
		for (size_t column_counter = 0; column_counter < this->width; column_counter++)
		{
			(*this)[cb(row_counter, column_counter)] = to_add[cb(row_counter, column_counter)];
		}
	}
	return *this;
}

template<class element_type>
matrix<element_type> operator -(const matrix<element_type> & A)
{
	matrix <element_type> A_copy(A);
	A_copy.change_sign();
	return A_copy;
}

template<class element_type>
element_type & matrix<element_type>::operator [] (subscript S)
{
	throw_exception(this->is_valid(S), ELEMENT_SUBSCRIPT_IS_INVALID);
	return this->body[S.row_number][S.column_number];
}

template<class element_type>
element_type matrix<element_type>::operator[](subscript S) const
{
	throw_exception(this->is_valid(S), ELEMENT_SUBSCRIPT_IS_INVALID);
	return this->body[S.row_number][S.column_number];
}

template <class element_type>
std::istream & operator>>(std::istream & input, matrix<element_type>& new_matrix)
{
	size_t new_height, new_width;
	input >> new_height >> new_width;
	new_matrix.clear();
	new_matrix = matrix <element_type>(new_height, new_width);
	for (size_t row_counter = 0; row_counter < new_height; row_counter++)
	{
		for (size_t column_counter = 0; column_counter < new_width; column_counter++)
		{
			input >> new_matrix[cb(row_counter, column_counter)];
		}
	}
	return input;
}

template<class element_type>
std::ostream & operator<<(std::ostream & output, const matrix<element_type>& to_be_printed)
{
	output << std::endl;
	for (size_t row_counter = 0; row_counter < to_be_printed.get_height(); row_counter++)
	{
		for (size_t column_counter = 0; column_counter < to_be_printed.get_width(); column_counter++)
		{
			output << to_be_printed[cb(row_counter, column_counter)] << "\t";
		}
		output << std::endl;
	}
	output << std::endl;
	return output;
}

template<class element_type>
inline matrix<element_type> operator+(const matrix<element_type>&A, const matrix<element_type>&B)
{
	matrix <element_type> C = A;
	C += B;
	return C;
}

template<class element_type>
inline matrix<element_type> operator-(const matrix<element_type>& A, const matrix<element_type>& B)
{
	matrix <element_type> C = A;
	C -= B;
	return C;
}

template<class element_type>
matrix<element_type> operator*(const matrix<element_type>& A, const matrix<element_type>&B)
{
	throw_exception(A.get_width() == B.get_height(), MATRICES_ARE_NOT_COMPATIBLE_FOR_MULTIPLICATION);
	matrix <element_type> C(A.get_height(), B.get_width());
	for (size_t C_row_counter = 0; C_row_counter < C.get_height(); C_row_counter++)
	{
		for (size_t C_column_counter = 0; C_column_counter < C.get_width(); C_column_counter++)
		{
			for (size_t i = 0; i < A.get_width(); i++)
			{
				C[cb(C_row_counter, C_column_counter)] += A[cb(C_row_counter, i)] * B[cb(i, C_column_counter)];
			}
		}
	}
	C.to_regular();
	return C;
}

template<class element_type>
matrix<element_type> operator*(const matrix<element_type>& A, const element_type & a)
{
	matrix <element_type> B(A);
	for (size_t row_counter = 0; row_counter < A.get_height(); row_counter++)
	{
		for (size_t column_counter = 0; column_counter < A.get_width(); column_counter++)
		{
			B[cb(row_counter, column_counter)] = B[cb(row_counter, column_counter)] * a;
		}
	}
	return B;
}

template<class element_type>
matrix<element_type> operator*(const element_type & a, const matrix<element_type>& A)
{
	matrix <element_type> B(A);
	for (size_t row_counter = 0; row_counter < A.get_height(); row_counter++)
	{
		for (size_t column_counter = 0; column_counter < A.get_width(); column_counter++)
		{
			B[cb(row_counter, column_counter)] = a * B[cb(row_counter, column_counter)];
		}
	}
	return B;
}

template<class element_type>
matrix<element_type> operator/(const matrix<element_type>& A, const element_type & a)
{
	throw_exception(!is_null(a), DIVISION_BY_ZERO);
	element_type b = ELEMENT_ID / a;
	return A * b;
}

template<class element_type>
matrix<element_type> operator/(const element_type & a, const matrix<element_type>& A)
{
	throw_exception(!is_null(a), DIVISION_BY_ZERO);
	element_type b = ELEMENT_ID / a;
	return b * A;
}

template<class element_type>
inline matrix<element_type> operator|(const matrix<element_type>& left_matrix, const matrix<element_type>& right_matrix)
{
	matrix<element_type> result(left_matrix);
	result.attach_right(right_matrix);
	return result;
}

template<class element_type>
inline matrix<element_type> operator/(const matrix<element_type>& top_matrix, const matrix<element_type>& bottom_matrix)
{
	matrix<element_type> result(top_matrix);
	result.attach_bottom(bottom_matrix);
	return result;
}

template<class element_type>
inline matrix<element_type> operator&(const matrix<element_type>& left_top, const matrix<element_type>& right_bottom)
{
	matrix <element_type> left_top_extended = left_top | matrix <element_type>(left_top.get_height(), right_bottom.get_width());
	matrix <element_type> right_bottom_extended = matrix <element_type>(right_bottom.get_height(), left_top.get_width()) | right_bottom;
	return left_top_extended / right_bottom_extended;
}


template<class element_type>
inline bool matrix<element_type>::is_void() const
{
	return !(this->get_height() && this->get_width());
}

template<class element_type>
bool matrix<element_type>::row_is_void(size_t row_number) const
{
	if (!this->row_is_valid(row_number)) return true;
	for (size_t column_counter = 0; column_counter < this->width; column_counter++)
	{
		if (!is_null((*this)[cb(row_number, column_counter)])) return false;
	}
	return true;
}

template<class element_type>
bool matrix<element_type>::column_is_void(size_t column_number) const
{
	if (!this->column_is_valid(column_number)) return true;
	for (size_t row_counter = 0; row_counter < this->height; row_counter++)
	{
		if (!is_null((*this)[cb(row_counter, column_number)])) return false;
	}
	return true;
}

template<class element_type>
bool matrix<element_type>::is_compatible(const matrix<element_type>& to_add) const
{
	return (this->height == to_add.height) && (this->width == to_add.width);
}

template<class element_type>
bool matrix<element_type>::is_valid(subscript S) const
{
	return this->row_is_valid(S.row_number) && this->column_is_valid(S.column_number);
}

template<class element_type>
bool matrix<element_type>::row_is_valid(size_t row_number) const
{
	return row_number < this->height;
}

template<class element_type>
bool matrix<element_type>::column_is_valid(size_t column_number) const
{
	return column_number < this->width;
}

template<class element_type>
bool matrix<element_type>::is_suitable(const minor &grid) const
{
	size_t max_row_subscript = 0, max_column_subscript = 0;
	for (int i = 0; i < grid.get_order(); i++)
	{
		max_row_subscript = std::max(max_row_subscript, grid.get_row_number(i));
		max_column_subscript = std::max(max_column_subscript, grid.get_column_number(i));
	}
	return (max_row_subscript < this->get_height() && max_column_subscript < this->get_width());
}

template<class element_type>
bool matrix<element_type>::is_square() const
{
	return this->width == this->height;
}

template<class element_type>
void matrix<element_type>::clear()
{
	if (this->body == NULL) return;
	for (size_t counter = 0; counter < this->height; counter++)
	{
		delete[] (this->body[counter]);
	}
	delete[] this->body;
	this->body = NULL;
	this->height = 0;
	this->width = 0;
	this->base_minor.clear();
	//std::cout << "The matrix was successfully cleared\n";
}

template<class element_type>
void matrix<element_type>::exchange_rows(size_t row_1, size_t row_2)
{
	stop_if_invalid(this->row_is_valid(row_1));
	stop_if_invalid(this->row_is_valid(row_2));
	stop_if_invalid(row_1 != row_2);
	this->is_transposed = !this->is_transposed;
	element_type *temp_row = new element_type[this->width];
	this->copy_row(row_1, temp_row);
	this->assign_one_row_to_another(row_2, row_1);
	this->assign_row(row_2, temp_row);
	delete[] temp_row;
}

template<class element_type>
void matrix<element_type>::exchange_columns(size_t column_1, size_t column_2)
{
	stop_if_invalid(this->column_is_valid(column_1));
	stop_if_invalid(this->column_is_valid(column_2));
	stop_if_invalid(column_1 != column_2);
	this->is_transposed = !this->is_transposed;
	element_type *temp_column = new element_type[this->height];
	this->copy_column(column_1, temp_column);
	this->assign_one_column_to_another(column_2, column_1);
	this->assign_column(column_2, temp_column);
	delete[] temp_column;
}

template<class element_type>
void matrix<element_type>::add_row(size_t source, size_t adress, element_type coefficient)
{
	throw_exception(this->row_is_valid(source), ROW_SUBSCRIPT_IS_INVALID);
	throw_exception(this->row_is_valid(adress), ROW_SUBSCRIPT_IS_INVALID);
	stop_if_invalid(source != adress);
	for (size_t column_counter = 0; column_counter < this->get_width(); column_counter++)
	{
		(*this)[cb(adress, column_counter)] += coefficient * (*this)[cb(source, column_counter)];
	}
}

template<class element_type>
void matrix<element_type>::multiply_row(size_t row_number, element_type factor)
{
	throw_exception(this->row_is_valid(row_number), ROW_SUBSCRIPT_IS_INVALID);
	for (size_t column_counter = 0; column_counter < this->get_width(); column_counter++)
	{
		(*this)[cb(row_number, column_counter)] *= factor;
	}
}

template<class element_type>
void matrix<element_type>::add_column(size_t source, size_t adress, element_type coefficient)
{
	throw_exception(this->column_is_valid(source), COLUMN_SUBSCRIPT_IS_INVALID);
	throw_exception(this->column_is_valid(adress), COLUMN_SUBSCRIPT_IS_INVALID);
	stop_if_invalid(source != adress);
	for (size_t row_counter = 0; row_counter < this->get_height(); row_counter++)
	{
		(*this)[cb(row_counter, adress)] += coefficient * (*this)[cb(row_counter, source)];
	}
}

template<class element_type>
void matrix<element_type>::multiply_column(size_t column_number, element_type factor)
{
	throw_exception(this->column_is_valid(column_number), COLUMN_SUBSCRIPT_IS_INVALID);
	for (size_t row_counter = 0; row_counter < this->get_height(); row_counter++)
	{
		(*this)[cb(row_counter, column_number)] *= factor;
	}
}

template<class element_type>
void matrix<element_type>::transpone()
{
	matrix <element_type> temp_matrix(this->width, this->height);
	for (size_t i = 0; i < this->height; i++)
	{
		for (size_t j = 0; j < this->width; j++)
		{
			temp_matrix[cb(j, i)] = (*this)[cb(i, j)];
		}
	}
	*this = temp_matrix;
}

template<class element_type>
size_t matrix<element_type>::to_diagonal()
{
	stop_if_invalid(!this->is_void()) 0;
	size_t size = std::min(this->get_height(), this->get_width()), curr_rank = 0;
	size_t *non_zero_minor_rows = new size_t[size];
	size_t *non_zero_minor_columns = new size_t[size];
	for (size_t i = 0; i < size; i++)
	{
		subscript next_non_zero = this->find_first_non_zero(i, i);
		break_if_invalid(next_non_zero != NULL_SUBSCRIPT);
		curr_rank++;
		non_zero_minor_rows[i] = next_non_zero.row_number;
		non_zero_minor_columns[i] = next_non_zero.column_number;
		this->move_element(cb(i, i), next_non_zero);
		for (size_t row_counter = i + 1; row_counter < this->get_height(); row_counter++)
		{
			element_type coefficient = ((*this)[cb(row_counter, i)]) / ((*this)[cb(i, i)]);
			this->add_row(i, row_counter, -coefficient);
		}
		for (size_t column_counter = i + 1; column_counter < this->get_width(); column_counter++)
		{
			element_type coefficient = ((*this)[cb(i, column_counter)]) / ((*this)[cb(i, i)]);
			this->add_column(i, column_counter, -coefficient);
		}
	}
	(this->base_minor) = minor(non_zero_minor_rows, non_zero_minor_rows + curr_rank, non_zero_minor_columns, non_zero_minor_columns + curr_rank);
	delete[] non_zero_minor_rows;
	delete[] non_zero_minor_columns;
	this->to_regular();
	return curr_rank;
}

template<class element_type>
void matrix<element_type>::to_diagonal_row()
{
	size_t size = std::min(this->get_height(), this->get_width());
	for (size_t i = 0; i < size; i++)
	{
		subscript next_non_zero = this->find_first_non_zero(i, i);
		stop_if_invalid(next_non_zero != NULL_SUBSCRIPT);
		this->move_element(cb(i, i), next_non_zero);
		for (size_t row_counter = 0; row_counter < i; row_counter++)
		{
			element_type coefficient = ((*this)[cb(row_counter, i)]) / ((*this)[cb(i, i)]);
			this->add_row(i, row_counter, -coefficient);
		}
		this->multiply_row(i, ELEMENT_ID / (*this)[cb(i, i)]);
		for (size_t row_counter = i + 1; row_counter < this->get_height(); row_counter++)
		{
			element_type coefficient = ((*this)[cb(row_counter, i)]) / ((*this)[cb(i, i)]);
			this->add_row(i, row_counter, -coefficient);
		}
	}
	this->to_regular();
}

template<class element_type>
void matrix<element_type>::inverse()
{
	throw_exception(!this->is_void(), MATRIX_IS_VOID);
	throw_exception(this->is_square(), MATRIX_IS_NOT_SQUARE);
	throw_exception(!this->is_singular(), MATRIX_IS_SINGULAR);
	matrix <element_type> this_copy(*this);
	matrix <element_type> B = E <element_type>(this->get_height());
	this_copy.attach_right(E <element_type>(this->get_height()));
	this_copy.to_diagonal_row();
	(*this) =  this_copy.get_submatrix(cb(0, this->get_height()), cb(this->get_height() - 1, 2 * this->get_height() - 1));
}

template<class element_type>
void matrix<element_type>::to_regular()
{
	for (size_t row_counter = 0; row_counter < this->get_height(); row_counter++)
	{
		for (size_t column_counter = 0; column_counter < this->get_width(); column_counter++)
		{
			if (is_null((*this)[cb(row_counter, column_counter)])) (*this)[cb(row_counter, column_counter)] = ELEMENT_NULL;
		}
	}
}

template<class element_type>
inline matrix<element_type> matrix<element_type>::get_inversed() const
{
	matrix<element_type> this_copy(*this);
	this_copy.inverse();
	return this_copy;
}

template<class element_type>
inline matrix<element_type> matrix<element_type>::get_transponed() const
{
	matrix <element_type> this_copy = *this;
	this_copy.transpone();
	return this_copy;
}

template<class element_type>
inline matrix<element_type> matrix<element_type>::get_diagonal() const
{
	matrix <element_type> this_copy = (*this);
	this_copy.to_diagonal();
	return this_copy;
}

template<class element_type>
matrix<element_type> matrix<element_type>::get_submatrix(subscript left_top, subscript right_bottom) const
{
	throw_exception(left_top <= right_bottom, SUBMATRIX_CORNER_SUBSCRIPTS_ARE_INVALID);
	throw_exception(this->is_valid(left_top), SUBMATRIX_CORNER_SUBSCRIPTS_ARE_INVALID);
	throw_exception(this->is_valid(right_bottom), SUBMATRIX_CORNER_SUBSCRIPTS_ARE_INVALID);
	subscript delta = right_bottom - left_top;
	matrix <element_type> result(delta.row_number + 1, delta.column_number + 1);
	for (size_t row_counter = 0; row_counter <= delta.row_number; row_counter++)
	{
		for (size_t column_counter = 0; column_counter <= delta.column_number; column_counter++)
		{
			result[cb(row_counter, column_counter)] = (*this)[left_top + cb(row_counter, column_counter)];
		}
	}
	return result;
}

template<class element_type>
matrix<element_type> matrix<element_type>::get_submatrix(const minor &grid) const
{
	throw_exception(this->is_suitable(grid), MINOR_PATTERN_IS_NOT_SUITABLE_FOR_THE_MATRIX);
	matrix <element_type> result(grid.get_order(), grid.get_order());
	for (size_t row_subscript = 0; row_subscript < grid.get_order(); row_subscript++)
	{
		for (size_t column_subscript = 0; column_subscript < grid.get_order(); column_subscript++)
		{
			result[cb(row_subscript, column_subscript)] = (*this)[cb(grid.get_row_number(row_subscript), grid.get_column_number(column_subscript))];
		}
	}
	return result;
}

template<class element_type>
element_type matrix<element_type>::determinant() const
{
	throw_exception(this->is_square(), MATRIX_IS_NOT_SQUARE);
	matrix <element_type> temp_matrix = (*this);
	temp_matrix.to_diagonal();
	element_type product = ELEMENT_ID;
	for (size_t i = 0; i < this->height; i++)
	{
		product = product * temp_matrix[cb(i, i)];
	}
	return product * temp_matrix.get_sign();
}

template<class element_type>
inline element_type matrix<element_type>::get_sign() const
{
	return this->is_transposed ? -ELEMENT_ID : ELEMENT_ID;
}

template<class element_type>
size_t matrix<element_type>::rank() const
{
	matrix <element_type> temp_matrix = (*this);
	return temp_matrix.to_diagonal();
}

template<class element_type>
void matrix<element_type>::attach_left(const matrix<element_type>& to_be_attached)
{
	matrix<element_type> to_be_attached_copy(to_be_attached);
	to_be_attached_copy.attach_right(*this);
	*this = to_be_attached_copy;
}

template<class element_type>
void matrix<element_type>::attach_right(const matrix<element_type>& to_be_attached)
{
	throw_exception(this->get_height() == to_be_attached.get_height(), MATRICES_ARE_NOT_COMPATIBLE_FOR_HORIZONTAL_ATTACHMENT);
	matrix <element_type> result(this->get_height(), this->get_width() + to_be_attached.get_width());
	for (size_t column_counter = 0; column_counter < this->get_width(); column_counter++)
	{
		element_type *temp_array = new element_type[result.get_height()];
		this->copy_column(column_counter, temp_array);
		result.assign_column(column_counter, temp_array);
		delete[] temp_array;
	}
	for (size_t column_counter = 0; column_counter < to_be_attached.get_width(); column_counter++)
	{
		element_type *temp_array = new element_type[result.get_height()];
		to_be_attached.copy_column(column_counter, temp_array);
		result.assign_column(column_counter + this->get_width(), temp_array);
		delete[] temp_array;
	}
	*this = result;
}

template<class element_type>
inline void matrix<element_type>::attach_top(const matrix<element_type>& to_be_attached)
{
	throw_exception(this->get_width() == to_be_attached.get_width(), MATRICES_ARE_NOT_COMPATIBLE_FOR_VERTICAL_ATTACHMENT);
	this->transpone();
	this->attach_left(to_be_attached.get_transponed());
 	this->transpone();
}

template<class element_type>
inline void matrix<element_type>::attach_bottom(const matrix<element_type>& to_be_attached)
{
	throw_exception(this->get_width() == to_be_attached.get_width(), MATRICES_ARE_NOT_COMPATIBLE_FOR_VERTICAL_ATTACHMENT);
	this->transpone();
	this->attach_right(to_be_attached.get_transponed());
	this->transpone();
}

template<class element_type>
inline void matrix<element_type>::move_element(subscript sourse, subscript adress)
{
	stop_if_invalid(this->is_valid(sourse));
	stop_if_invalid(this->is_valid(adress));
	exchange_rows(sourse.row_number, adress.row_number);
	exchange_columns(sourse.column_number, adress.column_number);
}

template<class element_type>
subscript matrix<element_type>::find_first_non_zero(size_t lower_height, size_t lower_width)
{
	for (size_t column_counter = lower_width; column_counter < this->width; column_counter++)
	{
		for (size_t row_counter = lower_height; row_counter < this->height; row_counter++)
		{
			if (!is_null((*this)[cb(row_counter, column_counter)])) return cb(row_counter, column_counter);
		}
	}
	return NULL_SUBSCRIPT;
}

template<class element_type>
inline matrix<element_type> scalar(size_t size, const element_type &value)
{
	return matrix <element_type>(size) * value;
}

template<class element_type>
inline matrix<element_type> E(size_t size)
{
	return matrix<element_type>();
}

template<class element_type>
matrix<element_type> power(matrix <element_type> A, int deg)
{
	throw_exception(A.is_square(), MATRIX_IS_NOT_SQUARE);
	if (deg < 0)
	{
		A.inverse();
		deg *= -1;
	}
	matrix <element_type> result = E <element_type>(A.get_height());
	while (deg > 0)
	{
		if (deg & 1)
		{
			result = result * A;
			deg--;
		}
		else
		{
			A = A * A;
			deg /= 2;
		}
	}
	return result;
}

template<class element_type>
bool operator==(const matrix<element_type> & L, const matrix<element_type> & R)
{
	if (L.get_height() != R.get_height()) return false;
	if (L.get_width() != R.get_width()) return false;
	for (size_t row_counter = 0; row_counter < L.get_height(); row_counter++)
	{
		for (size_t column_counter = 0; column_counter < L.get_width(); column_counter++)
		{
			if (!is_null(L[cb(row_counter, column_counter)] - R[cb(row_counter, column_counter)])) return false;
		}
	}
	return true;
}

template<class element_type>
inline bool operator!=(const matrix<element_type> & L, const matrix<element_type>& R)
{
	return !(L == R);
}

template<class element_type>
bool matrix<element_type>::is_singular() const
{
	if (!(this->is_square())) return true;
	return this->rank() < this->height;
}

template<class element_type>
void matrix<element_type>::copy_row(size_t row_number, std::vector<element_type> &copy) const
{
	throw_exception(this->row_is_valid(row_number), ROW_SUBSCRIPT_IS_INVALID);
	copy.clear();
	copy.resize(this->width);
	for (size_t column_counter = 0; column_counter < copy.size(); column_counter++)
	{
		copy[column_counter] = (*this)[cb(row_number, column_counter)];
	}
}

template<class element_type>
void matrix<element_type>::copy_column(size_t column_number, std::vector<element_type> &copy) const
{
	throw_exception(this->column_is_valid(column_number), COLUMN_SUBSCRIPT_IS_INVALID);
	copy.clear();
	copy.resize(this->height);
	for (size_t row_counter = 0; row_counter < copy.size(); row_counter++)
	{
		copy[row_counter] = (*this)[cb(row_counter, column_number)];
	}
}

template<class element_type>
size_t matrix<element_type>::copy_row(size_t row_number, element_type *copy) const
{
	throw_exception(this->row_is_valid(row_number), ROW_SUBSCRIPT_IS_INVALID);
	for (size_t column_counter = 0; column_counter < this->get_width(); column_counter++)
	{
		copy[column_counter] = (*this)[cb(row_number, column_counter)];
	}
	return this->width;
}

template<class element_type>
size_t matrix<element_type>::copy_column(size_t column_number, element_type *copy) const
{
	throw_exception(this->column_is_valid(column_number), COLUMN_SUBSCRIPT_IS_INVALID);
	for (size_t row_counter = 0; row_counter < this->get_height(); row_counter++)
	{
		copy[row_counter] = (*this)[cb(row_counter, column_number)];
	}
	return this->height;
}

template<class element_type>
void matrix<element_type>::asign_row(size_t row_number, const std::vector<element_type> &row_source)
{
	throw_exception(this->row_is_valid(row_number), ROW_SUBSCRIPT_IS_INVALID);
	throw_exception(row_source.size() == this->width, ROW_WIDTH_IS_INVALID);
	for (size_t column_counter = 0; column_counter < row_source.size(); column_counter++)
	{
		(*this)[cb(row_number, column_counter)] = row_source[column_counter];
	}
}

template<class element_type>
void matrix<element_type>::assign_column(size_t column_number, const std::vector<element_type>&column_source)
{
	throw_exception(this->column_is_valid(column_number), COLUMN_SUBSCRIPT_IS_INVALID);
	throw_exception(column_source.size() == this->hegiht, COLUMN_HEIGHT_IS_INVALID);
	for (size_t row_counter = 0; row_counter < column_source.size(); row_counter++)
	{
		(*this)[cb(row_counter, column_number)] = column_source[row_counter];
	}
}

template<class element_type>
void matrix<element_type>::assign_row(size_t row_number, element_type *row_source)
{
	for (size_t column_counter = 0; column_counter < this->width; column_counter++)
	{
		(*this)[cb(row_number, column_counter)] = row_source[column_counter];
	}
}

template<class element_type>
void matrix<element_type>::assign_column(size_t column_number, element_type *column_source)
{
	for (size_t row_counter = 0; row_counter < this->height; row_counter++)
	{
		(*this)[cb(row_counter, column_number)] = column_source[row_counter];
	}
}