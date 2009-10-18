#ifndef WORM_H
#define WORM_H

#include "IMyWorm.h"
#include "ISomeWorm.h"
#include "WormLogic.h"
#include "color.h"
#include <vector>

class WormsApplication;

// от этого класса будут наследоватьс€ все черви
class Worm : public IMyWorm, public ISomeWorm
{
public:
	Worm() : dead(false)
	{
	}
private:
	WormsApplication* app;
	int ID, classID;
	double energy;
	TPosition position;
	// локальное врем€ черв€
	double time;
	Color color;
	bool dead;

	double GetTime() const
	{
		return time;
	}

	// возвращает позиции каждой из клеток черв€, [0] - голова
    virtual const TPosition& Position() const
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

	virtual void Initialize(WormsApplication* _app, const int _ID, int const _classID, const double _energy, const TPosition& _position,
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

	virtual void Draw() const;

	virtual void UpdateMap() const;

	virtual void EraseOnScreen() const;

	virtual void EraseOnMap() const;

	virtual void Tick();

	virtual void ConsumeTime(const double dt);

	virtual void Go(const WormLogic direction);

	// проверить соотношение своей длины и энергии и удлинитьс€/укоротитьс€
	virtual void CheckLength();

	// увеличить свою длину на 1 клетку
	virtual void Grow();

	// уменьшить свою длину на 1 клетку
	virtual void AntiGrow();

	// умереть
	virtual void Die();

	virtual bool Dead();

public:
	virtual ~Worm()
	{
	}
};

#endif
