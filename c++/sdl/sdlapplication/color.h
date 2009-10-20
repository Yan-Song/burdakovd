#ifndef COLOR_H
#define COLOR_H

#include <SDL.h>

// I - int/double // как указать в шаблоне допустимые параметры?
template<typename I>
class GenericColor
{
public:
	I R, G, B; // компоненты цвета, 0..255

	GenericColor() : R(0), G(0), B(0) {};

	// конструктор от трёх компонент RGB, 0..255
	GenericColor(I rr, I gg, I bb) :
		R(rr),
		G(gg),
		B(bb)
		{};

	// конструктор от представления одним числом: 0xRRGGBB
	GenericColor(int color) :
		R(color>>16 & 255),
		G(color>>8 & 255),
		B(color & 255)
		{};

	inline GenericColor<I> operator +(const GenericColor<I>& other) const
	{
		return GenericColor<I>(R + other.R, G + other.G, B + other.B);
	}

	inline GenericColor<I> operator -(const GenericColor<I>& other) const
	{
		return GenericColor<I>(R - other.R, G - other.G, B - other.B);
	}

	// умножение всех компонент цвета на скаляр
    inline GenericColor<I> operator *(const I k) const
	{
	   return GenericColor<I>(R * k, G * k, B * k);
	}

	inline GenericColor<I> operator /(const I k) const
	{
		return GenericColor<I>(R / k, G / k, B / k);
	}

	template<typename J>
	inline operator GenericColor<J>()
	{
		return GenericColor<J>(static_cast<J>(R), static_cast<J>(G), static_cast<J>(B));
	}
};


// градиент работает и для целочисленного случая (Color)
template<typename I>
inline GenericColor<I> Gradient(const GenericColor<I>& ColorA, const GenericColor<I>& ColorB, const I WeightA, const I WeightB)
{
	return (ColorA * WeightA + ColorB * WeightB) / (WeightA + WeightB);
}


/*
Лучше использовать Color, так как он использует только целочисленную арифметику,
но если вдруг понадобится DoubleColor (использует double) то он тоже есть и cast работает в обе стороны
*/
typedef GenericColor<int> Color;
typedef GenericColor<double> DoubleColor;


// некоторые базовые цвета, хотя кто их будет использовать?)
class Palette
{
public:
	static const Color
		Black, White, Red, Green, Blue, Yellow, Gray;
};

#endif
