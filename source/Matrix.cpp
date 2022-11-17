#include "Matrix.h"

int Matrix::GetN()
{
    return n;
}

int Matrix::GetM()
{
    return m;
}

void Matrix::SwapRows(int ind_1, int ind_2)
{
    Row *temp = rows[ind_1];
    rows[ind_1] = rows[ind_2];
    rows[ind_2] = temp;
}

void Matrix::SwapCols(int ind_1, int ind_2)
{
    for (int i = 0; i < n; i++)
    {
        double temp = (*this)[i][ind_1];
        (*this)[i][ind_1] = (*this)[i][ind_2];
        (*this)[i][ind_2] = temp;
    }
}

Row &Matrix::operator[](int index)
{
    return (*rows[index]);
}

const Row &Matrix::operator[](int index) const
{
    return (*rows[index]);
}
Matrix &Matrix::operator=(const Matrix &ref)
{
    if (this->rows!=nullptr)
         this->~Matrix();
    this->n = ref.n;
    this->m = ref.m;
    this->rows = new Row *[n];
    for (int i = 0; i < n; i++)
        this->rows[i] = new Row(m);
    for (int i = 0; i < n; i++)
        (*this)[i] = ref[i];
    return *this;
}

Matrix::Matrix(const Matrix &ref)
{
    operator=(ref);
}

Matrix &Matrix::operator*(const Matrix &factor)
{
    int rows1 = this->n;
    int rows2 = factor.n;
    int cols1 = this->m;
    int cols2 = factor.m;
    if (cols1 != rows2)
    {
        throw std::invalid_argument("matrices can not be multiplied (different cols1 and rows2 number) \n");
    }
    Matrix *result = new Matrix(rows1, cols2);

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            (*result)[i][j] = 0;
            for (int k = 0; k < cols1; k++)
                (*result)[i][j] += (*this)[i][k] * factor[k][j];
        }
    }
    return *result;
}

Matrix &Matrix::operator+(const Matrix &term)
{
    if (this->n != term.n)
        throw std::invalid_argument("matrices can not be added (different rows number)\n");
    Matrix *result = new Matrix(n, m);
    for (int i = 0; i < this->n; i++)
    {
        (*result)[i] = (*this)[i] + term[i];
    }
    return *result;
}

Matrix &Matrix::operator-(const Matrix &term)
{
    if (this->n != term.n)
        throw std::invalid_argument("matrices can not be subtracted (different rows number)\n");
    Matrix *result = new Matrix(n, m);
    for (int i = 0; i < this->n; i++)
    {
        (*result)[i] = (*this)[i] - term[i];
    }
    return *result;
}

Matrix::Matrix()
{
    this->m = 1;
    this->n = 1;
    this->rows = new Row *[1];  //МА
    this->rows[0] = new Row[1]; //ТЬ
}

Matrix::Matrix(int n, int m)
{
    this->n = n;
    this->m = m;
    rows = new Row *[n];
    for (int i = 0; i < n; i++)
    {
        rows[i] = new Row(m);
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < n; i++)
    {
        (*rows[i]).~Row();
    }
    delete[] rows;
    rows=nullptr;
}

void Matrix::MakeRandom(bool degen)
{
    std::srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            (*this)[i][j] = rand() % 100 * pow(-1.0, rand() % 7);
        }
    }
    if (degen)
    {
        (*this)[3] = (*this)[1] - (*this)[0];
        (*this)[2] = (*this)[1] + (*this)[0];
    }
}

void Matrix::MakeCustom()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cin >> (*this)[i][j];
        }
    }
}

void Matrix::MakeIdentity()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == j)
                (*this)[i][j] = 1;
            else
                (*this)[i][j] = 0;
        }
    }
}

void Matrix::Display()
{
    for (int i = 0; i < n; i++)
    {
        (*this)[i].Display();
    }
}

Matrix Matrix::Transposed()
{
    Matrix *Tr = new Matrix(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
           (*Tr)[i][j] = (*this)[j][i];
        }
    }
    return *Tr;
}
