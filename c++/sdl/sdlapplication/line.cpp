#include "line.h"
#include <SDL.h>
#include "sdlapplication.h"
#include "Vector.h"

// http://ru.wikipedia.org/wiki/Алгоритм_Брезенхэма
// Шикин, Боресков, Компьютерная графика. Полигональные модели. с. 161

// для цвета пиксела в случае градиента такая точность не нужна, так что он вычисляется проще
void Line::Draw(SDL_Surface *surface)
{
	int dx = abs(B.x - A.x);
	int dy = abs(B.y - A.y);
	int sx = B.x >= A.x ? 1 : -1;
	int sy = B.y >= A.y ? 1 : -1;

	if(dy <= dx)
	{
		int d = (dy << 1) - dx;
		int d1 = dy << 1;
		int d2 = (dy - dx) << 1;

		SDLApplication::DrawPixel(surface, A, colorA);

		for(int x = A.x + sx, y = A.y, i = 1; i <= dx; ++i, x += sx)
		{
            if ( d > 0 )
            {
                d += d2;
                y += sy;
            }
            else
            {
                d += d1;
            }
            SDLApplication::DrawPixel(surface, Point(x, y), colorA + (colorB - colorA) * (x - A.x) / (B.x - A.x));
		}
	}
    else
    {
		int d = (dx << 1) - dy;
		int d1 = dx << 1;
		int d2 = (dx - dy) << 1;

		SDLApplication::DrawPixel(surface, A, colorA);

		for(int x = A.x, y = A.y + sy, i = 1; i <= dy; ++i, y += sy)
		{
            if ( d > 0 )
            {
                d += d2;
                x += sx;
            }
            else
            {
                d += d1;
            }
            SDLApplication::DrawPixel(surface, Point(x, y), colorA + (colorB - colorA) * (y - A.y) / (B.y - A.y));
		}
	}
}