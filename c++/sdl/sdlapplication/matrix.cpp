#include "matrix.h"
#include "Vector.h"
#include <cmath>

Matrix::Matrix()
{
    for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
            A[i][j] = 0;
}

Matrix Matrix::operator *(const Matrix &other) const
{
    Matrix m;

    for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
        {
            m[i][j] = 0;

            for(int k=0; k<3; ++k)
                m[i][j] += A[i][k] * other[k][j];
        }

    return m;
}

Matrix Matrix::Rotate(const double phi)
{
    Matrix m;

    m[0][0] = cos(phi);
    m[0][1] = sin(phi);
    m[1][0] = - sin(phi);
    m[1][1] = cos(phi);
    m[2][2] = 1;

    return m;
}

Matrix Matrix::Scale(const double kx, const double ky)
{
    Matrix m;

    m[0][0] = kx;
    m[1][1] = ky;
    m[2][2] = 1;

    return m;
}

Matrix Matrix::ReflectX()
{
    Matrix m;

    m[0][0] = -1;
    m[1][1] = 1;
    m[2][2] = 1;

    return m;
}

Matrix Matrix::ReflectY()
{
    Matrix m;

    m[0][0] = 1;
    m[1][1] = -1;
    m[2][2] = 1;

    return m;
}

Matrix Matrix::Shift(const OldHomogeneousPoint2D& d)
{
    Matrix m;

    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;
    m[0][2] = d.X();
    m[1][2] = d.Y();

    return m;
}

OldHomogeneousVector2D operator *(const Matrix& A, const OldHomogeneousVector2D& b)
{
    OldHomogeneousVector2D v;
    for(int i = 0; i < 3; ++i)
    {
        v[i] = 0;
        for(int j = 0; j < 3; ++j)
            v[i] += A[i][j] * b[j];
    }
    return v;
}
