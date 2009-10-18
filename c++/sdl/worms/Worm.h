#ifndef WORM_H
#define WORM_H

#include "IMyWorm.h"
#include "ISomeWorm.h"
#include "WormLogic.h"
#include "color.h"
#include <vector>

class WormsApplication;

// �� ����� ������ ����� ������������� ��� �����
class Worm : public IMyWorm, public ISomeWorm
{
public:
	Worm() : dead(false)
	{
	}
private:
	WormsApplication* app;
	int ID, classID;
	double energy;
	TPosition position;
	// ��������� ����� �����
	double time;
	Color color;
	bool dead;

	double GetTime() const
	{
		return time;
	}

	// ���������� ������� ������ �� ������ �����, [0] - ������
    virtual const TPosition& Position() const
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

	virtual void Initialize(WormsApplication* _app, const int _ID, int const _classID, const double _energy, const TPosition& _position,
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

	virtual void Draw() const;

	virtual void UpdateMap() const;

	virtual void EraseOnScreen() const;

	virtual void EraseOnMap() const;

	virtual void Tick();

	virtual void ConsumeTime(const double dt);

	virtual void Go(const WormLogic direction);

	// ��������� ����������� ����� ����� � ������� � ����������/�����������
	virtual void CheckLength();

	// ��������� ���� ����� �� 1 ������
	virtual void Grow();

	// ��������� ���� ����� �� 1 ������
	virtual void AntiGrow();

	// �������
	virtual void Die();

	virtual bool Dead();

public:
	virtual ~Worm()
	{
	}
};

#endif
