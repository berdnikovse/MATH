#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include "subscript.h"
#include "minor.h"

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
	matrix <element_type> operator -() const;



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
//this operator attaches one matrix to another horizontally
matrix <element_type> operator |(const matrix <element_type> &, const matrix <element_type> &);

template <class element_type>
//this operator attaches one matrix to another vertically
matrix <element_type> operator ||(const matrix <element_type> &, const matrix <element_type> &);

template <class element_type>
//this operator returns the direct sum of two matrices
matrix <element_type> operator &(const matrix <element_type> &, const matrix <element_type> &);

#include "matrix.cpp"