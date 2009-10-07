#ifndef WORMSAPPLICATION_H
#define WORMSAPPLICATION_H

#include "sdlapplication.h"
#include <vector>

using namespace std;

enum CellType
{
    Empty,
    Wall,
    Worm,
};

class WormsApplication: public SDLApplication
{
public:
	WormsApplication();
private:
	static const int ColorDepth = 0, SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	static const int ScreenWidth = 800, ScreenHeight = 600;
    void FullRender() const;
	long long lasttime, lastframes;
protected:
	virtual void ProcessEvent(SDL_Event Event);
	virtual void Main();
	virtual void Render();
};

#endif
