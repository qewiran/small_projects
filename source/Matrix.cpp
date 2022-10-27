
#include "Matrix.h"
Matrix::Matrix()
{
	this->rows = 1;
	this->cols = 1;
	this->values = new double *[1];
	values[0] = new double[1];
	values[0][0] = 0;
}

Matrix::Matrix(int a, int b)
{
	cols = b;
	rows = a;

	values = new double *[rows];
	for (int i = 0; i < rows; i++)
		values[i] = new double[cols];
}

Matrix &Matrix::operator=(const Matrix &reference)
{
	this->cols = reference.cols;
	this->rows = reference.rows;
	this->values = new double *[rows];

	for (int i = 0; i < rows; i++)
		(*this)(i) = new double[cols];
	for (int i = 0; i < rows; i++)
		std::copy(reference(i), reference(i) + cols, (*this)(i));
	return *this;
}

Matrix &Matrix::operator*(const Matrix &other)
{
	int rows1 = this->rows;
	int rows2 = other.rows;
	int cols1 = this->cols;
	int cols2 = other.cols;
	if (cols1 != rows2)
	{
		throw std::invalid_argument("the number of columns of the first matrix does not match the number of rows of the second matrix \n");
	}
	Matrix *result = new Matrix(rows1, cols2);

	for (int i = 0; i < rows1; i++)
	{
		for (int j = 0; j < cols2; j++)
		{
			(*result)(i, j) = 0;
			for (int k = 0; k < cols1; k++)
				(*result)(i, j) += (*this)(i, k) * other(k, j);
		}
	}
	return *result;
}

const double &Matrix::operator()(int index_row, int index_col) const
{
	return this->values[index_row][index_col];
}

double &Matrix::operator()(int index_row, int index_col)
{
	return this->values[index_row][index_col];
}

const double *Matrix::operator()(int index_row) const
{
	return this->values[index_row];
}

double *&Matrix::operator()(int index_row)
{
	return this->values[index_row];
}

Matrix::Matrix(const Matrix &reference)
{
	this->cols = reference.cols;
	this->rows = reference.rows;
	this->values = new double *[rows];

	for (int i = 0; i < rows; i++)
		(*this)(i) = new double[cols];
	for (int i = 0; i < rows; i++)
		std::copy(reference(i), reference(i) + cols, (*this)(i));
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
		delete[] (*this)(i);

	delete[] this->values;
}

void Matrix::MakeCustom()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int exp = rand();
			std::cin >> (*this)(i, j);
		}
	}
}

void Matrix::MakeRandom(bool degen)
{
	srand(time(NULL));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int exp = rand();
			(*this)(i, j) = (exp % 100) * pow(-1.0, exp % 7);
		}
	}
	if (degen)
	{
		for (int i = 0; i < cols; i++)
		{
			(*this)(2, i) = (*this)(0, i) + (*this)(1, i);
			(*this)(3, i) = (*this)(0, i) - (*this)(1, i);
		}
	}
}

void Matrix::MakeIdentity()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == j)
				(*this)(i, j) = 1;
			else
				(*this)(i, j) = 0;
		}
	}
}

void Matrix::Swap_Rows(const int row1, const int row2)
{
	double *buff;
	buff = (*this)(row1);
	(*this)(row1) = (*this)(row2);
	(*this)(row2) = buff;
}

void Matrix::Swap_Cols(const int col1, const int col2)
{
	int rows = this->rows;
	for (int i = 0; i < rows; i++)
	{
		double buff = (*this)(i, col1);
		(*this)(i, col1) = (*this)(i, col2);
		(*this)(i, col2) = buff;
	}
}

void Matrix::Transpose()
{
	int new_rows = this->cols;
	int new_cols = this->rows;
	Matrix Transposed(new_rows, new_cols);

	for (int i = 0; i < new_cols; i++)
	{
		for (int j = 0; j < new_rows; j++)
		{
			Transposed(j, i) = (*this)(i, j);
		}
	}
	*this = Transposed;
}

void Matrix::Display()
{
	// std::ofstream writer("output.txt");
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			if (std::abs((*this)(i, j)) - 1e-14 > 0.0)
				std::cout << (*this)(i, j) << ' ';
			else
				std::cout << 0 << ' ';
		}
		std::cout << '\n';
	}
}
