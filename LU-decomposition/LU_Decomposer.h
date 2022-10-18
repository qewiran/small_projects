#pragma once
#include "Matrix.h"

class LU_Decomposer
{
private:
	void Decomposition();
	std::tuple<double, int, int> Get_Max(Matrix&, int index);
public:
	Matrix InitialMatrix;
	Matrix* L; Matrix* P; Matrix* U; Matrix* Q;

	LU_Decomposer(Matrix&);

	double Get_Determinant(); 
	Matrix EquationSolution(Matrix&);
	Matrix GetInverted();

};