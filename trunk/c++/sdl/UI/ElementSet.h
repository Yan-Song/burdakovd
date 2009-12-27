#ifndef ELEMENTSET_H
#define ELEMENTSET_H

#include <list>
#include "Element.h"

namespace UI
{
	class ElementSet : public UI::Element
	{
	protected:
		typedef std::list<UI::SharedElement> Elements;

		Elements elements;

		void Add(const SharedElement& element);

	public:
		ElementSet(SDLApplication* const app);

		virtual void ProcessEvent(const SDL_Event& Event);

		virtual void Main();

		virtual void Render();
	};
}

#endif
