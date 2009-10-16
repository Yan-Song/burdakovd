#ifndef WORM_H
#define WORM_H

#include "IMyWorm.h"
#include "ISomeWorm.h"
#include <vector>

class WormsApplication;

// �� ����� ������ ����� ������������� ��� �����
class Worm : public IMyWorm, public ISomeWorm
{
public:
	Worm()
	{
	}
private:
	WormsApplication* app;
	int ID, classID;
	double energy;
	std::vector<pii> position;

	// ���������� ������� ������ �� ������ �����, [0] - ������
    virtual const std::vector<pii>& Position() const
	{
		return position;
	}
    
    // ��� �������
    virtual double Energy() const
	{
		return energy;
	}
    
    // �������������, ���������� ��� ������� ���������� �����
    virtual int GetID() const
	{
		return ID;
	}

    // �������������, ���������� ��� ������� ������ �����
    virtual int GetClassID() const
	{
		return classID;
	}

	virtual void Initialize(WormsApplication* _app, const int _ID, int const _classID, const double _energy, const std::vector<pii>& _position)
	{
		app = _app;
		ID = _ID;
		classID = _classID;
		energy = _energy;
		position = _position;
	};

public:
	
};

#endif
