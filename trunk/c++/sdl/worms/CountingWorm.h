#ifndef COUNTINGWORM_H
#define COUNTINGWORM_H

#include <list>
#include <map>
#include "Worm.h"
#include "WormLogic.h"

class CountingWorm : public Worm
{
private:
	static const int maxMoves = 5;
	TPosition forbidden;
	std::map<SimplePoint, CellType> cache;

	CellType FastLook(const SimplePoint& position);

	WormLogic solve();

	bool FreeToMove(const SimplePoint& position);

	double CellValue(const SimplePoint& position);

	double value(const SimplePoint& position, const int movesLeft);

public:
	CountingWorm();

	virtual WormLogic Run();
};

#endif
