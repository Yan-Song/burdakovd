#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
	int x, y;

	Vector(): x(0), y(0) {};

	Vector(int xx, int yy): x(xx), y(yy) {};

	Vector(double xx, double yy): x(static_cast<int>(xx)), y(static_cast<int>(yy)) {};

	Vector(double xx, double yy, double scale):
		x(static_cast<int>(xx * scale)),
		y(static_cast<int>(yy * scale))
		{};

	Vector(Vector base, double xx, double yy, double scale):
		x(static_cast<int>(base.x + xx * scale)),
		y(static_cast<int>(base.y + yy * scale))
		{};

	Vector operator+(const Vector& other) const;

	Vector operator-(const Vector& other) const;

	Vector operator-() const;

	Vector operator*(double k) const;

	Vector operator/(double k) const;

    int Dist2(const Vector& other) const;
};

typedef Vector Point;

#endif
