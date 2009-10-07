#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

#define sqr(x) ((x) * (x))
#define mset(x, value) memset(x, value, sizeof(x))

/* мутный вектор
   сложение, умножение на скаляр и вычитание тут идёт не покомпонентно
   а так, чтобы оно было аналогично параллельному переносу или растяжению.
*/
class OldHomogeneousVector2D
{
private:
	double x, y, k;
 
public:
	OldHomogeneousVector2D(): x(0), y(0), k(1) {};

	OldHomogeneousVector2D(double xx, double yy): x(xx), y(yy), k(1) {};

	OldHomogeneousVector2D(double xx, double yy, double kk):
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

    OldHomogeneousVector2D operator -() const
    {
        return OldHomogeneousVector2D(-x, -y, k);
    }

    inline OldHomogeneousVector2D operator +(const OldHomogeneousVector2D& other) const
    {
        return OldHomogeneousVector2D(x * other.k + other.x * k, y * other.k + other.y * k, k * other.k); 
    }

    inline OldHomogeneousVector2D operator -(const OldHomogeneousVector2D& other) const
    {
        return (*this) + (-other);
    }

    inline OldHomogeneousVector2D operator *(const double p)
    {
        return OldHomogeneousVector2D(x * p, y * p, k);
    }

    inline OldHomogeneousVector2D operator /(const double q)
    {
        return OldHomogeneousVector2D(x / q, y / q, k);
    }

    inline double length()
    {
        return sqrt(sqr(X()) + sqr(Y()));
    }

    inline double dist(const OldHomogeneousVector2D& other)
    {
        return (*this - other).length();
    }
    
    friend std::ostream& operator<<(std::ostream&, const OldHomogeneousVector2D& v);
};

std::ostream& operator<<(std::ostream& os, const OldHomogeneousVector2D& v);

typedef OldHomogeneousVector2D OldHomogeneousPoint2D;



template<typename T, int N>
class GenericVector
{
private:
	T data[N];
	T scale;
public:
	GenericVector<T, N>()
	{
		for(int i=0; i<N; ++i)
			data[i] = 0;
		scale = 1;
	}

	
};


#endif
