#pragma once
#include <cstdlib>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <ctime>
#include <iostream>

class LU_Decomposer;
class GR_Decomposer;
class Iteration_Method;

class Matrix
{
    friend class LU_Decomposer;
    friend class GR_Decomposer;
    friend class Iteration_Method;

private:
    int n = 0, m = 0;
    int rank = 0;
    std::vector<std::vector<double>> rows;
    void SwapCols(int, int);
    void SwapRows(int, int);

public:
    int GetRank() const;
    int GetN() const;
    int GetM() const;
    double max_row_abs = 0.0;

    void MakeRandom(bool);
    void MakeCustom();
    void MakeIdentity();

    Matrix() = default;
    Matrix(int, int);
    Matrix(const Matrix &);
    Matrix(Matrix &&) noexcept;
    ~Matrix() = default;

    Matrix &operator*(const Matrix &);
    Matrix &operator*(const double k);
    Matrix &operator+(const Matrix &);
    Matrix &operator-(const Matrix &);
    Matrix &operator=(Matrix);
    std::vector<double> &operator[](int);
    const std::vector<double> &operator[](int) const;
    void swap(Matrix &matrix1, Matrix &matrix2) noexcept;

    Matrix Transposed() const;
    void Display() const;
    double Norm() const;
};

std::vector<double> operator+(const std::vector<double> &v1,
                              const std::vector<double> &v2);

std::vector<double> operator-(const std::vector<double> &v1,
                              const std::vector<double> &v2);

std::vector<double> operator*(const std::vector<double> &v1, double k);
