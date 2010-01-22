#include "SimplePoint.h"

bool operator >(const SimplePoint& a, const SimplePoint& b)
{
	return (a.X > b.X) || ((a.X == b.X) && (a.Y > b.Y));
}

bool operator <(const SimplePoint& a, const SimplePoint& b)
{
	return (a.X < b.X) || ((a.X == b.X) && (a.Y < b.Y));
}
