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
	inline void Move(const Vector& v)
	{
		Center += v;
	}

	// растяжение относительно заданной точки
	inline void ScaleRelative(const GenericVector<double, Dimensions>& coefficients, const GenericVector<double, Dimensions>& center)
	{
		// рассчитываем куда перейдет центр
		Center = center + (Center - center) * coefficients;

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
	virtual void Draw(const SDLApplication* app, const Vector& base) const = 0;

	// вращение относительно центра объекта
	virtual void Rotate(const double phi) = 0;

	// вращение относительно заданной точки
	inline void RotateAround(const double phi, const Vector2D& center)
	{
		// повернуть центр
		Center = Affine::Rotate2D(phi, center) * Center;

		// повернуть всё остальное относительно центра
		Rotate(phi);
	}
};

// методы, специфичные для 3D объектов
class GraphObject3D : public GenericGraphObject<3>
{
public:
	// отрисовать себя, относительно заданной точки
	virtual void Draw(const SDLApplication* app, const Vector3D& base) const = 0;

	// повращать вокруг заданной оси, так чтоб Center остался неподвижным
	virtual void Rotate(const int axe, const double phi) = 0;

	inline void RotateRelative(const int axe, const double phi, const Vector3D& center)
	{
		// повращать центр
		Center = Affine::Rotate3D(axe, phi, center) * Center;
		// а затем всё остальное относительно него
		Rotate(axe, phi);
	}

	// Вообще говоря у параметра center здесь значимы только координаты y и z
	inline void RotateX(const double phi, const Vector3D& center = Vector000)
	{
		RotateRelative(0, phi, center);
	}

	inline void RotateY(const double phi, const Vector3D& center = Vector000)
	{
		RotateRelative(1, phi, center);
	}

	inline void RotateZ(const double phi, const Vector3D& center = Vector000)
	{
		RotateRelative(2, phi, center);
	}
};

#endif
