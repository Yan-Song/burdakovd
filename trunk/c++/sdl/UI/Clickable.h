#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <SDL.h>
#include "MouseOverable.h"

namespace UI
{
	class Clickable : public MouseOverable
	{
	private:
		bool halfClicked;

	protected:
		// вызывается в момент нажатия левой кнопки мыши в пределах элемента управления
		virtual void onMouseDown(const SDL_MouseButtonEvent& );

		// вызывается в момент отпускания левой кнопки мыши в пределах элемента управления
		// при условии, что нажата она была также над этим элементом
		virtual void onMouseUp(const SDL_MouseButtonEvent& );

		// вызывается при нажатии и отпускании левой кнопки мыши над элементом управления
		// между этими двумя событиями указатель мыши мог выходить за пределы элемента
		virtual void onClick();

		// "зажат" ли сейчас элемент управления
		// истинно в том случае если ЛКМ была нажата над этим элементом
		// и сейчас находится над ним, и ещё не отпущена
		// может использоваться для различной прорисовки "нажатого" и "не нажатого" элемента управления
		virtual bool isElementPressed() const;

	public:
		Clickable(SDLApplication* const app);

		virtual void ProcessEvent(const SDL_Event& Event);
	};
}

#endif
