#ifndef REGISTRATOR_H
#define REGISTATOR_H

#include "IWormFactory.h"
#include "ISomeWorm.h"
#include <vector>
#include <string>

class Registrator
{
private:
	std::vector<IWormFactory*> factories;

	// delete ��� ���� ���������� ����� ������ � �����������
	inline void Register(IWormFactory* wf)
	{
		factories.push_back(wf);
	}

public:
	Registrator();

	// ���������� ������������������ ��������
	inline int Count() const
	{
		return factories.size();
	}

	// ��� ������ ��������� �������
	inline std::string ClassName(int index) const
	{
		return factories[index]->ClassName();
	}

	// ������ delete ��� ����� ��������� ����������� �� �����������
	inline ISomeWorm* Create(int index) const
	{
		return factories[index]->Create();
	}

	~Registrator()
	{
		for(unsigned int i = 0; i < factories.size(); ++i)
			delete factories[i];
	}
};

#endif