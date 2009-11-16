#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "sdlapplication/Color.h"

namespace RT
{
	// экземпляры этого класса можно создавать только после инициализации SDL
	// а также их нельзя копировать
	class Texture
	{
	private:
		SDL_Surface* surface;

		Texture(const Texture&) {}
		const Texture& operator =(const Texture&) {}

	public:
		Texture(const std::string& path);

		RealColor GetPixel(const int x, const int y) const;

		int GetWidth() const
		{
			return surface->w;
		}

		int GetHeight() const
		{
			return surface->h;
		}

		~Texture();
	};
}

#endif
