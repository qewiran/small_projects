#pragma once
#include "Matrix.h"

class LU_Decomposer
{
private:
    void Decomposition();
    void SetSquare(Matrix &);
    bool IsCompatible(const Matrix&);

public:
    LU_Decomposer(Matrix &);
    ~LU_Decomposer();
    Matrix *pInitialMatrix=nullptr;
    Matrix *pL=nullptr;
    Matrix *pP=nullptr;
    Matrix *pU=nullptr;
    Matrix *pQ=nullptr;

    int GetRank();
    double GetDeterminant();
    Matrix EquationSolution(const Matrix &);
    Matrix GetInverted();
    double GetConditionNumber();
};
