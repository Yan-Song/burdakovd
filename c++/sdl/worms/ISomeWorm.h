#ifndef ISOMEWORM_H
#define ISOMEWORM_H

#include "IWorm.h"
#include "color.h"

class WormsApplication;

// �������� ����� ������ �������� ��������� ����� ������������ ����� �������������� �����
// ����� �� ����������, � ������������ ��������� ����� ������ ����� �� �������� � ��� ������ (��� ��� ����� ������� protected),
// � ����� �������� ��������� ������� ������ ����� friend \\todo
class ISomeWorm : private IWorm
{
private:
	virtual void Initialize(WormsApplication* _app, const int _ID, int const classID, const double energy, const std::vector<pii>& position,
		const double _time, const Color& _color) = 0;

	// ��������� ����������� �����
	virtual void FullRender() const = 0;

	virtual Color GetColor() const = 0;
	
	friend WormsApplication;
public:
	virtual ~ISomeWorm()
	{
	}
};

#endif
