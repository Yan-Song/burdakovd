#include "Sprite.h"
#include <string>
#include <SDL.h>

#pragma warning (disable : 4100)

Sprite::Sprite(const std::string &BMPFile, const Vector2D& center) : image(NULL)
{
	Center = center;

	SDL_Surface* raw = SDL_LoadBMP(BMPFile.c_str());

	if(raw == NULL)
		throw new SDLException();

	image = SDL_DisplayFormat(raw);

	SDL_FreeSurface(raw);

	if(image == NULL)
		throw new SDLException();	
}

Sprite::~Sprite()
{
	if(image != NULL)
		SDL_FreeSurface(image);
}

// http://sdl.beuc.net/sdl.wiki/SDL_BlitSurface
void Sprite::Draw(const SDLApplication *app, const Vector2D &base) const
{
	SDL_Rect dst;
	// Only the position is used in the dstrect (the width and height are ignored).
	dst.x = static_cast<Sint16>((base + Center)[0] - image->w / 2);
	dst.y = static_cast<Sint16>((base + Center)[1] - image->h / 2);
	
	// If srcrect is NULL, the entire surface is copied.
	SDLCheck(SDL_BlitSurface(image, NULL, app->Screen, &dst));
}

void Sprite::Rotate(const double phi)
{
	// \todo: вращать спрайт пока хз как
}

void Sprite::Scale(const Vector2D& coefficients)
{
	// \todo: раст€гивать спрайт пока тоже не умею
}
