#ifndef ALPHACOLOR_H
#define ALPHACOLOR_H

#include <SDL.h>
#include "Color.h"

struct AlphaColor
{
	Color color;
	// �����-����� �� 0 �� 255
	Uint8 alpha;

	AlphaColor(const Color& color_, const Uint8 alpha_ = 255) : color(color_), alpha(alpha_)
	{

	}
};

#endif
