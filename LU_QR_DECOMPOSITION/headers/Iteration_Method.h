#pragma once
#include "../headers/Matrix.h"
class Iteration_Method
{
private:
    void Decomposition();
    double q;

public:
    Matrix *pInitialMatrix = nullptr;
    Iteration_Method(const Matrix &, const Matrix &);
    ~Iteration_Method();
    Matrix JacobiSolution();
    Matrix SeidelSolution();
    Matrix *pR = nullptr;
    Matrix *pD = nullptr;
    Matrix *pL = nullptr;
    Matrix *pB = nullptr;
    Matrix *pB_l = nullptr;
    Matrix *pB_r = nullptr;
    Matrix *pC = nullptr;
};