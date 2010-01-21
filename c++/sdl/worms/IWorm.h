#ifndef IWORM_H
#define IWORM_H

#include <list>
#include <Utils.h>

struct SimplePoint
{
	int X, Y;
	SimplePoint(const int x, const int y) : X(x), Y(y) {};

	inline bool operator ==(const SimplePoint& other) const
	{
		return X == other.X && Y == other.Y;
	}

	inline bool operator !=(const SimplePoint& other) const
	{
		return X != other.X || Y != other.Y;
	}
};

typedef std::list<SimplePoint> TPosition;

// методы, общие для логики червя и для основной программы
class IWorm
{
public:
    // возвращает позиции каждой из клеток червя, [0] - голова
    virtual const TPosition& Position() const = 0;

    // его энергия
    virtual double Energy() const = 0;

    // Идентификатор, уникальный для каждого экземпляра червя
    virtual unsigned int GetID() const = 0;

    // Идентификатор, уникальный для каждого класса червя
    virtual unsigned int GetClassID() const = 0;

	// число из полуинтервала [0, x)
	virtual int Rand(const int x) const = 0;

	// из отрезка [x, y]
	virtual int Rand(const int x, const int y) const = 0;

	// узнать текущее время
	virtual double GetGlobalTime() const = 0;

	virtual SimplePoint Mouse() const = 0;

	virtual ~IWorm()
	{
	}
};

#endif
