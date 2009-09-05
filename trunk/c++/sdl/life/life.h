#ifndef LIFEAPPLICATION_H
#define LIFEAPPLICATION_H

#include "sdlapplication.h"
#include <vector>

using namespace std;

class LifeApplication: public SDLApplication
{
public:
	LifeApplication();
private:
	static const int ScreenWidth = 640, ScreenHeight = 480, ColorDepth = 0, SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	static const int Density = 30; // 0..100
	static const int minimumNeighbours = 2, maximumNeighbours = 3, neighboursForBaby = 3;
	bool map[2][ScreenHeight][ScreenWidth];
	int current;
	void Populate();
	void Turn();
	long long lasttime, lastframes;
protected:
	virtual void ProcessEvent(SDL_Event Event);
	virtual void Main();
	virtual void Render();
};

#endif
