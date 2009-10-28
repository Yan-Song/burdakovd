#ifndef SPRITE_H
#define SPRITE_H

#include "GraphObject.h"
#include "Vector.h"
#include "SDLApplication.h"
#include <SDL.h>
#include <string>

class SDLApplication;

// экземпляры этого класса можно создавать только _после_ инициализации SDL
// !! При прорисовке спрайта поверхность не должна быть заблокирована!
class Sprite : public GraphObject2D
{
private:
	SDL_Surface* image;

public:
	Sprite(const std::string& BMPFile, const Vector2D& center = Vector00);

	virtual void Draw(const SDLApplication* app, const Vector2D& base) const;

	virtual ~Sprite();
};


#endif