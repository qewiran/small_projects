#include "LU_Decomposer.h"

LU_Decomposer::LU_Decomposer(Matrix *InitialMatrix)
{
	SetSquare(*InitialMatrix);
	this->InitialMatrix = InitialMatrix;
	int rows = (*InitialMatrix).rows;
	int cols = (*InitialMatrix).cols;
	L = new Matrix(rows, cols);
	U = new Matrix(rows, cols);
	P = new Matrix(rows, cols);
	Q = new Matrix(rows, cols);
	(*L).MakeIdentity();
	(*U).MakeIdentity();
	(*P).MakeIdentity();
	(*Q).MakeIdentity();
	Decomposition();
}

LU_Decomposer::~LU_Decomposer()
{
	L->~Matrix();
	U->~Matrix();
	P->~Matrix();
	Q->~Matrix();
}

std::tuple<double, int, int> LU_Decomposer::Get_Max(Matrix &matrix, int start_index)
{
	int max_row = start_index, max_col = start_index;
	double matrix_max = matrix(start_index, start_index);

	int rows = matrix.rows;
	int cols = matrix.cols;
	for (int j = start_index; j < rows; j++)
	{
		for (int k = start_index; k < cols; k++)
		{
			if (std::abs(matrix(j, k)) > std::abs(matrix_max))
			{
				matrix_max = matrix(j, k);
				max_row = j;
				max_col = k;
			}
		}
	}
	return std::make_tuple(matrix_max, max_row, max_col);
}

bool LU_Decomposer::KroneckerCopelli(Matrix &B)
{
	bool result = false;
	int rows = InitialMatrix->rows;
	int cols = InitialMatrix->cols;

	Matrix Copy(rows, cols + B.cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < B.cols; j++)
		{
			if (j < cols)
				Copy(i, j) = (*InitialMatrix)(i, j);
			else
				Copy(i, j) = B(i, j);
		}
	}
	LU_Decomposer dec(&Copy);

	int rank_init = this->GetRank();
	int rank_expanded = dec.GetRank();

	if (rank_init == rank_expanded)
		result = true;
	return result;
}

void LU_Decomposer::SetSquare(Matrix &matrix)
{
	int rows = matrix.rows;
	int cols = matrix.cols;
	if (rows < cols)
	{
		for (int i = rows; i < cols; i++)
		{
			matrix(i) = new double[cols];
			for (int j = 0; j < cols; j++)
			{
				matrix(i, j) = 0;
			}
		}
		matrix.rows = cols;
	}
	else if (rows > cols)
	{
		for (int i = 0; i < rows; i++)
		{
			double *temp = new double[rows];
			for (int j = cols; j < rows; j++)
			{
				temp[j] = 0;
			}
			std::copy(temp,temp+rows, matrix(i));
			delete[] temp;
		}
		matrix.cols = rows;
	}
}

void LU_Decomposer::Decomposition()
{
	int rows = (*InitialMatrix).rows;
	int cols = (*InitialMatrix).cols;
	Matrix Copy = *InitialMatrix;

	for (int i = 0; i < rows; i++)
	{

		auto t = Get_Max(Copy, i);
		int max_row = std::get<1>(t);
		int max_col = std::get<2>(t);
		(*Q).Swap_Cols(i, max_col);
		(*P).Swap_Rows(i, max_row);

		Copy.Swap_Rows(i, max_row);
		Copy.Swap_Cols(i, max_col);

		if (abs(Copy(i, i)) - 1e-13 < 0.0)
			break;
		for (int j = i + 1; j < rows; j++)
		{

			Copy(j, i) /= Copy(i, i);
			for (int k = i + 1; k < cols; k++)
			{
				Copy(j, k) -= Copy(i, k) * Copy(j, i);
			}
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i > j)
				(*L)(i, j) = Copy(i, j);
			else
				(*U)(i, j) = Copy(i, j);
		}
	}
}

int LU_Decomposer::GetRank()
{
	int rank = 0;
	int rows = U->rows;
	for (int i = 0; i < rows; i++)
	{
		if (abs((*U)(i, i)) - 1e-14 > 0.0)
			rank++;
	}
	return rank;
}

double LU_Decomposer::Get_Determinant()
{
	double det = 1;
	for (int i = 0; i < (*L).rows; i++)
	{
		det *= (*L)(i, i) * (*U)(i, i);
	}
	return det;
}

Matrix LU_Decomposer::EquationSolution(Matrix &B)
{
	// if (!KroneckerCopelli(B))
	// {
	// 	std::cout << "не совместна \n";
	// 	return *(new Matrix());
	// }

	int sol_cols = B.cols;
	int sol_rows = (*InitialMatrix).rows;

	Matrix y(sol_rows, sol_cols);

	for (int i = 0; i < sol_rows; ++i)
	{
		for (int j = 0; j < sol_cols; ++j)
		{
			y(i, j) = B(i, j);
			for (int k = 0; k < i; ++k)
			{
				y(i, j) -= (*L)(i, k) * y(k, j);
			}
		}
	}

	Matrix z(sol_rows, sol_cols);

	for (int i = sol_rows - 1; i >= 0; --i)
	{
		for (int j = 0; j < sol_cols; ++j)
		{
			z(i, j) = y(i, j);

			for (int k = i + 1; k < sol_rows; ++k)
			{
				z(i, j) -= (*U)(i, k) * z(k, j);
			}
			z(i, j) /= (*U)(i, i);
		}
	}
	Matrix *x = new Matrix(sol_rows, sol_cols);
	*x = (*Q) * z;

	return *x;
}

Matrix LU_Decomposer::GetInverted()
{
	Matrix I((*InitialMatrix).rows, (*InitialMatrix).cols);
	I.MakeIdentity();
	I = I * (*P);
	return EquationSolution(I);
}

double LU_Decomposer::GetConditionNumber()
{
	double result = 0;
	double L_norm = 0;
	for (int i = 0; i < L->cols; i++)
	{
		double buf = 0;
		for (int j = i; j < L->rows; j++)
		{
			buf += (*L)(j, i);
		}
		L_norm = std::max(L_norm, buf);
	}
	return result;
}