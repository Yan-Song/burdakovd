#ifndef MANUAL_H
#define MANUAL_H

#include "Worm.h"
#include "WormLogic.h"

// ������� � ���� ������ ������ �������� ��������� (� ���������� ID)
// ���� �� �������, �� ����� ����������� ������ � ������� ����� �������, ������������ ����������
// � LeaderID �������� ������� ID ������, ���� � ����-�� ID ������, �� �� �������� ��� �����, ��� �������� ������
// ����� ����������� � ����������, ��������� ������ �� ���
class Manual : public Worm
{
private:
	static unsigned int LeaderID;
	static SimplePoint LeaderPosition;
	static double LastLeaderPresenceTime;
public:
	Manual()
	{
		
	}

	virtual WormLogic Run();

	WormLogic FindFood();
	
	void InitiateElections();

	virtual ~Manual()
	{
	}
};

#endif
