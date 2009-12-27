#include "Utils.h"

SDL_Rect Intersect(const SDL_Rect& first, const SDL_Rect& second)
{
	SDL_Rect intersection;

	intersection.x = std::max(first.x, second.x);
	intersection.y = std::max(first.y, second.y);

	const Sint16 right = static_cast<Sint16>(std::min<Sint32>(first.x +first.w, second.x + second.w));
	const Sint16 bottom = static_cast<Sint16>(std::min<Sint32>(first.y + first.h, second.y + second.h));

	intersection.w = static_cast<Uint16>(std::max<Sint32>(0, right - intersection.x));
	intersection.h = static_cast<Uint16>(std::max<Sint32>(0, bottom - intersection.y));

	return intersection;
}
