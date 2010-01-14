#ifndef PIXELACCESS_H
#define PIXELACCESS_H

#include <SDL.h>

Uint32 GetPixel(SDL_Surface* const surface, const int x, const int y, const bool lock = true);

void PutPixel(SDL_Surface* const surface, const int x, const int y, const Uint32 color, const bool lock = true);

#endif
