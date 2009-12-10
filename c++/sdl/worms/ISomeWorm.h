#ifndef ISOMEWORM_H
#define ISOMEWORM_H

#include <Color.h>
#include <Shared.h>
#include "IWorm.h"

class WormsApplication;
class Worm;

// методами этого класса основная программа будет пользоваться чтобы манипулировать червём
// делаю их приватными, и наследование приватным чтобы логика червя не получила к ним доступ (для это нужно минимум protected),
// а класс основной программы получит доступ через friend \\todo
class ISomeWorm : private IWorm
{
private:
	virtual void Initialize(WormsApplication* _app, const size_t _ID, const size_t classID,
				const double energy, const TPosition& position,
				const double _time, const Color& _color) = 0;

	// полностью прорисовать червя
	virtual void Draw() const = 0;

	// обновить ячейки червя на карте (пометить их как содержащие червя)
	virtual void UpdateMap() const = 0;

	// стереть червя с экрана
	virtual void EraseOnScreen() const = 0;

	// освободить свои ячейки на карте (сделать их CellEmpty)
	virtual void EraseOnMap() const = 0;

	virtual Color GetColor() const = 0;

	// выполнить логику червя, двигаться если возможно, обновить его Energy, вызывается на каждом фрейме
	// обновление карты и экрана будет произведено автоматически (=> экран должен быть заблокирован перед вызовом этого метода)
	virtual void Tick() = 0;

	virtual bool Dead() = 0;

	friend class WormsApplication;

	friend class Worm;

public:
	virtual ~ISomeWorm()
	{
	}
};

typedef Shared::shared_ptr<ISomeWorm> SharedSomeWorm;

#endif
