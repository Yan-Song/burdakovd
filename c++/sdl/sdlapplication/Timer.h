#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
	long long startTicks;
public:
	Timer(void);
	~Timer(void);
	// время от запуска таймера, сек. С точностью до миллисекунд
	double GetTime() const;
};

#endif
