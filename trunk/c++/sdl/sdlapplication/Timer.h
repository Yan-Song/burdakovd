#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
private:
	Uint32 startTicks;
public:
	Timer(void);
	~Timer(void);
	// ����� �� ������� �������, ���. � ��������� �� �����������
	double GetTime() const;
	void Reset();
};

#endif
