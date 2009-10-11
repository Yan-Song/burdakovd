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
	static const int ColorDepth = 32, SDLflags = SDL_DOUBLEBUF || SDL_ANYFORMAT;
	static const int Density = 30; // 0..100
	static const int ScreenWidth = 800, ScreenHeight = 600;
	static const int minimumNeighbours = 2, maximumNeighbours = 3, neighboursForBaby = 3;
	static const Color alive, dead;
	bool map[2][ScreenWidth][ScreenHeight];
	int current;
	void Populate();
	void Turn();
	long long lasttime;
protected:
	virtual void ProcessEvent(SDL_Event Event);
	virtual void Main();
	virtual void Render();
};

#endif
