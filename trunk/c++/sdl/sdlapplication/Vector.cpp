#include "Vector.h"
#include "Matrix.h"
#include <cmath>
#include <iostream>

Vector2D Vector2DByCoords(const double x, const double y)
{
	Vector2D ans;
	ans[0] = x;
	ans[1] = y;
	return ans;
}

Vector3D Vector3DByCoords(const double x, const double y, const double z)
{
	Vector3D ans;
	ans[0] = x;
	ans[1] = y;
	ans[2] = z;
	return ans;
}

ScreenPoint ScreenPointByCoords(const int x, const int y)
{
	ScreenPoint ans;
	ans[0] = x;
	ans[1] = y;
	return ans;
}
