#ifndef FONT_H
#define FONT_H

#include <string>
#include <SDL_ttf.h>
#include "SDLException.h"
#include "Shared.h"

class Font
{
private:
	Font(const Font& );
	Font& operator =(const Font& );

public:
	TTF_Font* font;

public:
	Font(const std::string& file, const int size);

	virtual ~Font();
};

typedef Shared::shared_ptr<Font> SharedFont;

SharedFont GetFont(const std::string& file, const int size);

void ClearFontCache();

#endif
