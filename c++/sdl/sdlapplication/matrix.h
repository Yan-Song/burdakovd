#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

/*
typedef double MatrixRow[3];
typedef MatrixRow MatrixData[3];

// ���������� ����� ������
class Matrix
{
private:
    MatrixData A;

public:
    Matrix();

    Matrix(double m)
    {
        for(int i=0; i<3; ++i)
            for(int j=0; j<3; ++j)
                A[i][j] = i == j ? m : 0;
    }

    MatrixRow& operator [](int i)
    {
        return A[i];
    }

    const MatrixRow& operator [](int i) const
    {
        return A[i];
    }

    Matrix operator *(const Matrix& other) const;

    static Matrix Shift(const OldHomogeneousPoint2D& d);

    static Matrix Rotate(const double phi);

    inline static Matrix Rotate(const OldHomogeneousPoint2D& base, const double phi)
    {
        return Matrix::Shift(base) * Matrix::Rotate(phi) * Matrix::Shift(-base);
    }

    static Matrix Scale(const double kx, const double ky);

    inline static Matrix Scale(const OldHomogeneousPoint2D& base, const double kx, const double ky)
    {
        return Matrix::Shift(base) * Matrix::Scale(kx, ky) * Matrix::Shift(-base);
    }

    static Matrix ReflectX();

    inline static Matrix ReflectX(const double x)
    {
        return Matrix::Shift(OldHomogeneousPoint2D(x, 0)) * Matrix::ReflectX() * Matrix::Shift(OldHomogeneousPoint2D(-x, 0));
    }

    static Matrix ReflectY();

    inline static Matrix ReflectY(const double y)
    {
        return Matrix::Shift(OldHomogeneousPoint2D(0, y)) * Matrix::ReflectY() * Matrix::Shift(OldHomogeneousPoint2D(0, -y));
    }
};

OldHomogeneousVector2D operator *(const Matrix& A, const OldHomogeneousVector2D& b);
*/

#endif