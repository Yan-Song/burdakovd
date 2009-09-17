#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
	double x, y, k;

	Vector(): x(0), y(0), k(1) {};

	Vector(double xx, double yy): x(xx), y(yy), k(1) {};

	Vector(double xx, double yy, double scale):
		x(xx * scale),
		y(yy * scale),
        k(1)
		{};

	Vector(Vector base, double xx, double yy, double scale):
		x(base.x + xx * scale),
		y(base.y + yy * scale),
        k(1)
		{};

	Vector operator+(const Vector& other) const;

	Vector operator-(const Vector& other) const;

	Vector operator-() const;

	Vector operator*(double k) const;

	Vector operator/(double k) const;

    double Dist(const Vector& other) const;
};

typedef Vector Point;

#endif
