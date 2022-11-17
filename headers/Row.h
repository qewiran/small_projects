#pragma once
class Matrix;
//class LU_Decomposer;
class Row
{
    friend class Matrix;
    //friend class LU_decomposer;
private:
    int len=0;
    double *values = nullptr;

public:
    Row();
    Row(int);
    Row(const Row &);
    ~Row();
    Row &operator*(const double);
    Row &operator=(const Row &);
    Row &operator-(const Row &);
    Row &operator+(const Row &);
    double &operator[](int);
    double &operator[](int) const;
    int GetLength();
    void Display();
};