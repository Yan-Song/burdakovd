#ifndef GOBJECT_H
#define GOBJECT_H

#include <SDL.h>

class GraphObject
{
public:
	virtual void Draw(SDL_Surface*) = 0;
	// ...
};

#endif
