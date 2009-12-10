#ifndef WORM_H
#define WORM_H

#include "IMyWorm.h"
#include "ISomeWorm.h"
#include "WormLogic.h"
#include "Color.h"
#include <vector>
#include "SDL.h"

class WormsApplication;

// от этого класса будут наследоваться все черви
class Worm : public IMyWorm, public ISomeWorm
{
public:
	Worm() : app(NULL), position(), ID(0), classID(0), energy(0.0), time(0.0),
	     lastUpdateEnergyTime(0.0), color(Palette::White), dead(false)
	{
	}

	virtual bool isPressed(const SDLKey key) const;

	// число из полуинтервала [0, x)
	virtual int Rand(const int x) const;

	// из отрезка [x, y]
	virtual int Rand(const int x, const int y) const;

	// локальное время червя
	virtual double GetLocalTime() const
	{
		return time;
	}

	virtual double GetGlobalTime() const;

	virtual CellType Look(const int x, const int y);

	// возвращает позиции каждой из клеток червя, [0] - голова
    virtual const TPosition& Position() const
	{
		return position;
	}

    // его энергия
    virtual double Energy() const
	{
		return energy;
	}

    // Идентификатор, уникальный для каждого экземпляра червя
    virtual size_t GetID() const
	{
		return ID;
	}

    // Идентификатор, уникальный для каждого класса червя
    virtual size_t GetClassID() const
	{
		return classID;
	}

	virtual Color GetColor() const
	{
		return color;
	}

private:
	Worm(const Worm& );
	Worm& operator =(const Worm& );

	WormsApplication* app;
	TPosition position;
	size_t ID, classID;
	double energy;
	// локальное время червя
	double time;
	// время последнего обновления энергии
	double lastUpdateEnergyTime;
	Color color;
	bool dead;

	virtual void Initialize(WormsApplication* _app, const size_t _ID, const size_t _classID,
				const double _energy, const TPosition& _position,
				const double _time, const Color& _color)
	{
		app = _app;
		ID = _ID;
		classID = _classID;
		energy = _energy;
		position = _position;
		lastUpdateEnergyTime = time = _time;
		color = _color;
	};

	virtual void Draw() const;

	virtual void UpdateMap() const;

	virtual void EraseOnScreen() const;

	virtual void EraseOnMap() const;

	virtual void Tick();

	virtual void ConsumeTime(const double dt);

	virtual void Go(const WormLogic direction);

	// проверить соотношение своей длины и энергии и удлиниться/укоротиться при необходимости
	virtual void CheckLength();

	// увеличить свою длину на 1 клетку, с хвоста
	virtual void Grow();

	// уменьшить свою длину на 1 клетку, с хвоста
	virtual void AntiGrow();

	// умереть (убрать себя с карты, с экрана), вызов Dead() теперь будет возвращать true
	virtual void Die();

	virtual bool Dead();

	// Уменьшить энергию в соответствии с прошедшим временем с последнего вызова этой функции.
	// Размножение (деление) при превышении некоторой пороговой величины энергии.
	// Смерть при понижении энергии до пороговой величины.
	void UpdateEnergy();

	// Если подошло время - вызвать Run() и перейти в нужном направлении
	void DoLogic();

public:
	virtual ~Worm()
	{
	}
};

#endif
