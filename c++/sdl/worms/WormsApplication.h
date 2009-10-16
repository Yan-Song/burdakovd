#ifndef WORMSAPPLICATION_H
#define WORMSAPPLICATION_H

#include "sdlapplication.h"
#include "utils.h"
#include "color.h"
#include "Registrator.h"
#include <vector>

class ISomeWorm;

using namespace std;

enum CellType
{
    CellEmpty,
    CellWall,
    CellWorm,
	CellFood
};

class WormsApplication: public SDLApplication
{
public:
	WormsApplication();
	Registrator registrator;
	static const int FieldWidth = 800, FieldHeight = 600;
	static const Color EmptyColor, WallColor, FoodColor;
	void DrawCell(const pii& position, const CellType type) const;
	void DrawWormCell(const pii& position, const ISomeWorm* worm) const;
	void DrawCell(const pii& position, const Color& color) const;
	std::vector<ISomeWorm*> worms;
	virtual ~WormsApplication();

private:
	static const int ColorDepth = 0, SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	static const int ScreenWidth = 800, ScreenHeight = 600;
	long long lasttime;

protected:
	virtual void ProcessEvent(SDL_Event Event);
	virtual void Main();
	virtual void Render();
};

#endif
