#include "Texture.h"
#include "sdlapplication/SDLException.h"
#include <SDL.h>

RT::Texture::Texture(const std::string &path) : surface(NULL)
{
	surface = SDL_LoadBMP(path.c_str());

	if(surface == NULL)
		throw SDLException();
}

RealColor RT::Texture::GetPixel(const int _x, const int _y) const
{	
	const int x = ((_x % surface->w) + surface->w) % surface->w;
	const int y = ((_y % surface->h) + surface->h) % surface->h;
	
	Uint32 color;

	if(SDL_MUSTLOCK(surface))
		SDLCheck(SDL_LockSurface(surface));

	switch (surface->format->BytesPerPixel){ 
	   case 1:  // Assuming 8-bpp 
	   { 
		 Uint8 *bufp; 
		 bufp = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x;
		 color = *bufp; 
	   } break; 
	   case 2: // Probably 15-bpp or 16-bpp 
	   { 
		 Uint16 *bufp; 
		 bufp = static_cast<Uint16*>(surface->pixels) + y * surface->pitch / 2 + x;
		 color = *bufp;
	   } break; 
	   case 3: // Slow 24-bpp mode, usually not used 
	   { 
		 Uint8 *bufp; 
		 bufp = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * 3;

		 #if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
		 { 
		   color = static_cast<Uint32>(bufp[0]) + (static_cast<Uint32>(bufp[1]) << 8) + (static_cast<Uint32>(bufp[2]) << 16);
		 }
		 #else
		 { 
		   color = static_cast<Uint32>(bufp[2]) + (static_cast<Uint32>(bufp[1]) << 8) + (static_cast<Uint32>(bufp[0]) << 16);
		 } 
		#endif
	   } break; 
	   case 4: // Probably 32-bpp 
	   { 
		 Uint32 *bufp; 
		 bufp = static_cast<Uint32*>(surface->pixels) + y * surface->pitch / 4 + x;

		 color = *bufp;
	   } break;
	   default:
	   {
		 if(SDL_MUSTLOCK(surface))
		   SDL_UnlockSurface(surface);

		 throw NotImplementedException();
	   }

	 }

	if(SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);

	Uint8 r, g, b;
	SDL_GetRGB(color, surface->format, &r, &g, &b);

	return RealColor(r, g, b);
}

RT::Texture::~Texture()
{
	if(surface != NULL)
		SDL_FreeSurface(surface);
}
