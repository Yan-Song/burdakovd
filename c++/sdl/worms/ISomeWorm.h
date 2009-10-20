#ifndef ISOMEWORM_H
#define ISOMEWORM_H

#include "IWorm.h"
#include "color.h"

class WormsApplication;
class Worm;

// �������� ����� ������ �������� ��������� ����� ������������ ����� �������������� �����
// ����� �� ����������, � ������������ ��������� ����� ������ ����� �� �������� � ��� ������ (��� ��� ����� ������� protected),
// � ����� �������� ��������� ������� ������ ����� friend \\todo
class ISomeWorm : private IWorm
{
private:
	virtual void Initialize(WormsApplication* _app, const int _ID, const int classID, const double energy, const TPosition& position,
		const double _time, const Color& _color) = 0;

	// ��������� ����������� �����
	virtual void Draw() const = 0;

	// �������� ������ ����� �� ����� (�������� �� ��� ���������� �����)
	virtual void UpdateMap() const = 0;

	// ������� ����� � ������
	virtual void EraseOnScreen() const = 0;

	// ���������� ���� ������ �� ����� (������� �� CellEmpty)
	virtual void EraseOnMap() const = 0;

	virtual Color GetColor() const = 0;

	// ��������� ������ �����, ��������� ���� ��������, �������� ��� Energy, ���������� �� ������ ������
	// ���������� ����� � ������ ����� ����������� ������������� (=> ����� ������ ���� ������������ ����� ������� ����� ������)
	virtual void Tick() = 0;

	virtual bool Dead() = 0;
	
	friend class WormsApplication;
	friend class Worm;
public:
	virtual ~ISomeWorm()
	{
	}
};

#endif
