#ifndef H_SIMPLEPOINT_H
#define H_SIMPLEPOINT_H

struct SimplePoint
{
	int X, Y;
	SimplePoint(const int x, const int y) : X(x), Y(y) {};

	inline bool operator ==(const SimplePoint& other) const
	{
		return X == other.X && Y == other.Y;
	}

	inline bool operator !=(const SimplePoint& other) const
	{
		return X != other.X || Y != other.Y;
	}
};

bool operator >(const SimplePoint& a, const SimplePoint& b);

bool operator <(const SimplePoint& a, const SimplePoint& b);

#endif
