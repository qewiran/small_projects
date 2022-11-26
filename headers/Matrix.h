#pragma once
#include <cstdlib>
#include <vector>
#include <cmath>
#include "Row.h"
class LU_Decomposer;
class GR_Decomposer;

class Matrix
{
    friend class LU_Decomposer;
    friend class GR_Decomposer;

private:
    int n = 0, m = 0;
    int rank = 0;
    Row **rows = nullptr;
    void SwapCols(int, int);
    void SwapRows(int, int);

public:
    void SetRank(int);
    int GetRank();
    int GetN();
    int GetM();

    void MakeRandom(bool);
    void MakeCustom();
    void MakeIdentity();

    Matrix();

    Matrix(int, int);
    Matrix(const Matrix &);
    ~Matrix();

    Matrix &operator*(const Matrix &);
    Matrix &operator+(const Matrix &);
    Matrix &operator-(const Matrix &);
    Matrix &operator=(const Matrix &);
    Row &operator[](int);
    const Row &operator[](int) const;

    Matrix Transposed();
    void Display();
};