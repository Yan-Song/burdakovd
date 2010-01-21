#ifndef WORM_H
#define WORM_H

#include "IMyWorm.h"
#include "ISomeWorm.h"
#include "WormLogic.h"
#include "Color.h"
#include <vector>
#include "SDL.h"

class Engine;
class Battle;

// от этого класса будут наследоваться все черви
// Требования
// * Initialize нужно вызвать ровно один раз (он типа конструктора)
// * Не запускать никакие другие методы пока не вызван Initialize
// ИНВАРИАНТЫ:
// * Все инварианты выполняются после вызова Initialize, и сохраняются после вызова любых публичных методов,
//   а также приватных методов с соответствующими пометками
// * Мертвые черви на карте не отображаются, в последующих инвариантах под словом "червь" понимаем "живой червь"
// * Инвариант карты: на карте содержат значение CellWorm те и только те ячейки которые содержат тело червя
// * Инвариант отстутствия пересечений: каждая клетка содержит не более одного червя
// * Инвариант отсутствия самопересечений: Position() не содержит повторений
// (Когда червь умирает - все его ячейки стираются с карты, это следует из второго и третьего пункта)
class Worm : public IMyWorm, public ISomeWorm
{
public:
	Worm() : app(NULL), BattleState(NULL), position(), ID(0), classID(0), energy(0.0), time(0.0),
	     lastUpdateEnergyTime(0.0), renderer(), dead(false)
	{
	}

	virtual SimplePoint Mouse() const;

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

	virtual SharedRenderer GetRenderer() const
	{
		return renderer;
	}

private:
	Worm(const Worm& );
	Worm& operator =(const Worm& );

	Engine* app;
	Battle* BattleState;
	TPosition position;
	size_t ID, classID;
	double energy;
	// локальное время червя
	double time;
	// время последнего обновления энергии
	double lastUpdateEnergyTime;
	SharedRenderer renderer;
	bool dead;

	virtual void ModifyEnergy(const double delta);

	virtual void UpdateMap() const;

	virtual void EraseOnMap() const;

	virtual void Tick();

	virtual void ConsumeTime(const double dt);

	virtual void Go(const WormLogic direction);

	// проверить соотношение своей длины и энергии и удлиниться/укоротиться при необходимости
	virtual void CheckLength();

	// умереть (убрать себя с карты), вызов Dead() теперь будет возвращать true
	virtual void Die();

	// мертв ли?
	virtual bool Dead() const;

	// Уменьшить энергию в соответствии с прошедшим временем с последнего вызова этой функции.
	// Размножение (деление) при превышении некоторой пороговой величины энергии.
	// Смерть при понижении энергии до пороговой величины.
	void UpdateEnergy();

	// Если подошло время - вызвать Run() и перейти в нужном направлении
	void DoLogic();

	// попытаться найти свободную клетку и удлиннить хвост на одну ячейку
	// возвращает true если это сделать удалось
	bool Grow();

	virtual void Initialize(Engine* const _app, Battle* const battle_, const size_t _ID, const size_t _classID,
				const double _energy, const TPosition& _position,
				const double _time, const SharedRenderer& _renderer)
	{
		app = _app;
		BattleState = battle_;
		ID = _ID;
		classID = _classID;
		energy = _energy;
		position = _position;
		lastUpdateEnergyTime = time = _time;
		renderer = _renderer;

		UpdateMap();

		
		CheckLength();

		
	};

public:
	virtual ~Worm()
	{
	}
};

#endif
