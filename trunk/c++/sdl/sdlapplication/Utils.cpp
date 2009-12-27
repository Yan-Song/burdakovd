#include "Utils.h"

SDL_Rect Intersect(const SDL_Rect& first, const SDL_Rect& second)
{
	SDL_Rect intersection;

	intersection.x = std::max(first.x, second.x);
	intersection.y = std::max(first.y, second.y);

	const Sint16 right = std::min<Sint16>(first.x + static_cast<Sint16>(first.w), second.x + static_cast<Sint16>(second.w));
	const Sint16 bottom = std::min<Sint16>(first.y + static_cast<Sint16>(first.h), second.y + static_cast<Sint16>(second.h));

	intersection.w = static_cast<Uint16>(std::max<Sint16>(0, right - intersection.x));
	intersection.h = static_cast<Uint16>(std::max<Sint16>(0, bottom - intersection.y));

	return intersection;
}
