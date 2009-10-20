#ifndef WORM_H
#define WORM_H

#include "IMyWorm.h"
#include "ISomeWorm.h"
#include "WormLogic.h"
#include "color.h"
#include <vector>
#include "SDL.h"

class WormsApplication;

// �� ����� ������ ����� ������������� ��� �����
class Worm : public IMyWorm, public ISomeWorm
{
public:
	Worm() : dead(false)
	{
	}
	
	virtual bool isPressed(const SDLKey key) const;

	// ����� �� ������������� [0, x)
	virtual int Rand(const int x) const;

	// �� ������� [x, y]
	virtual int Rand(const int x, const int y) const;

private:
	WormsApplication* app;
	TPosition position;
	int ID, classID;
	double energy;
	// ��������� ����� �����
	double time;
	// ����� ���������� ���������� �������
	double lastUpdateEnergyTime;
	Color color;
	bool dead;

	// ��������� ����� �����
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
		lastUpdateEnergyTime = time = _time;
		color = _color;
	};

	virtual void Draw() const;

	virtual void UpdateMap() const;

	virtual void EraseOnScreen() const;

	virtual void EraseOnMap() const;

	virtual void Tick();

	virtual void ConsumeTime(const double dt);

	virtual void Go(const WormLogic direction);

	// ��������� ����������� ����� ����� � ������� � ����������/����������� ��� �������������
	virtual void CheckLength();

	// ��������� ���� ����� �� 1 ������, � ������
	virtual void Grow();

	// ��������� ���� ����� �� 1 ������, � ������
	virtual void AntiGrow();

	// ������� (������ ���� � �����, � ������), ����� Dead() ������ ����� ���������� true
	virtual void Die();

	virtual bool Dead();

	// ��������� ������� � ������������ � ��������� �������� � ���������� ������ ���� �������.
	// ����������� (�������) ��� ���������� ��������� ��������� �������� �������.
	// ������ ��� ��������� ������� �� ��������� ��������.
	void UpdateEnergy();

	// ���� ������� ����� - ������� Run() � ������� � ������ �����������
	void DoLogic();

public:
	virtual ~Worm()
	{
	}
};

#endif
