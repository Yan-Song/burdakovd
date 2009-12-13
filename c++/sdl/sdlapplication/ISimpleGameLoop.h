#ifndef ISIMPLEGAMELOOP_H
#define ISIMPLEGAMELOOP_H

#include <SDL.h>

class ISimpleGameLoop
{
public:
	virtual void ProcessEvent(const SDL_Event&) = 0; // обработать событие, поступившее от пользователя
	virtual void Main() = 0; // основная логика
	virtual void Render() = 0; // без комментариев
};

#endif
