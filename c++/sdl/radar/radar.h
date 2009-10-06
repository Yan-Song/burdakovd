#ifndef RADAR_H
#define RADAR_H

#include "sdlapplication.h"

class Radar : public SDLApplication
{
public:
    Radar();

private:
	static const int ScreenWidth = 320, ScreenHeight = 240;
	static const int ColorDepth = 0, SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
    double phi, r, dphi;
    Point c;
    int x;

protected:

    virtual void Main();

	virtual void Render();

	virtual void ProcessEvent(SDL_Event);
};

#endif
