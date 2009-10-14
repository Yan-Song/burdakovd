#include "Circle2D.h"

void Circle2D::circlePoints(const SDLApplication* app, const int x, const int y, const Color& color) const
{
	const int xCenter = static_cast<int>(Center[0]), yCenter = static_cast<int>(Center[1]);

	app->DrawPixel(xCenter + x, yCenter + y, color);
	app->DrawPixel(xCenter + y, yCenter + x, color);
	app->DrawPixel(xCenter + y, yCenter - x, color);
	app->DrawPixel(xCenter + x, yCenter - y, color);
	app->DrawPixel(xCenter - x, yCenter - y, color);
	app->DrawPixel(xCenter - y, yCenter - x, color);
	app->DrawPixel(xCenter - y, yCenter + x, color);
	app->DrawPixel(xCenter - x, yCenter + y, color);
}

void Circle2D::Draw(const SDLApplication* app) const
{
	int r = static_cast<int>(R);

	int x = 0;
	int y = r;

	int d = 1 - r;

	int delta1 = 3;
	int delta2 = - 2 * r + 5;

	circlePoints(app, x, y, color);

	while(y > x)
	{
		if(d < 0)
		{
			d += delta1;
			delta1 += 2;
			delta2 += 2;
			++x;
		}
		else
		{
			d += delta2;
			delta1 += 2;
			delta2 += 4;
			++x;
			--y;
		}
		circlePoints(app, x, y, color);
	}
}

void Circle2D::Shift(const Vector2D& v)
{
	Center += v;
}
