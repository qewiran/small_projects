#pragma once
#include <iostream>
#include <algorithm>
#include <tuple>
#include <string>
#include <cmath>
#include <ctime>
#include <chrono>
#include <immintrin.h>
class LU_Decomposer;

class Matrix
{

	friend class LU_Decomposer;

protected:
	int rows, cols;
	double **values;

public:
	void MakeIdentity();
	void MakeRandom(bool);
	void MakeCustom();

	Matrix &operator*(const Matrix &);
	double &operator()(int, int);
	const double &operator()(int, int) const;
	double *&operator()(int);
	const double *operator()(int) const;
	Matrix &operator=(const Matrix &);

	Matrix();
	Matrix(int n, int m);
	Matrix(const Matrix &);
	~Matrix();

	void Swap_Rows(int, int);
	void Swap_Cols(int, int);

	void Display();
	void Transpose();
};
