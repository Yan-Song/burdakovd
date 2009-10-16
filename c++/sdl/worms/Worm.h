#ifndef WORM_H
#define WORM_H

#include "IMyWorm.h"
#include "ISomeWorm.h"
#include <vector>
#include "color.h"

class WormsApplication;

// от этого класса будут наследоватьс€ все черви
class Worm : public IMyWorm, public ISomeWorm
{
public:
	Worm()
	{
	}
private:
	WormsApplication* app;
	int ID, classID;
	double energy;
	std::vector<pii> position;
	// локальное врем€ черв€
	double time;
	Color color;

	double GetTime()
	{
		return time;
	}

	// возвращает позиции каждой из клеток черв€, [0] - голова
    virtual const std::vector<pii>& Position() const
	{
		return position;
	}
    
    // его энерги€
    virtual double Energy() const
	{
		return energy;
	}
    
    // »дентификатор, уникальный дл€ каждого экземпл€ра черв€
    virtual unsigned int GetID() const
	{
		return ID;
	}

    // »дентификатор, уникальный дл€ каждого класса черв€
    virtual unsigned int GetClassID() const
	{
		return classID;
	}

	virtual Color GetColor() const
	{
		return color;
	}

	virtual void Initialize(WormsApplication* _app, const int _ID, int const _classID, const double _energy, const std::vector<pii>& _position,
		const double _time, const Color& _color)
	{
		app = _app;
		ID = _ID;
		classID = _classID;
		energy = _energy;
		position = _position;
		time = _time;
		color = _color;
	};

	virtual void FullRender() const;

public:
	virtual ~Worm()
	{
	}
};

#endif
