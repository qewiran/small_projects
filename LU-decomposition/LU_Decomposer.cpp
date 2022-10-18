#include "LU_Decomposer.h"


LU_Decomposer::LU_Decomposer(Matrix& InitialMatrix)
{
	this->InitialMatrix = InitialMatrix;
	int rows = InitialMatrix.rows;
	int cols = InitialMatrix.cols;
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

std::tuple <double, int, int> LU_Decomposer::Get_Max(Matrix& Matrix, int start_index)
{
	int max_row = 0, max_col = 0;
	double matrix_max = DBL_MIN;
	int rows = Matrix.rows;
	int cols = Matrix.cols;
	for (int j = start_index; j < rows; j++)
	{
		for (int k = start_index; k < cols; k++)
		{
			if (Matrix(j, k) > matrix_max)
			{
				matrix_max = Matrix(j, k);
				max_row = j;
				max_col = k;
			}
		}
	}
	return std::make_tuple(matrix_max, max_row, max_col);
}

void LU_Decomposer::Decomposition()
{
	int rows = InitialMatrix.rows;
	int cols = InitialMatrix.cols;
	Matrix Copy = InitialMatrix;
	
	for (int i = 0; i < rows; i++)
	{
		auto t = Get_Max(Copy, i);
		double matrix_max = std::get<0>(t);
		int max_row = std::get<1>(t);
		int max_col = std::get<2>(t);

		(*Q).Swap_Cols(i, max_col);
		(*P).Swap_Rows(i, max_row);

		Copy.Swap_Rows(i, max_row);
		Copy.Swap_Cols(i, max_col);

		for (int j = i + 1; j < rows; j++)
		{
			Copy(j,i) /= Copy(i, i);

			for (int k = i + 1; k < cols; k++)
			{
				Copy(j,k) -= Copy(i, k) * Copy(j, i);
			}
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i > j)
				(*L)(i,j) = Copy(i, j);
			else
				(*U)(i, j) = Copy(i, j);
		}
	}

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

Matrix LU_Decomposer::EquationSolution(Matrix& B)
{
	
	int sol_cols = B.cols;
	int sol_rows = InitialMatrix.rows;

	Matrix y(sol_rows, sol_cols);

	for (int i = 0; i < sol_rows; ++i)
	{
		for (int j = 0; j < sol_cols; ++j)
		{
			y(i,j) = B(i, j);
			for (int k = 0; k < i; ++k)
			{
				y(i, j) -= (*L)(i, k) * y(k, j);
			}
		}
	}

	Matrix z(sol_rows, sol_cols);

	for (int i = sol_rows - 1; i >=0; --i)
	{
		for (int j = 0; j < sol_cols; ++j)
		{
			z(i,j) = y(i, j);

			for (int k = i+1; k < sol_rows; ++k)
			{
				z(i, j) -= (*U)(i, k) * z(k, j);
			}
			z(i, j) /= (*U)(i, i);
		}
	}

Matrix* x = new Matrix(sol_rows, sol_cols);
*x = (*Q) * z;

return *x;
}

Matrix LU_Decomposer::GetInverted()
{
	Matrix I(InitialMatrix.rows, InitialMatrix.cols);
	I.MakeIdentity();
	I = I * (*P);
	return EquationSolution(I);
}
