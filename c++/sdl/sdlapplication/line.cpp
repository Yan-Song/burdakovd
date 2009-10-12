#include "line.h"
#include <SDL.h>
#include "sdlapplication.h"
#include "Vector.h"

// http://ru.wikipedia.org/wiki/��������_����������
// �����, ��������, ������������ �������. ������������� ������. �. 161

void Line::Draw(const SDLApplication* app) const
{
    int x1 = static_cast<int>(A[0]);
    int y1 = static_cast<int>(A[1]);
    int x2 = static_cast<int>(B[0]);
    int y2 = static_cast<int>(B[1]);

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = x2 >= x1 ? 1 : -1;
	int sy = y2 >= y1 ? 1 : -1;

	if(dy <= dx)
	{
		int d = (dy << 1) - dx;
		int d1 = dy << 1;
		int d2 = (dy - dx) << 1;

		app->DrawPixel(A, color);

		for(int x = x1 + sx, y = y1, i = 1; i <= dx; ++i, x += sx)
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
            app->DrawPixel(x, y, color);
		}
	}
    else
    {
		int d = (dx << 1) - dy;
		int d1 = dx << 1;
		int d2 = (dx - dy) << 1;

		app->DrawPixel(A, color);

		for(int x = x1, y = y1 + sy, i = 1; i <= dy; ++i, y += sy)
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
            app->DrawPixel(x, y, color);
		}
	}
}

/*void Line::Modify(const Matrix &m)
{
    A = m * A;
    B = m * B;
}*/