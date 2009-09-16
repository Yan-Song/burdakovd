#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
	int r, g, b;

	Color(int rr, int gg, int bb) : r(rr), g(gg), b(bb) {};

	Color(int color) : r(color>>16 & 255), g(color>>8 & 255), b(color & 255) {};

	Color(double rr, double gg, double bb) :
		r(static_cast<int>(rr*256)),
		g(static_cast<int>(gg*256)),
		b(static_cast<int>(bb*256)) {};

	operator int() const;

    Color operator*(const int k) const;

    Color operator/(const int k) const;

    Color operator+(const Color& other) const;

    Color operator-(const Color& other) const;
};

#endif
