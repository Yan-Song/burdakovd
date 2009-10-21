#include "Vector.h"
#include "Matrix.h"
#include <cmath>
#include <iostream>

Vector2D Vector2DByCoords(double x, double y)
{
	Vector2D ans;
	ans[0] = x;
	ans[1] = y;
	return ans;
}

ScreenPoint ScreenPointByCoords(int x, int y)
{
	ScreenPoint ans;
	ans[0] = x;
	ans[1] = y;
	return ans;
}
