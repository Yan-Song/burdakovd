#ifndef WORMSAPPLICATION_H
#define WORMSAPPLICATION_H

#include <vector>
#include <Color.h>
#include <SDLApplication.h>
#include <Timer.h>
#include <Utils.h>
#include "BattleField.h"
#include "CellType.h"
#include "Registrator.h"

class ISomeWorm;
typedef std::vector<ISomeWorm*> SomeWorms;

class WormsApplication: public SDLApplication
{
public:
	WormsApplication();
	BattleField Map;
	static const int FieldWidth, FieldHeight;
	void DrawCell(const SimplePoint& position, const CellType type);
	void DrawWormCell(const SimplePoint& position, const ISomeWorm* worm, const int index);
	void DrawCell(const SimplePoint& position, const Color& color);
	static const Color EmptyColor, WallColor, FoodColor;
	// создать нового червя заданного класса, добавить его в список, и вернуть указатель на него
	// вызывающая сторона не должна делать delete для этого указателя
	// UpdateMap и Draw для созданного червя автоматически не вызывается
	ISomeWorm* AddWorm(const int ClassID, const double energy, const TPosition& position, const Color& color);
	// создать некоторое количество еды для червей
	void MakeFood();
	void MakeFood(const int xx, const int yy, const int r);
	void DrawMap();
	virtual ~WormsApplication();

private:
	static const int ColorDepth = 0, SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	static const int ScreenWidth = 800, ScreenHeight = 600;
	Timer printStatsTimer;
	unsigned int nextWormID;
	Registrator registrator;
	SomeWorms worms;

protected:
	virtual void ProcessEvent(SDL_Event Event);
	virtual void Main();
	virtual void Render();
	virtual void InitialRender();
};

#endif
