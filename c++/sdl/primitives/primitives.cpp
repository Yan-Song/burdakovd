#include "primitives.h"
#include "sdlapplication.h"
#include "Vector.h"
#include "color.h"
#include <cmath>
#include <ctime>
#include <cstring>
#include "line.h"
#include "matrix.h"
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

const Color yellow = Color(255, 255, 0);
const Color black = Color(0, 0, 0);
const Color white = Color(255, 255, 255);
const Color background = black;
const Color sand = Color(200, 200, 0);
const Color cyan = Color(0, 255, 255);
const double density = 1, activity = 0.001;

PrimitivesApplication::PrimitivesApplication()
{
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Demo", NULL);
}

void PrimitivesApplication::Main()
{
	
}

double norm(double x)
{
	return 0.5 * (1.0 + x);
}

template<class T>
int sgn(T x)
{
	return x<0 ? -1 :
		(x>0 ? 1 : 0);
}

void PrimitivesApplication::Render()
{
    double lsf = norm(sin(0.001 * frames));
	double lcf = norm(cos(0.001 * frames));

	double sf = sin(0.01 * frames * lsf);
	double cf = cos(0.01 * frames * lcf);


	//LockSurface(Screen);

	if(frames == 0)
    {
        
        Point p1(20, 100);
        Point p2(320, 100);

        Koh(Line(p1, p2, cyan));

        Dragon(Line(Point(220, 360), Point(520, 360), yellow));
    }

    /*
    // chaos
	for(int x=400; x<780; ++x)
		for(int y=20; y<200; ++y)
		{
			double sx = sin(sf*x*0.1-cf*y*0.1);
			double sy = sin(cf*x*0.1-sf*y*0.1);
			DrawPixel(Screen, Point(x, y), Color(norm(sx), norm(sy), norm(-1)));
		}
    */

	//UnlockSurface(Screen);
	//SDL_Flip(Screen);
}

void PrimitivesApplication::ProcessEvent(SDL_Event Event)
{
	if(Event.type == SDL_KEYDOWN)
	{
		SDLKey sym = Event.key.keysym.sym;

		if(sym == SDLK_ESCAPE || sym == SDLK_q)
			Stop();
	}
}

void PrimitivesApplication::Koh(const int depth, const Line& l, const vector<Matrix>& m, const Matrix& acc)
{
    if(depth == 0) // финишная прорисовка
    {
        Line tmp = l;
        tmp.Modify(acc);
        LockSurface(Screen);
        tmp.Draw(Screen);
        UnlockSurface(Screen);
        SDL_Flip(Screen);
    }
    else
    {
        for(Uint16 i=0; i<m.size(); ++i)
        {
            Koh(depth - 1, l, m, acc * m[i]);
        }
    }
}

void PrimitivesApplication::Koh(const Line& l)
{
    vector<Matrix> v;

    v.push_back(Matrix::Scale(l.A, 1.0/3, 1.0/3));

    v.push_back(Matrix::Shift((l.B - l.A) / 3) * Matrix::Rotate(l.A, Pi / 3) * Matrix::Scale(l.A, 1.0/3, 1.0/3));

    v.push_back(Matrix::Shift((l.A - l.B) / 3) * Matrix::Rotate(l.B, -Pi / 3) * Matrix::Scale(l.B, 1.0/3, 1.0/3));

    v.push_back(Matrix::Scale(l.B, 1.0/3, 1.0/3));

    Koh(4, l, v, Matrix(1));
}


void PrimitivesApplication::Dragon(const int depth, const Line& l, const vector<Matrix>& m, const Matrix& acc)
{
    if(depth == 0) // финишная прорисовка
    {
        Line tmp = l;
        tmp.Modify(acc);
        LockSurface(Screen);
        tmp.Draw(Screen);
        UnlockSurface(Screen);
        SDL_Flip(Screen);
    }
    else
    {
        for(Uint16 i=0; i<m.size(); ++i)
        {
            Dragon(depth - 1, l, m, acc * m[i]);
        }
    }
}

void PrimitivesApplication::Dragon(const Line& l)
{
    vector<Matrix> v;

    v.push_back(Matrix::ReflectY(l.A.Y()) * Matrix::Rotate(l.A, -Pi / 4) * Matrix::Scale(l.A, sqrt(0.5), sqrt(0.5)));

    v.push_back(Matrix::Rotate(l.B, -Pi / 4) * Matrix::Scale(l.B, sqrt(0.5), sqrt(0.5)));

    Dragon(13, l, v, Matrix(1));
}