#include "Vector.h"
#include <cmath>

#define sqr(x) ((x)*(x))

Vector Vector::operator +(const Vector& other) const
{
	return Vector(x + other.x, y + other.y);
}

Vector Vector::operator -(const Vector& other) const
{
	return Vector(x - other.x, y - other.y);
}

Vector Vector::operator -() const
{
	return Vector(-x, -y);
}

Vector Vector::operator *(double k) const
{
	return Vector(x * k, y * k);
}

Vector Vector::operator /(double k) const
{
	return Vector(x / k, y / k);
}

double Vector::Dist(const Vector& other) const
{
    return sqrt(sqr(x - other.x) + sqr(y - other.y));
}
