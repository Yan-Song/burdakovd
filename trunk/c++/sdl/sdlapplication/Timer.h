#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
	long long startTicks;
public:
	Timer(void);
	~Timer(void);
	// ����� �� ������� �������, ���. � ��������� �� �����������
	double GetTime() const;
};

#endif
