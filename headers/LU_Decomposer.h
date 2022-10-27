#pragma once
#include "Matrix.h"

class LU_Decomposer
{
private:
	void Decomposition();
	std::tuple<double, int, int> Get_Max(Matrix &, int index);
	void SetSquare(Matrix&);
	bool KroneckerCopelli(Matrix&);
public: 
	LU_Decomposer(Matrix *);
	~LU_Decomposer();
	Matrix *InitialMatrix;
	Matrix *L;
	Matrix *P;
	Matrix *U;
	Matrix *Q;

	int GetRank();
	double Get_Determinant();
	Matrix EquationSolution(Matrix &);
	Matrix GetInverted();
	double GetConditionNumber();
};
