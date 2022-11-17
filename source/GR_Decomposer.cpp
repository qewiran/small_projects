#include "GR_Decomposer.h"
GR_Decomposer::GR_Decomposer(Matrix &initialMatrix)
{
    pInitialMatrix = &initialMatrix;
    int N = initialMatrix.n;
    int M = initialMatrix.m;
    pG = new Matrix(N, M);
    Decomposition();
}
GR_Decomposer::~GR_Decomposer()
{
    pInitialMatrix = nullptr;
    if (pG != nullptr)
        pG->~Matrix();
    if (pR != nullptr)
        pR->~Matrix();
}
double VecNorm(Row &a)
{
    double result = 0;
    int n = a.GetLength();
    for (int i = 0; i < n; i++)
    {
        result += a[i] * a[i];
    }
    return std::sqrt(result);
}

double Dot(Row &a, Row &b)
{
    int n = a.GetLength();
    double result = 0;

    if (a.GetLength() != b.GetLength())
        throw std::invalid_argument("rows have diff-t lengths (dot)");
        
    for (int i = 0; i < n; i++)
    {
        result += a[i] * b[i];
    }
    return result;
}

Row Proj(Row &a, Row &b)
{

    int n = a.GetLength();
    int m = n;

    if (a.GetLength() != b.GetLength())
        throw std::invalid_argument("rows have diff-t lengths (proj)");

    double k = Dot(a, b) / Dot(b, b);
    Row *result = new Row(n);
    for (int i = 0; i < n; i++)
    {
        (*result)[i] = b[i] * k;
    }
    return *result;
}

void GR_Decomposer::Decomposition()
{
    int N = pInitialMatrix->n;
    int M = pInitialMatrix->m;
    for (int i = 0; i < N; i++)
    {
        (*pG)[i] = (*pInitialMatrix)[i];
        for (int j = 0; j < i; j++)
        {
            (*pG)[i] = (*pG)[i] - Proj((*pInitialMatrix)[i], (*pG)[j]);
        }
        double norm = VecNorm((*pG)[i]);
        (*pG)[i]=(*pG)[i]*(1/norm);
    }
    // pG->Display();
    Matrix Gt = (*pG).Transposed();
    pR = new Matrix(pInitialMatrix->n, pInitialMatrix->m);
    *pR = Gt*(*pInitialMatrix);
}