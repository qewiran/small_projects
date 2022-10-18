#include "Matrix.h"

Matrix::Matrix()
{
	this->rows = 1;
	this->cols = 1;
	this->values = new double* [1];
	values[0] = new double[1];
	values[0][0] = 0;
}

Matrix::Matrix(int a, int b)
{
	cols = b;
	rows = a;

	values = new double* [rows];
	for (int i = 0; i < rows; i++)
		values[i] = new double[cols];
}

Matrix& Matrix::operator=(const Matrix& reference)
{
	this->cols = reference.cols;
	this->rows = reference.rows;
	this->values = new double* [rows];

	for (int i = 0; i < rows; i++)
		(*this)(i) = new double[cols];

	for (int i = 0; i < rows; i++)
		memcpy((*this)(i), reference.values[i], cols * 8);
	return *this;
}

Matrix& Matrix::operator*(const Matrix& other)
{
	int rows1 = this->rows;
	int rows2 = other.rows;
	int cols1 = this->cols;
	int cols2 = other.cols;
	if (cols1 != rows2)
	{
		throw std::invalid_argument("the number of columns of the first matrix does not match the number of rows of the second matrix \n");
	}
	Matrix* result = new Matrix(rows1, cols2);
	for (int i = 0; i < rows1; i++)
	{
		for (int j = 0; j < cols2; j++)
		{
			(*result)(i, j) = 0;
			for (int k = 0; k < cols1; k++)
				(*result)(i, j) += (*this)(i,k) * other(k,j);
		}
	}
	return *result;
}

const inline double& Matrix:: operator()(int index_row, int index_col) const
{
	return this->values[index_row][index_col];
}

inline double& Matrix::operator()(int index_row, int index_col)
{	
	return this->values[index_row][index_col];
}

const inline double* Matrix:: operator()(int index_row) const
{
	return this->values[index_row];
}

inline double*& Matrix::operator()(int index_row)
{
	return this->values[index_row];
}


Matrix::Matrix(const Matrix& reference)
{
	this->cols = reference.cols;
	this->rows = reference.rows;
	this->values = new double* [rows];

	for (int i = 0; i < rows; i++)
		(*this)(i) = new double[cols];

	for (int i = 0; i < rows; i++)
		memcpy((*this)(i), reference(i), cols * 8);
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
		delete[] this->values[i];

	delete[] this->values;
}

void Matrix::MakeCustom()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			std::cin >> (*this)(i,j);
}

void Matrix::MakeIdentity()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == j)
				(*this)(i,j) = 1;
			else (*this)(i,j) = 0;
		}
	}
}

void Matrix::Swap_Rows(const int row1, const int row2)
{
	double* buff;
	buff = values[row1];
	values[row1] = values[row2];
	values[row2] = buff;

}

void Matrix::Swap_Cols(const int col1, const int col2)
{
	int rows =this->rows;
	for (int i = 0; i < rows; i++)
	{
		double buff = (*this)(i,col1);
		(*this)(i,col1) = (*this)(i,col2);
		(*this)(i,col2) = buff;
	}

}

void Matrix::Transpose()
{
	int new_rows = this->cols;
	int new_cols = this->rows;
	Matrix Transposed(new_rows,new_cols);

	for (int i = 0; i < new_cols; i++)
	{
		for (int j = 0; j < new_rows; j++)
		{
			Transposed(j,i)=(*this)(i, j);
		}
	}

	Transposed.Display();
	*this = Transposed;

}

void Matrix::Display()
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			if (std::abs((*this)(i, j)) > 1e-14)
				std::cout << (*this)(i, j) << ' ';
			else std::cout << 0 << ' ';
		}
		std::cout << '\n';
	}

}


