#include "Row.h"
#include <algorithm>
#include <iostream>

double &Row::operator[](int index)
{
    return values[index];
}

double &Row::operator[](int index) const
{
    return values[index];
}

void Row::Display()
{
    for (int i = 0; i < len; i++)
        std::cout << (*this)[i] << " ";
    std::cout << "\n";
}

Row &Row::operator=(const Row &ref)
{
    len = ref.len;
    std::copy(ref.values, ref.values + len, values);
    return *this;
}

Row &Row::operator-(const Row &subtr)
{
    if (this->len < subtr.len)
        throw std::invalid_argument("первая строчка короче второй (вычитание)");
    Row *diff = new Row(len);
    for (int i = 0; i < len; i++)
        (*diff)[i] = (*this)[i] - subtr[i];
    return *diff;
}

Row &Row::operator+(const Row &term)
{
    if (this->len < term.len)
        throw std::invalid_argument("первая строчка короче второй (сложение)");
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
    len = m;
    values = new double[m];
    for (int i = 0; i < m; i++)
        values[i] = 0;
}

Row::~Row()
{
    delete[] values;
}