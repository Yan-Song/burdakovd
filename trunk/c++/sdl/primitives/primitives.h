#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "sdlapplication.h"
#include <vector>
#include "line.h"

using namespace std;

typedef double pFunction(double);

class PrimitivesApplication : public SDLApplication
{
private:
	static const int ScreenWidth = 800, ScreenHeight = 600;
	static const int ColorDepth = 0, SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
    void Koh(const Line& l);
    void Koh(const int depth, const Line& l, const vector<Matrix>& m, const Matrix& acc);
    void Dragon(const Line& l);
    void Dragon(const int depth, const Line& l, const vector<Matrix>& m, const Matrix& acc);

protected:
	virtual void Main();

	virtual void Render();

	virtual void ProcessEvent(SDL_Event);

public:
	PrimitivesApplication();

};

#endif
