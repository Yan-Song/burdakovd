#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

typedef double MatrixRow[3];
typedef MatrixRow MatrixData[3];

// нормальный класс матриц
class Matrix
{
private:
    MatrixData A;

public:
    Matrix();

    MatrixRow& operator [](int i)
    {
        return A[i];
    }

    const MatrixRow& operator [](int i) const
    {
        return A[i];
    }

    Matrix operator *(const Matrix& other) const;

    static Matrix Shift(const Point& d);

    static Matrix Rotate(const double phi);

    inline static Matrix Rotate(const Point& base, const double phi)
    {
        return Matrix::Shift(base) * Matrix::Rotate(phi) * Matrix::Shift(-base);
    }

    static Matrix Scale(const double kx, const double ky);

    inline static Matrix Scale(const Point& base, const double kx, const double ky)
    {
        return Matrix::Shift(base) * Matrix::Scale(kx, ky) * Matrix::Shift(-base);
    }

    static Matrix ReflectX();

    static Matrix ReflectY();
};

Vector operator *(const Matrix& A, const Vector& b);


#endif
