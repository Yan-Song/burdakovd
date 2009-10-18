#ifndef IMYWORM_H
#define IMYWORM_H

#include "IWorm.h"
#include "WormLogic.h"

// ������, ������� ����� ������������ ������ ������� �����
class IMyWorm : public IWorm
{
public:

	// �������� ������ �����
	virtual WormLogic Run() = 0;

	virtual ~IMyWorm()
	{
	}
};

#endif
