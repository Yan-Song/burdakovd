#ifndef UI_COLORSELECTOR_H
#define UI_COLORSELECTOR_H

#include <Color.h>
#include "Clickable.h"

namespace UI
{
	class ColorSelector : public UI::Clickable
	{
	private:
		Color RandomColor();

	public:
		Color color;

		ColorSelector(SDLApplication* const app_);

		virtual void onClick();

		virtual void Render();
	};

	typedef Shared::shared_ptr<UI::ColorSelector> SharedColorSelector;
}

#endif
