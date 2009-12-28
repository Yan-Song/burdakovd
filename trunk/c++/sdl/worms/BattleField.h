#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "CellType.h"
#include <stdexcept>
#include <vector>

class BattleField
{
private:
	typedef std::vector<CellType> Row;
	typedef std::vector<Row> Grid;
	Grid map;

public:
	int Height, Width;

	BattleField(const int height, const int width)
			: map(Grid(static_cast<size_t>(height), Row(static_cast<size_t>(width), CellEmpty))),
		      	Height(height),
			Width(width)
	{
	}

	CellType Get(const int x, const int y) const
	{
		if(y >= 0 && x >= 0 && y < Height && x < Width)
			return map[static_cast<size_t>(y)][static_cast<size_t>(x)];
		else
			return CellWall; // за пределами поля типа всюду стены
	}

	void Set(const int x, const int y, const CellType value)
	{
		if(y >= 0 && x >= 0 && y < Height && x < Width)
			map[static_cast<size_t>(y)][static_cast<size_t>(x)] = value;
		else
			throw new std::out_of_range("Set() out of BattleField range");
	}
};

#endif
