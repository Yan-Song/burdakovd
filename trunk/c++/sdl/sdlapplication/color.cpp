#include "color.h"

Color::operator int() const
{
	return ((r&255)<<16) + ((g&255)<<8) + (b&255);
}

Color Color::operator*(const int k) const
{
    return Color(k*r, k*g, k*b);
}

Color Color::operator/(const int k) const
{
    return Color(r/k, g/k, b/k);
}

Color Color::operator +(const Color &other) const
{
    return Color(r+other.r, g+other.g, b+other.b);
}

Color Color::operator -(const Color &other) const
{
   return Color(r-other.r, g-other.g, b-other.b);
}
