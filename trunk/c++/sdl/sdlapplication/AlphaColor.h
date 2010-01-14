#ifndef ALPHACOLOR_H
#define ALPHACOLOR_H

#include <SDL.h>
#include "Color.h"

struct AlphaColor
{
	Color color;
	// альфа-канал от 0 до 255
	Uint8 alpha;

	AlphaColor(const Color& color_, const Uint8 alpha_ = 255) : color(color_), alpha(alpha_)
	{

	}
};

#endif
