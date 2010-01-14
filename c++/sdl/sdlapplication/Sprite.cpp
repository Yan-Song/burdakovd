#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "PixelAccess.h"
#include "SDLApplication.h"
#include "Sprite.h"

Sprite::Sprite(const std::string &file, const Vector2D& center) : image(NULL)
{
	Center = center;

	SDL_Surface* raw = IMG_Load(file.c_str());

	if(raw == NULL)
		throw SDLException();

	image = SDL_DisplayFormatAlpha(raw);

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
void Sprite::Draw(SDLApplication* const app, const Vector2D &base) const
{
	BlitOnScreen(app, base + Center - 0.5 * Vector2DByCoords(GetWidth(), GetHeight()));
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

void Sprite::BlitOnSprite(Sprite &target, const ScreenPoint& center) const
{
	SDL_Rect offset;

	offset.x = static_cast<Sint16>(center[0] - image->w / 2);
	offset.y = static_cast<Sint16>(target.image->h - 1 - center[1] - image->h / 2 );

	SDLCheck(SDL_BlitSurface(image, NULL, target.image, &offset));
}

void Sprite::BlitOnSprite(Sprite &target) const
{
	SDL_Rect offset;

	offset.x = 0;
	offset.y = 0;

	SDLCheck(SDL_BlitSurface(image, NULL, target.image, &offset));
}

void Sprite::BlitOnScreen(SDLApplication* const app, const ScreenPoint& LeftBottom) const
{
	SDL_Rect dst;
	dst.x = static_cast<Sint16>(LeftBottom[0]);
	dst.y = static_cast<Sint16>(app->Screen->h - 1 - LeftBottom[1] - image->h);

	SDLCheck(SDL_BlitSurface(image, NULL, app->Screen, &dst));
}

void Sprite::SetColorKey(const Color &color)
{
	const Uint32 key = SDL_MapRGB(image->format,
		static_cast<Uint8>(color.R),
		static_cast<Uint8>(color.G),
		static_cast<Uint8>(color.B));

	SDL_SetColorKey(image, SDL_SRCCOLORKEY, key);
}

AlphaColor Sprite::GetPixel(const int x, const int y) const
{
	const Uint32 raw = ::GetPixel(image, x, y);

	Uint8 r, g, b, a;

	SDL_GetRGBA(raw, image->format, &r, &g, &b, &a);

	return AlphaColor(Color(r, g, b), a);
}

void Sprite::SetPixel(const int x, const int y, const AlphaColor &acolor)
{
	const Uint32 raw = SDL_MapRGBA(
		image->format,
		static_cast<Uint8>(acolor.color.R),
		static_cast<Uint8>(acolor.color.G),
		static_cast<Uint8>(acolor.color.B),
		acolor.alpha);

	::PutPixel(image, x, y, raw);
}
