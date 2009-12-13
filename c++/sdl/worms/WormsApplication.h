#ifndef WORMSAPPLICATION_H
#define WORMSAPPLICATION_H

#include <vector>
#include <Color.h>
#include <SDLApplication.h>
#include <Timer.h>
#include <Utils.h>
#include "BattleField.h"
#include "CellType.h"
#include "ISomeWorm.h"
#include "Registrator.h"


typedef std::vector<SharedSomeWorm> SomeWorms;

class WormsApplication: public SDLApplication
{
public:
	static const int FieldWidth, FieldHeight;
	static const Color EmptyColor, WallColor, FoodColor;
public:
	BattleField Map;

public:
	WormsApplication();
	void DrawCell(const SimplePoint& position, const CellType type);
	void DrawWormCell(const SimplePoint& position, const ISomeWorm* worm, const int index);
	void DrawCell(const SimplePoint& position, const Color& color);
	// создать нового червя заданного класса, добавить его в список, и вернуть указатель на него
	// вызывающая сторона не должна делать delete для этого указателя
	// UpdateMap и Draw для созданного червя автоматически не вызывается
	SharedSomeWorm AddWorm(const size_t ClassID, const double energy, const TPosition& position, const Color& color);
	// создать некоторое количество еды для червей
	void MakeFood();
	void MakeFood(const int xx, const int yy, const int r);
	void DrawMap();
	virtual ~WormsApplication();

private:
	static const int ColorDepth = 0, SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	static const int ScreenWidth = 800, ScreenHeight = 600;
	Timer printStatsTimer;
	size_t nextWormID;
	Registrator registrator;
	SomeWorms worms;

protected:
	virtual void ProcessEvent(const SDL_Event& Event);
	virtual void Main();
	virtual void Render();
	virtual void InitialRender();
};

#endif
