#pragma once
#include "../headers_1/Matrix.h"
class GR_Decomposer
{
private:
    void Decomposition();

public:
    GR_Decomposer(Matrix &);
    ~GR_Decomposer();
    Matrix *pInitialMatrix = nullptr;
    Matrix *pG = nullptr;
    Matrix *pR = nullptr;
};