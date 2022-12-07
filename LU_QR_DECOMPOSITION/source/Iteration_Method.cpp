
#include "../headers/Iteration_Method.h"
#include "../headers/GR_Decomposer.h"
#include "../headers/LU_Decomposer.h"

void Iteration_Method::Decomposition()
{
    int n = pInitialMatrix->n;
    int m = pInitialMatrix->m;
    pD = new Matrix(n, m);
    pL = new Matrix(n, m);
    pR = new Matrix(n, m);
    for (int i = 0, j = 1; i < pInitialMatrix->n; i++, ++j)
    {
        if (std::abs((*pInitialMatrix)[i][i]) - pInitialMatrix->max_row_abs < 0.0)
            (*pD)[i][i] = pInitialMatrix->max_row_abs + (*pInitialMatrix)[i][i];
        else
            (*pD)[i][i] = (*pInitialMatrix)[i][i];

        std::copy((*pInitialMatrix)[i].begin(),
                  (*pInitialMatrix)[i].begin() + (j - 1), (*pL)[i].begin());

        std::copy((*pInitialMatrix)[i].begin() + j,
                  (*pInitialMatrix)[i].end(), (*pR)[i].begin() + j);
    }
}

Matrix Iteration_Method::JacobiSolution()
{
    double q = this->q;
    int k = 1;
    Matrix prev_iteration(*pC);
    Matrix curr_iteration = prev_iteration;
    double norm = curr_iteration.Norm();
    while (q / (1 - q) * norm > 1e-13)
    {
        curr_iteration = (*pB) * prev_iteration + (*pC);
        auto diff = curr_iteration - prev_iteration;
        norm = diff.Norm();
        // std::cout << norm << "\n";
        ++k;
        prev_iteration = curr_iteration;
    }
    std::cout << "K: " << k << "\n";
    return curr_iteration;
}

Matrix Iteration_Method::SeidelSolution()
{
    double q = this->q;
    int k = 1;
    int n = pInitialMatrix->n;
    Matrix prev_iteration(*pC);
    Matrix curr_iteration = prev_iteration;
    double norm = curr_iteration.Norm();
    while (q / (1 - q) * norm > 1e-13)
    {
        for (int i = 0; i < n; i++)
        {
            curr_iteration[i][0] = 0.0;
            for (int j = 0; j < i; j++)
            {
                curr_iteration[i][0] += (*pB_l)[i][j] * curr_iteration[j][0];
            }
            for (int j = i; j < n; j++)
            {
                curr_iteration[i][0] += (*pB_r)[i][j] * prev_iteration[j][0];
            }
            curr_iteration[i][0] += (*pC)[i][0];
        }
        norm = (curr_iteration - prev_iteration).Norm();
        ++k;
        prev_iteration = curr_iteration;
    }
    std::cout << "K: " << k << "\n";
    return curr_iteration;
}

Iteration_Method::Iteration_Method(const Matrix &A, const Matrix &b)
{
    using std::log;
    pInitialMatrix = new Matrix;
    *pInitialMatrix = A;

    pB = new Matrix;
    pB_l = new Matrix;
    pB_r = new Matrix;
    pC = new Matrix;
    Decomposition();

    Matrix &L = *pL;
    Matrix &R = *pR;
    Matrix &D = *pD;

    for (int i = 0; i < pInitialMatrix->n; i++)
        (*pInitialMatrix)[i][i] = D[i][i];

    LU_Decomposer LU_D(D);
    std::cout << (*pInitialMatrix).max_row_abs << "\n";

    D = LU_D.GetInverted();
    Matrix B = D * (L + R) * (-1.0);
    Matrix B_l = D * L * (-1.0);
    Matrix B_r = D * R * (-1.0);
    Matrix C = D * b;

    *pB = std::move(B);
    *pB_l = std::move(B_l);
    *pB_r = std::move(B_r);
    *pC = std::move(C);

    double B_norm = (*pB).Norm();
    double C_norm = (*pC).Norm();
    std::cout << B_norm << " :b norm and c norm: " << C_norm << '\n';
    B_norm - 1.0 > 1e-14 ? q = 0.1 : q = B_norm;
    double k = std::ceil(log(1e-13 / C_norm * (1 - q)) / log(q));
    std::cout << "calculated k:" << k << '\n';
}

Iteration_Method::~Iteration_Method()
{
    if (pL != nullptr)
        pL->~Matrix();

    if (pD != nullptr)
        pD->~Matrix();

    if (pR != nullptr)
        pR->~Matrix();
}