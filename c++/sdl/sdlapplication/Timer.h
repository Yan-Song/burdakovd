#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

// 1) все методы этого класса можно вызывать только после того как инициализирована SDL
// (создавать экземпляры этого класса можно и раньше)
class Timer
{
private:
	// когда таймер работает, эта переменная хранит значение SDL_GetTicks() в момент его запуска
	// когда он на паузе - то значение таймера
	Uint32 ticks;
	bool started;
	bool paused;

public:
	Timer();
	
	void Start();
	
	void Stop();

	void Pause();

	void Resume();

	// значение таймера в миллисекундах
	Uint32 GetTicks() const;

	// значение таймера в секундах, с точностью до тысячных
	double GetTime() const;

	// прошло ли заданное время с момента запуска таймера
	inline bool Elapsed(Uint32 time_ms) const
	{
		return GetTicks() >= time_ms;
	}

	~Timer();
};

#endif
