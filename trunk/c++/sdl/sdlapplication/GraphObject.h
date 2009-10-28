#ifndef GOBJECT_H
#define GOBJECT_H

#include <SDL.h>
#include "Matrix.h"
#include "Vector.h"
#include "SDLApplication.h"

// методы, не зависящие от числа измерений
template<int Dimensions>
class GenericGraphObject
{
public:
	typedef GenericVector<double, Dimensions> Vector;

	// центр этого объекта относительно центра родительского
	Vector Center;

	// параллельный перенос
	virtual void Move(const Vector& v)
	{
		Center += v;
	}

	// ... прочие повороты/растяжения...
    
    virtual ~GenericGraphObject() {};
};

// методы, специфичные для 2D объектов
class GraphObject2D : public GenericGraphObject<2>
{
public:
	// отрисовать себя, относительно заданной точки
	virtual void Draw(const SDLApplication*, const Vector& base) const = 0;

};

#endif
