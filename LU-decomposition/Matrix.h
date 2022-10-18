#pragma once
#include <iostream>
#include <algorithm>
#include <tuple> 
#include <limits>
#include <string>
#include <cmath>

class LU_Decomposer;

class Matrix
{
	/*на мой взгляд, стоит использовать дружественные классы, чтобы был доступ к полям матрицы у классов, выполн.
	свои задачи. я */
	friend class LU_Decomposer;

protected:
	int rows, cols;
	double** values;

public:
	//костыли для инициализации матриц
	void MakeIdentity();
	void MakeCustom();

	/*перегруженные операторы : умножение - умн-е матриц, скобки - индексация, присваивание - 
	копирование инициализированного объекта матрицы*/
	Matrix& operator* (const Matrix&);
	inline double& operator()(int, int);
	const inline double& operator()(int, int) const;
	inline double*& operator()(int);
	const inline double* operator()(int) const;
	Matrix& operator=(const Matrix&);

	/*конструкторы: по умолчанию - создает матрицу 1х1, перегруженный двумя интами - выделяет память для двум. массива 
	на n строк, m столбцов, копирования - копирует значения массива и полей
	деструктор: освобождает динамическую память, выделенную массиву значений */
	Matrix();
	Matrix(int n,int m);
	Matrix(const Matrix&);
	~Matrix();

	/*методы перестановки строк и столбцов для разложений*/
	void Swap_Rows(int,int);
	void Swap_Cols(int, int);

	/* дисплей - вывод матрицы, транспоус - транспозиция*/
	void Display();
	void Transpose();

};
