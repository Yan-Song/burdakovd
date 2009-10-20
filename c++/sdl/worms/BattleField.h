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

	BattleField(int height, int width) : Height(height), Width(width)
	{
		map = Grid(Height, Row(Width, CellEmpty));
	}
	
	CellType Get(const int x, const int y) const
	{
		if(y >= 0 && x >=0 && y < Height && x < Width)
			return map[y][x];
		else
			return CellWall; // за пределами поля типа стены
	}

	void Set(const int x, const int y, const CellType value)
	{
		if(y >= 0 && x >=0 && y < Height && x < Width)
			map[y][x] = value;
		else
			throw new std::out_of_range("Set() out of BattleField range");
	}
};

#endif