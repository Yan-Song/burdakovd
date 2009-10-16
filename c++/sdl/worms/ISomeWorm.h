#ifndef ISOMEWORM_H
#define ISOMEWORM_H

#include "IWorm.h"

class WormsApplication;

// методами этого класса основная программа будет пользоваться чтобы манипулировать червём
// делаю их приватными, и наследование приватным чтобы логика червя не получила к ним доступ (для это нужно минимум protected),
// а класс основной программы получит доступ через friend \\todo
class ISomeWorm : private IWorm
{
private:
	virtual void Initialize(WormsApplication* _app, const int _ID, int const classID, const double energy, const std::vector<pii>& position) = 0;
};

#endif
