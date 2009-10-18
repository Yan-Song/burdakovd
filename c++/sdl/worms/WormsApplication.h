#ifndef WORMSAPPLICATION_H
#define WORMSAPPLICATION_H

#include "sdlapplication.h"
#include "utils.h"
#include "color.h"
#include "Registrator.h"
#include "CellType.h"
#include <vector>
#include "BattleField.h"

class ISomeWorm;

using namespace std;

class WormsApplication: public SDLApplication
{
public:
	WormsApplication();
	Registrator registrator;
	BattleField Map;
	static const int FieldWidth = 800, FieldHeight = 600;
	static const Color EmptyColor, WallColor, FoodColor;
	void DrawCell(const SimplePoint& position, const CellType type) const;
	void DrawWormCell(const SimplePoint& position, const ISomeWorm* worm, const int index) const;
	void DrawCell(const SimplePoint& position, const Color& color) const;
	std::vector<ISomeWorm*> worms;
	std::vector<ISomeWorm*> nextWorms;
	virtual ~WormsApplication();

private:
	static const int ColorDepth = 0, SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	static const int ScreenWidth = 800, ScreenHeight = 600;
	long long lasttime;

protected:
	virtual void ProcessEvent(SDL_Event Event);
	virtual void Main();
	virtual void Render();
	virtual void InitialRender();
};

#endif
