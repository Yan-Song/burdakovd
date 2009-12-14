#ifndef MOUSEOVERABLE_H
#define MOUSEOVERABLE_H

#include "Element.h"

class SDLApplication;

namespace UI
{
	class MouseOverable : public Element
	{
	protected:
		SDLApplication* app;

		virtual bool isMouseOver() const;

	public:
		MouseOverable(SDLApplication* const app_);
	};
}

#endif
