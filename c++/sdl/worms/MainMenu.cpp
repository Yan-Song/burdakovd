#include <Color.h>
#include <SDLApplication.h>
#include <UI/MouseOverable.h>
#include "MainMenu.h"

namespace
{
	class test : public UI::MouseOverable
	{
	public:
		test(SDLApplication* const app_) : UI::MouseOverable(app_)
		{
			SetHeight(50);
			SetWidth(100);
			SetBottom(200);
			SetLeft(200);
		}

		virtual void Render()
		{
			const Color color = isMouseOver() ? Palette::Gray : Palette::Gray / 2;

			app->FillRectangle(
				ScreenPointByCoords(GetLeft(), GetBottom()),
				ScreenPointByCoords(GetLeft() + GetWidth(), GetBottom() + GetHeight()), color);
		}

		virtual void Main()
		{
			
		}
	};
}

MainMenu::MainMenu(SDLApplication* const app) : element(new test(app))
{
	
}

void MainMenu::ProcessEvent(const SDL_Event& Event)
{
	element->ProcessEvent(Event);
}

void MainMenu::Main()
{
	element->Main();
}

void MainMenu::Render()
{
	element->Render();
}
