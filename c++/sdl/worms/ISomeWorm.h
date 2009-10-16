#ifndef ISOMEWORM_H
#define ISOMEWORM_H

#include "IWorm.h"

class WormsApplication;

// �������� ����� ������ �������� ��������� ����� ������������ ����� �������������� �����
// ����� �� ����������, � ������������ ��������� ����� ������ ����� �� �������� � ��� ������ (��� ��� ����� ������� protected),
// � ����� �������� ��������� ������� ������ ����� friend \\todo
class ISomeWorm : private IWorm
{
private:
	virtual void Initialize(WormsApplication* _app, const int _ID, int const classID, const double energy, const std::vector<pii>& position) = 0;
};

#endif
