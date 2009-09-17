#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

/* мутный вектор
   сложение, умножение на скаляр и вычитание тут идёт не покомпонентно
   а так, чтобы оно было аналогично параллельному переносу или растяжению.
*/
class Vector
{
public:
	double x, y, k;

	Vector(): x(0), y(0), k(1) {};

	Vector(double xx, double yy): x(xx), y(yy), k(1) {};

	Vector(double xx, double yy, double kk):
		x(xx),
		y(yy),
        k(kk)
		{};

    inline double X() const
    {
        return x / k;
    }

    inline double Y() const
    {
        return y / k;
    }

    double& operator [](int index)
    {
        return *(index + &x);
    }

    const double& operator [](int index) const
    {
        return *(index + &x);
    }

    Vector operator -() const
    {
        return Vector(-x, -y, k);
    }
};

std::ostream& operator<<(std::ostream& os, const Vector& v);

typedef Vector Point;

#endif
