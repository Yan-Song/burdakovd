#include <SDL.h>
#include <SDL_image.h>
#include "sdlapplication/PixelAccess.h"
#include "sdlapplication/SDLException.h"
#include "Texture.h"

RT::Texture::Texture(const std::string &path) : surface(NULL)
{
	surface = IMG_Load(path.c_str());

	if(surface == NULL)
		throw SDLException();
}

RealColor RT::Texture::GetPixel(const int _x, const int _y) const
{	
	const int x = ((_x % surface->w) + surface->w) % surface->w;
	const int y = ((_y % surface->h) + surface->h) % surface->h;
	
	const Uint32 color = ::GetPixel(surface, x, y);

	Uint8 r, g, b;
	SDL_GetRGB(color, surface->format, &r, &g, &b);

	return RealColor(r, g, b);
}

RT::Texture::~Texture()
{
	if(surface != NULL)
		SDL_FreeSurface(surface);
}
