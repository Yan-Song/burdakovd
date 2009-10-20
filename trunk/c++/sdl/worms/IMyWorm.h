#ifndef IMYWORM_H
#define IMYWORM_H

#include "IWorm.h"
#include "WormLogic.h"
#include "SDL.h"

// ������, ������� ����� ������������ ������ ������� �����
class IMyWorm : public IWorm
{
public:

	// �������� ������ �����
	virtual WormLogic Run() = 0;

	virtual bool isPressed(const SDLKey key) const = 0;

	virtual ~IMyWorm()
	{
	}
};

#endif
