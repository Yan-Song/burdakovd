#include "PixelAccess.h"
#include "SDLException.h"

Uint32 GetPixel(SDL_Surface* const surface, const int x, const int y, const bool lock)
{
	if(lock && SDL_MUSTLOCK(surface))
		SDLCheck(SDL_LockSurface(surface));

	Uint32 result;

	switch (surface->format->BytesPerPixel){ 
	   case 1:  // Assuming 8-bpp 
	   { 
		 Uint8 *bufp; 
		 bufp = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x;
		 result = *bufp; 
	   } break; 
	   case 2: // Probably 15-bpp or 16-bpp 
	   { 
		 Uint16 *bufp; 
		 bufp = static_cast<Uint16*>(surface->pixels) + y * surface->pitch / 2 + x;
		 result = *bufp;
	   } break; 
	   case 3: // Slow 24-bpp mode, usually not used 
	   { 
		 Uint8 *bufp; 
		 bufp = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * 3;

		 #if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
		 { 
		   result = static_cast<Uint32>(bufp[0]) + (static_cast<Uint32>(bufp[1]) << 8) + (static_cast<Uint32>(bufp[2]) << 16);
		 }
		 #else
		 { 
		   result = static_cast<Uint32>(bufp[2]) + (static_cast<Uint32>(bufp[1]) << 8) + (static_cast<Uint32>(bufp[0]) << 16);
		 } 
		#endif
	   } break; 
	   case 4: // Probably 32-bpp 
	   { 
		 Uint32 *bufp; 
		 bufp = static_cast<Uint32*>(surface->pixels) + y * surface->pitch / 4 + x;

		 result = *bufp;
	   } break;
	   default:
	   {
		 if(lock && SDL_MUSTLOCK(surface))
		   SDL_UnlockSurface(surface);

		 throw NotImplementedException();
	   }

	 }

	if(lock && SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);	

	return result;
}

void PutPixel(SDL_Surface* const surface, const int x, const int y, const Uint32 color, const bool lock)
{
	if((x < 0) || (x >= surface->w) || (y < 0) || (y >= surface->h)) return; // out of bounds

	if(lock && SDL_MUSTLOCK(surface))
		SDLCheck(SDL_LockSurface(surface));

	switch (surface->format->BytesPerPixel){
	   case 1:  // Assuming 8-bpp
	   {
		 Uint8 *bufp;
		 bufp = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x;
		 *bufp = static_cast<Uint8>(color);
	   } break;
	   case 2: // Probably 15-bpp or 16-bpp
	   {
		 Uint16 *bufp;
		 bufp = static_cast<Uint16*>(surface->pixels) + y * surface->pitch/2 + x;
		 *bufp = static_cast<Uint16>(color);
	   } break;
	   case 3: // Slow 24-bpp mode, usually not used
	   {
		 Uint8 *bufp;
		 bufp = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * 3;
		 #if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
		 {
		   bufp[0] = static_cast<Uint8>(color);
		   bufp[1] = static_cast<Uint8>(color >> 8);
		   bufp[2] = static_cast<Uint8>(color >> 16);
		 }
		 #else
		 {
		   bufp[2] = color;
		   bufp[1] = color >> 8;
		   bufp[0] = color >> 16;
		 }
		#endif
	   } break;
	   case 4: // Probably 32-bpp
	   {
		 Uint32 *bufp;
		 bufp = static_cast<Uint32*>(surface->pixels) + y * surface->pitch/4 + x;
		 *bufp = color;
	   } break;
	 }	

	if(lock && SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
}
