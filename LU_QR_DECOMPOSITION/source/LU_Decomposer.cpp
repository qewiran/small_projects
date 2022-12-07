#include "../headers/Matrix.h"
#include "../headers/LU_Decomposer.h"
#define out(a) std::cout << a << ": \n";

std::tuple<double, int, int> GetMax(const Matrix &matrix, int start_index)
{
    int max_row = start_index, max_col = start_index;
    double matrix_max = matrix[start_index][start_index];
    int N = matrix.GetN();
    int M = matrix.GetM();

    for (int j = start_index; j < N; j++)
    {
        for (int k = start_index; k < M; k++)
        {
            if (std::abs(matrix[j][k]) > std::abs(matrix_max))
            {
                matrix_max = matrix[j][k];
                max_row = j;
                max_col = k;
            }
        }
    }
    return std::make_tuple(matrix_max, max_row, max_col);
}

void LU_Decomposer::SetSquare()
{
    int N = pInitialMatrix->n;
    int M = pInitialMatrix->m;
    if (N < M)
    {
        pInitialMatrix->rows.resize(M, std::vector<double>(M));
    }
    else if (N > M)
    {
        for (int i = 0; i < N; i++)
        {
            (*pInitialMatrix)[i].resize(N);
        }
    }
    else
        std::cout << "squared\n";
}

void LU_Decomposer::Decomposition()
{
    int N = pInitialMatrix->n;
    int M = pInitialMatrix->m;
    Matrix Copy = *pInitialMatrix;
    Matrix &Q = *pQ; //ээээ
    Matrix &P = *pP; //нууу
    Matrix &L = *pL;
    Matrix &U = *pU;
    for (int i = 0; i < N; i++)
    {
        auto t = GetMax(Copy, i);
        int max_row = std::get<1>(t);
        int max_col = std::get<2>(t);

        Q.SwapCols(i, max_col);
        P.SwapRows(i, max_row);

        Copy.SwapRows(i, max_row);
        Copy.SwapCols(i, max_col);

        if (std::abs(Copy[i][i]) - 1e-12 < 0.0)
        {
            pInitialMatrix->rank = i;
            break;
        }
        else
            pInitialMatrix->rank = i + 1;
        for (int j = i + 1; j < N; j++)
        {
            Copy[j][i] /= Copy[i][i];
            for (int k = i + 1; k < M; k++)
            {
                Copy[j][k] -= Copy[i][k] * Copy[j][i];
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (i > j)
                L[i][j] = Copy[i][j];
            else
                U[i][j] = Copy[i][j];
        }
    }
}

bool LU_Decomposer::IsCompatible(const Matrix &y)
{
    int N = pU->n;
    bool is_compatible = true;
    for (int i = 0; i < N; i++)
    {
        if (std::abs((*pU)[i][i]) - 1e-10 < 0.0)
        {
            for (int j = 0; j < y.m; j++)
            {
                if (std::abs(y[i][j]) - 1e-12 > 0.0)
                {
                    is_compatible = false;
                    break;
                }
            }
        }
        if (is_compatible == false)
            break;
    }
    return is_compatible;
}

Matrix LU_Decomposer::EquationSolution(const Matrix &B)
{
    int M = B.m;
    int N = (*pInitialMatrix).n;

    Matrix y(N, M);

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            y[i][j] = B[i][j];
            for (int k = 0; k < i; ++k)
            {
                y[i][j] -= (*pL)[i][k] * y[k][j];
            }
        }
    }
    if (!IsCompatible(y))
        throw std::invalid_argument("slae is not compatible\n");

    Matrix z(N, M);
    for (int i = N - 1; i >= 0; --i)
    {
        for (int j = 0; j < M; ++j)
        {
            z[i][j] = y[i][j];
        }
        if (i >= pInitialMatrix->GetRank())
            continue;
        for (int j = 0; j < M; ++j)
        {
            for (int k = i + 1; k < N; ++k)
            {
                z[i][j] -= (*pU)[i][k] * z[k][j];
            }
            z[i][j] /= (*pU)[i][i];
        }
    }

    return (*pQ) * z;
}

Matrix LU_Decomposer::GetInverted()
{
    Matrix I(pInitialMatrix->n, pInitialMatrix->m);
    I.MakeIdentity();
    return EquationSolution(I * (*pP));
}
LU_Decomposer::LU_Decomposer(Matrix &InitialMatrix)
{
    //SetSquare();
    this->pInitialMatrix = &InitialMatrix;
    int N = InitialMatrix.n;
    int M = InitialMatrix.m;
    pL = new Matrix(N, M);
    pU = new Matrix(N, M);
    pP = new Matrix(N, M);
    pQ = new Matrix(N, M);
    (*pL).MakeIdentity();
    (*pU).MakeIdentity();
    (*pP).MakeIdentity();
    (*pQ).MakeIdentity();
    Decomposition();
}

LU_Decomposer::~LU_Decomposer()
{
    pInitialMatrix = nullptr;
    pL->~Matrix();
    pU->~Matrix();
    pQ->~Matrix();
    pP->~Matrix();
}