#pragma once
#include "../headers/Matrix.h"
class GR_Decomposer
{
private:
    void Decomposition();
    Matrix *pInitialMatrix = nullptr;

public:
    GR_Decomposer(Matrix &);
    ~GR_Decomposer();
    
    Matrix *pG = nullptr;
    Matrix *pR = nullptr;
};