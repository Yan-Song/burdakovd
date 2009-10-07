#ifndef COLOR_H
#define COLOR_H

#include <SDL.h>

// I - int/double // ��� ������� � ������� ���������� ���������?
template<typename I>
class GenericColor
{
public:
	I R, G, B; // ���������� �����, 0..255

	// ����������� �� ��� ��������� RGB, 0..255
	GenericColor(I rr, I gg, I bb) :
		R(rr),
		G(gg),
		B(bb)
		{};

	// ����������� �� ������������� ����� ������: 0xRRGGBB
	GenericColor(int GenericColor) :
		R(GenericColor>>16 & 255),
		G(GenericColor>>8 & 255),
		B(GenericColor & 255)
		{};

	// ��������� ���� ��������� ����� �� ������
    inline GenericColor<I> operator *(const I k) const
	{
	   return GenericColor<I>(R * k, G * k, B * k);
	}

	inline GenericColor<I> operator /(const I k) const
	{
		return GenericColor<I>(R / k, G / k, B / k);
	}

	inline GenericColor<I> operator +(const GenericColor<I>& other) const
	{
		return GenericColor<I>(R + other.R, G + other.G, B + other.B);
	}

	inline GenericColor<I> operator -(const GenericColor<I>& other) const
	{
		return GenericColor<I>(R - other.R, G - other.G, B - other.B);
	}

	template<typename J>
	inline operator GenericColor<J>()
	{
		return GenericColor<J>(static_cast<J>(R), static_cast<J>(G), static_cast<J>(B));
	}
};

typedef GenericColor<int> Color;
typedef GenericColor<double> DoubleColor;

#endif
