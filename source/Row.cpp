#include "Row.h"

#include <iostream>

double &Row::operator[](int index)
{
    return values[index];
}

double &Row::operator[](int index) const
{
    return values[index];
}

int Row::GetLength()
{
    return this->len;
}

void Row::Display()
{
    for (int i = 0; i < len; i++)
    {
        if (std::abs((*this)[i]) - 1e-10 > 0.0)
            std::cout << (*this)[i] << " ";
        else
            std::cout << 0 << ' ';
    }
    std::cout << "\n";
}

Row &Row::operator*(const double k)
{
    int N = this->len;
    for (int i = 0; i < N; i++)
    {
        (*this)[i] *= k;
    }
    return *this;
}

Row &Row::operator*(const __m512d coeff_v)
{
    Row *mul = new Row(len);

    int i = 0;
    for (; i < len - len % 8; i += 8)
    {
        _mm512_store_pd(&(*mul)[i], _mm512_mul_pd(_mm512_load_pd(&(*this)[i]), coeff_v));
    }
    for (; i < len; i++)
    {
        (*mul)[i] = (*this)[i] * coeff_v[0];
    }
    return *mul;
}

Row &Row::operator=(const Row &ref)
{
    if (this->len != ref.len)
    {
        this->len = ref.len;
        if (this->values != nullptr)
            delete[] this->values;
        this->values = new double[len];
    }
    std::copy(ref.values, ref.values + ref.len, this->values);
    return *this;
}

Row &Row::operator-(const Row &subtr)
{
    if (this->len < subtr.len)
        throw std::invalid_argument("rows can not be added");
    Row *diff = new Row(len);
    for (int i = 0; i < len; i++)
        (*diff)[i] = (*this)[i] - subtr[i];
    return *diff;
}

Row &Row::operator+(const Row &term)
{
    if (this->len < term.len)
        throw std::invalid_argument("rows can not be subtracted");
    Row *sum = new Row(len);
    for (int i = 0; i < len; i++)
        (*sum)[i] = (*this)[i] + term[i];
    return *sum;
}

Row::Row(const Row &ref)
{
    operator=(ref);
}

Row::Row()
{
    values = new double[1];
    values[0] = 0;
}

Row::Row(int m)
{
    if (values != nullptr)
        delete[] values;
    this->len = m;
    values = new double[m];
    for (int i = 0; i < m; i++)
        values[i] = 0;
}

Row::~Row()
{
    delete[] values;
}