#ifndef MOUSEOVERABLE_H
#define MOUSEOVERABLE_H

#include <Vector.h>
#include "Element.h"

class SDLApplication;

namespace UI
{
	class MouseOverable : public Element
	{
	private:
		bool inside(const ScreenPoint& mouse) const;

	protected:
		virtual bool isMouseOver() const;

		virtual bool isInside(const SDL_MouseButtonEvent& Event) const;

	public:
		MouseOverable(SDLApplication* const app_);
	};
}

#endif
