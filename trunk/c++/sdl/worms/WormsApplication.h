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
typedef std::vector<ISomeWorm*> SomeWorms;

class WormsApplication: public SDLApplication
{
public:
	WormsApplication();
	BattleField Map;
	static const int FieldWidth = 800, FieldHeight = 600;
	static const Color EmptyColor, WallColor, FoodColor;
	void DrawCell(const SimplePoint& position, const CellType type) const;
	void DrawWormCell(const SimplePoint& position, const ISomeWorm* worm, const int index) const;
	void DrawCell(const SimplePoint& position, const Color& color) const;
	// создать нового червя заданного класса, добавить его в список, и вернуть указатель на него
	// вызывающая сторона не должна делать delete для этого указателя
	// UpdateMap и Draw для созданного червя автоматически не вызывается
	ISomeWorm* AddWorm(const int ClassID, const double energy, const TPosition& position, const Color& color);
	virtual ~WormsApplication();

private:
	static const int ColorDepth = 0, SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	static const int ScreenWidth = 800, ScreenHeight = 600;
	long long lasttime;
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
