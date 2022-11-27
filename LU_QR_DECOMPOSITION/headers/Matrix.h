#pragma once
#include <cstdlib>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <ctime>
#include <iostream>
class LU_Decomposer;
class GR_Decomposer;

class Matrix
{
    friend class LU_Decomposer;
    friend class GR_Decomposer;

private:
    int n = 0, m = 0;
    int rank = 0;
    std::vector<std::vector<double>> rows;
    void SwapCols(int, int);
    void SwapRows(int, int);

public:
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
    std::vector<double> &operator[](int);
    const std::vector<double> &operator[](int) const;

    Matrix Transposed();
    void Display();
};

std::vector<double> operator+(const std::vector<double> &v1, const std::vector<double> &v2);

std::vector<double> operator-(const std::vector<double> &v1, const std::vector<double> &v2);

std::vector<double> operator*(const std::vector<double> &v1, double k);
