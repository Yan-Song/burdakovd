#ifndef WORM_H
#define WORM_H

#include "IMyWorm.h"
#include "ISomeWorm.h"
#include <vector>
#include "color.h"

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
	// ��������� ����� �����
	double time;
	Color color;

	double GetTime()
	{
		return time;
	}

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
    virtual unsigned int GetID() const
	{
		return ID;
	}

    // �������������, ���������� ��� ������� ������ �����
    virtual unsigned int GetClassID() const
	{
		return classID;
	}

	virtual Color GetColor() const
	{
		return color;
	}

	virtual void Initialize(WormsApplication* _app, const int _ID, int const _classID, const double _energy, const std::vector<pii>& _position,
		const double _time, const Color& _color)
	{
		app = _app;
		ID = _ID;
		classID = _classID;
		energy = _energy;
		position = _position;
		time = _time;
		color = _color;
	};

	virtual void FullRender() const;

public:
	virtual ~Worm()
	{
	}
};

#endif
