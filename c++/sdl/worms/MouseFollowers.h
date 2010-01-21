#ifndef MOUSEFOLLOWERS_H
#define MOUSEFOLLOERS_H

#include <cmath>
#include "Worm.h"
#include "WormLogic.h"

class MouseFollower : public Worm
{
public:
	enum decision
	{
		deciseX, deciseY, deciseStay
	};

	virtual WormLogic Run()
	{
		const SimplePoint mouse = Mouse(), head = Position().front();
		const int dx = mouse.X - head.X;
		const int dy = mouse.Y - head.Y;

		if(abs(dx) + abs(dy) < 20)
		{
			return static_cast<WormLogic>(Rand(1,4));
		}
		else
		{
			const decision d =
				dx == 0 ? (dy == 0 ? deciseStay : deciseY)
				: (dy == 0 ?
					deciseX :
					(Rand(2) ? deciseX : deciseY));

			return d == deciseStay ? Stay :
				(d == deciseX ?
				(dx > 0 ? GoRight : GoLeft)
				:
				(dy > 0 ? GoUp : GoDown));
		}
	}
};

#endif
