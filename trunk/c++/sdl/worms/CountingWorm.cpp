#include <algorithm>
#include <list>
#include <map>
#include "Config.h"
#include "CountingWorm.h"

CountingWorm::CountingWorm() : Worm(), forbidden(), cache()
{
}

CellType CountingWorm::FastLook(const SimplePoint& position)
{
	if(cache.count(position) == 0)
	{
		cache[position] = Look(position.X, position.Y);
	}

	return cache[position];
}

double CountingWorm::CellValue(const SimplePoint& position)
{
	return FastLook(position) == CellFood ? Config::FoodEnergyPerCell : 0.0;
}

bool CountingWorm::FreeToMove(const SimplePoint& position)
{
	return
		((FastLook(position) == CellFood) || (FastLook(position) == CellEmpty)) &&
		(std::find(forbidden.begin(), forbidden.end(), position) == forbidden.end());
}

double CountingWorm::value(const SimplePoint& position, const int movesLeft)
{
	if(movesLeft == 0)
	{
		return 0.0;
	}
	else
	{
		// варианты
		forbidden.push_back(position);

		const SimplePoint pleft = SimplePoint(position.X - 1, position.Y);
		const SimplePoint pright = SimplePoint(position.X + 1, position.Y);
		const SimplePoint ptop = SimplePoint(position.X, position.Y + 1);
		const SimplePoint pbottom = SimplePoint(position.X, position.Y - 1);

		double ans = -1000000;

		if(FreeToMove(pleft))
		{
			ans = std::max(ans, CellValue(pleft) + 0.5 * value(pleft, movesLeft - 1));
		}

		if(FreeToMove(pright))
		{
			ans = std::max(ans, CellValue(pright) + 0.5 * value(pright, movesLeft - 1));
		}

		if(FreeToMove(ptop))
		{
			ans = std::max(ans, CellValue(ptop) + 0.5 * value(ptop, movesLeft - 1));
		}

		if(FreeToMove(pbottom))
		{
			ans = std::max(ans, CellValue(pbottom) + 0.5 * value(pbottom, movesLeft - 1));
		}

		forbidden.pop_back();

		return ans;
	}
}

WormLogic CountingWorm::solve()
{
	forbidden.clear();
	const SimplePoint head = Position().front();
	forbidden.push_back(head);
	
	const SimplePoint pleft = SimplePoint(head.X - 1, head.Y);
	const SimplePoint pright = SimplePoint(head.X + 1, head.Y);
	const SimplePoint ptop = SimplePoint(head.X, head.Y + 1);
	const SimplePoint pbottom = SimplePoint(head.X, head.Y - 1);

	typedef std::pair<double, WormLogic> dw;
	std::vector<dw> candidates;

	if(FreeToMove(pleft))
	{
		candidates.push_back(dw(CellValue(pleft) + 0.5 * value(pleft, maxMoves - 1), GoLeft));
	}

	if(FreeToMove(pright))
	{
		candidates.push_back(dw(CellValue(pright) + 0.5 * value(pright, maxMoves - 1), GoRight));
	}

	if(FreeToMove(ptop))
	{
		candidates.push_back(dw(CellValue(ptop) + 0.5 * value(ptop, maxMoves - 1), GoUp));
	}

	if(FreeToMove(pbottom))
	{
		candidates.push_back(dw(CellValue(pbottom) + 0.5 * value(pbottom, maxMoves - 1), GoDown));
	}

	forbidden.pop_back();

	if(candidates.empty())
	{
		return Stay;
	}
	else
	{
		std::sort(candidates.begin(), candidates.end(), std::greater<dw>());

		const dw best = candidates[0];
		std::vector<dw> bests;
		for(std::vector<dw>::const_iterator it = candidates.begin(); it != candidates.end(); ++it)
			if(it->first == best.first)
				bests.push_back(*it);

		if(best.first >= 0)
		{
			return bests[Rand(bests.size())].second;
		}
		else
		{
			return Stay;
		}
	}
}

WormLogic CountingWorm::Run()
{
	cache.clear();
	return solve();
}
