#ifndef IWORM_H
#define IWORM_H

#include <list>
#include <utils.h>

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

// методы, общие дл€ логики черв€ и дл€ основной программы
class IWorm
{
public:
    // возвращает позиции каждой из клеток черв€, [0] - голова
    virtual const TPosition& Position() const = 0;
    
    // его энерги€
    virtual double Energy() const = 0;
    
    // »дентификатор, уникальный дл€ каждого экземпл€ра черв€
    virtual unsigned int GetID() const = 0;

    // »дентификатор, уникальный дл€ каждого класса черв€
    virtual unsigned int GetClassID() const = 0;

	// число из полуинтервала [0, x)
	virtual int Rand(const int x) const = 0;

	// из отрезка [x, y]
	virtual int Rand(const int x, const int y) const = 0;

	virtual ~IWorm()
	{
	}
};

#endif
