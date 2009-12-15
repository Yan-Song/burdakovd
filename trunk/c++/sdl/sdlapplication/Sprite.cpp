#include <string>
#include <SDL.h>
#include "SDLApplication.h"
#include "Sprite.h"

Sprite::Sprite(const std::string &BMPFile, const Vector2D& center) : image(NULL)
{
	Center = center;

	SDL_Surface* raw = SDL_LoadBMP(BMPFile.c_str());

	if(raw == NULL)
		throw SDLException();

	image = SDL_DisplayFormat(raw);

	SDL_FreeSurface(raw);

	if(image == NULL)
		throw SDLException();	
}

Sprite::Sprite(const SharedFont& font, const std::string& text, const Color& color) : image(NULL)
{
	Center = Vector00;

	image = TTF_RenderText_Blended(font->font, text.c_str(), color);

	if(image == NULL)
		throw SDLException();
}

Sprite::~Sprite()
{
	if(image != NULL)
		SDL_FreeSurface(image);
}

// http://sdl.beuc.net/sdl.wiki/SDL_BlitSurface
void Sprite::Draw(SDLApplication * const app, const Vector2D &base) const
{
	SDL_Rect dst;
	// Only the position is used in the dstrect (the width and height are ignored).
	dst.x = static_cast<Sint16>((base + Center)[0] - image->w / 2);
	dst.y = static_cast<Sint16>(app->Screen->h - 1 - (base + Center)[1] - image->h / 2);
	
	// If srcrect is NULL, the entire surface is copied.
	SDLCheck(SDL_BlitSurface(image, NULL, app->Screen, &dst));
}

void Sprite::Rotate(const double )
{
	// \todo: вращать спрайт пока хз как
}

void Sprite::Scale(const Vector2D& )
{
	// \todo: растягивать спрайт пока тоже не умею
}

int Sprite::GetWidth() const
{
	return image->w;
}

int Sprite::GetHeight() const
{
	return image->h;
}

void Sprite::Blit(Sprite &target, const ScreenPoint& center) const
{
	SDL_Rect offset;

	offset.x = static_cast<Sint16>(center[0] - image->w / 2);
	offset.y = static_cast<Sint16>(target.image->h - 1 - center[1] - image->h / 2 );

	SDLCheck(SDL_BlitSurface(image, NULL, target.image, &offset));
}

void Sprite::SetColorKey(const Color &color)
{
	const Uint32 key = SDL_MapRGB(image->format,
		static_cast<Uint8>(color.R),
		static_cast<Uint8>(color.G),
		static_cast<Uint8>(color.B));

	SDL_SetColorKey(image, SDL_SRCCOLORKEY, key);
}
