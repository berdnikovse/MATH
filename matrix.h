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
	void change_element_sign();


public:
	//constructors
	matrix(size_t, size_t); //creates rectangular matrix with given dimensions filled with zeores
	matrix(size_t = 0); //creates identity matrix with given size
	matrix(const matrix <element_type> &); //copy constructor
	matrix(const std::vector <element_type> &); //creates matrix-coulmn from vector-column
	matrix(const element_type * const * const _array, const size_t &, const size_t &); //creates rectangular matrix with given dimensions and body
	matrix(const element_type *_array, size_t new_height); //creates matrix-coulmn from an array-column

	//destructor
	~matrix();

	//set_ functions
	void fill(element_type(*filling_func)(size_t, size_t)); //fills matrix with values of filling_func(i, j)
	void apply(element_type(*to_be_applied)(const element_type &)); //applies function "to_be_applied" to each element of the matrix
	void set_sign();

	//basic get_ functions
	size_t get_height() const;
	size_t get_width() const;
	minor get_base_minor() const;


	//basic internal operators
	matrix <element_type> &operator =(const matrix <element_type> &);
	matrix <element_type> &operator +=(const matrix <element_type> &);
	matrix <element_type> &operator -=(const matrix <element_type> &);
	matrix <element_type> &operator ^=(int);
	element_type &operator[] (subscript);
	element_type operator[] (subscript) const;
	matrix <element_type> operator -() const;



	//input/output operators
	template <class element_type>
	friend std::istream &operator >>(std::istream &, matrix <element_type> &);

	template <class element_type>
	friend std::ostream &operator <<(std::ostream &, const matrix <element_type> &);


	//basic checking operations
	bool is_void() const; //checks whether both of matrix dimentions are non-zero
	bool row_is_void(size_t) const; //checks whether there is at least one non-zero element in the row with given number
	bool column_is_void(size_t) const; //checks whether there is at least one non-zero element in the column with given number
	bool is_compatible(const matrix <element_type> &) const; //cheks whether it is possible to add given matrix to this
	bool is_valid(subscript) const;
	bool row_is_valid(size_t) const; //checks whether given row number is valid
	bool column_is_valid(size_t) const; //checks whether given column number is valid
	bool is_suitable(const minor &) const; //checks whether minor pattren is suitable for the matrix
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
matrix <element_type> operator ^(const matrix <element_type> &, int);

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