#include "Vector.h"

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
	return Vector(static_cast<int>(x * k), static_cast<int>(y * k));
}

Vector Vector::operator /(double k) const
{
	return (*this) * (1 / k);
}

int Vector::Dist2(const Vector& other) const
{
    return sqr(x - other.x) + sqr(y - other.y);
}