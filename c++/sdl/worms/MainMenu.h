#ifndef MAINMENU_H
#define MAINMENU_H

#include <ISimpleGameLoop.h>

class MainMenu : public ISimpleGameLoop
{
public:
	virtual void ProcessEvent(const SDL_Event&); // обработать событие, поступившее от пользователя
	virtual void Main(); // основная логика
	virtual void Render(); // без комментариев
};

#endif
