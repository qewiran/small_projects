class Matrix;
class Row
{
    friend class Matrix;

private:
    int len;
    double *values = nullptr;

public:
    Row();
    Row(int);
    Row(const Row &);
    ~Row();
    Row &operator=(const Row &);
    Row &operator-(const Row &);
    Row &operator+(const Row &);
    double &operator[](int);
    double &operator[](int) const;

    void Display();
};