#ifndef ISOMEWORM_H
#define ISOMEWORM_H

#include <Color.h>
#include <Shared.h>
#include "IRenderer.h"
#include "IWorm.h"

class Battle;
class Engine;
class Worm;


// методами этого класса основная программа будет пользоваться чтобы манипулировать червём
// делаю их приватными, и наследование приватным чтобы логика червя не получила к ним доступ (для это нужно минимум protected),
// а класс основной программы получит доступ через friend \\todo
class ISomeWorm : private IWorm
{
private:
	virtual void Initialize(Engine* const _app, Battle* const battle_, const size_t _ID, const size_t classID,
				const double energy, const TPosition& position,
				const double _localtime, const SharedRenderer& _renderer) = 0;

	// обновить ячейки червя на карте (пометить их как содержащие червя)
	virtual void UpdateMap() const = 0;

	// освободить свои ячейки на карте (сделать их CellEmpty)
	virtual void EraseOnMap() const = 0;

	virtual SharedRenderer GetRenderer() const = 0;

	// выполнить логику червя если пришло время, двигаться если возможно, обновить его Energy, вызывается на каждом фрейме
	// обновление карты будет произведено автоматически
	virtual void Tick() = 0;

	virtual bool Dead() const = 0;

	friend class Battle;
	friend class Worm;

public:
	virtual ~ISomeWorm()
	{
	}
};

typedef Shared::shared_ptr<ISomeWorm> SharedSomeWorm;

#endif
