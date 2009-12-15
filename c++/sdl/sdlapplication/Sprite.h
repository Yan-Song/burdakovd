#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL.h>
#include "Color.h"
#include "Font.h"
#include "GraphObject.h"
#include "Shared.h"
#include "Vector.h"

class SDLApplication;

// экземпляры этого класса можно создавать только _после_ инициализации SDL
// !! При прорисовке спрайта поверхность не должна быть заблокирована!
// их нельзя копировать
class Sprite : public GraphObject2D
{
private:
	SDL_Surface* image;

	Sprite(const Sprite& );
	Sprite operator =(const Sprite& );

public:
	Sprite(const std::string& BMPFile, const Vector2D& center = Vector00);

	Sprite(const SharedFont& font, const std::string& text, const Color& color);

	virtual void Draw(SDLApplication* const app, const Vector2D& base) const;

	virtual void Rotate(const double phi);

	virtual void Scale(const Vector2D& coefficients);

	virtual int GetWidth() const;

	virtual int GetHeight() const;

	virtual ~Sprite();
};

typedef Shared::shared_ptr<Sprite> SharedSprite;

#endif
