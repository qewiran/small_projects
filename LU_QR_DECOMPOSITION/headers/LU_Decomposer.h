#pragma once
#include "../headers/Matrix.h"
#include <tuple>

class LU_Decomposer
{
private:
    void Decomposition();
    void SetSquare();
    bool IsCompatible(const Matrix &);
    Matrix *pInitialMatrix = nullptr;

public:
    LU_Decomposer(Matrix &);
    ~LU_Decomposer();
    
    Matrix *pL = nullptr;
    Matrix *pP = nullptr;
    Matrix *pU = nullptr;
    Matrix *pQ = nullptr;

    int GetRank();
    double GetDeterminant();
    Matrix EquationSolution(const Matrix &);
    Matrix GetInverted();
    double GetConditionNumber();
};
