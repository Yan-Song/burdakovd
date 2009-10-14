#ifndef GOBJECT_H
#define GOBJECT_H

#include <SDL.h>
#include "matrix.h"
#include "Vector.h"
#include "sdlapplication.h"

// методы, не зависящие от числа измерений
template<int Dimensions>
class GenericGraphObject
{
public:
	typedef GenericVector<double, Dimensions> Vector;

	// параллельный перенос
	virtual void Shift(const Vector& v) = 0;

	// ... прочие повороты/растяжения...
    
    virtual ~GenericGraphObject() {};
};

// методы, специфичные для 2D объектов
class GraphObject2D : public GenericGraphObject<2>
{
public:
	// отрисовать себя на заданной поверхности
	virtual void Draw(const SDLApplication*) const = 0;

};

#endif
