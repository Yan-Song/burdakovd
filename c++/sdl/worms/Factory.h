#ifndef FACTORY_H
#define FACTORY_H

#include "ISomeWorm.h"
#include "IWormFactory.h"

// W ������ ���� ����������� Worm, �� ��� ������� ��� ����������� � �������?
template<class W>
class Factory : public IWormFactory
{
private:
	std::string _ClassName;

public:
	Factory(const std::string& __ClassName) : _ClassName(__ClassName)
	{
	};

	// ������ delete ��� ����� ��������� ����������� �� �����������
	virtual ISomeWorm* Create() const
	{
		return new W();
	}

	virtual std::string ClassName() const
	{
		return _ClassName;
	}
};

#endif
