#include <iostream>
#include "Clickable.h"

UI::Clickable::Clickable(SDLApplication* const app) : MouseOverable(app), halfClicked(false), buttonDefault(false), buttonCancel(false)
{
	
}

void UI::Clickable::onMouseDown(const SDL_MouseButtonEvent& )
{
	
}

void UI::Clickable::onMouseUp(const SDL_MouseButtonEvent& )
{
	
}

void UI::Clickable::onClick()
{
	
}

bool UI::Clickable::isElementPressed() const
{
	return halfClicked && isMouseOver();
}

void UI::Clickable::ProcessEvent(const SDL_Event& Event)
{
	if(Event.type == SDL_MOUSEBUTTONDOWN && isInside(Event.button))
	{
		onMouseDown(Event.button);

		if(Event.button.button == SDL_BUTTON_LEFT)
		{
			halfClicked = true;
		}
	}
	else if(Event.type == SDL_MOUSEBUTTONUP)
	{
		if(isInside(Event.button))
		{
			if(Event.button.button == SDL_BUTTON_LEFT && halfClicked)
			{
				onClick();
			}

			onMouseUp(Event.button);
		}

		halfClicked = false;
	}
	else if(Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE && GetButtonCancel())
	{
		onClick();
	}
	else if(Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_RETURN && GetButtonDefault())
	{
		onClick();
	}
}	
