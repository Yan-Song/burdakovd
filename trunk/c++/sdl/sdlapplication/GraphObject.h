#ifndef GOBJECT_H
#define GOBJECT_H

#include <SDL.h>
#include "Matrix.h"
#include "Vector.h"
#include "SDLApplication.h"
#include "Affine.h"

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

	// растяжение относительно заданной точки
	virtual void ScaleRelative(const GenericVector<double, Dimensions>& coefficients, const GenericVector<double, Dimensions>& center)
	{
		// рассчитываем куда перейдет центр
		for(unsigned int i = 0; i < coefficients.Dimensions; ++i)
			Center[i] = center[i] + (Center[i] - center[i]) * coefficients[i];

		// затем делаем растяжение относительно центра
		Scale(coefficients);
	}

	// растяжение относительно центра объекта
	virtual void Scale(const GenericVector<double, Dimensions>& coefficients) = 0;
   
    virtual ~GenericGraphObject() {};
};

// методы, специфичные для 2D объектов
class GraphObject2D : public GenericGraphObject<2>
{
public:
	// отрисовать себя, относительно заданной точки
	virtual void Draw(const SDLApplication*, const Vector& base) const = 0;

	// вращение относительно центра объекта
	virtual void Rotate(const double phi) = 0;

	// вращение относительно заданной точки
	virtual void RotateAround(const double phi, const Vector2D& center)
	{
		// повернуть центр
		Center = Affine::Rotate2D(phi, center) * Center;

		// повернуть всё остальное относительно центра
		Rotate(phi);
	}
};

#endif
