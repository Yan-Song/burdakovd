#ifndef ELEMENTSET_H
#define ELEMENTSET_H

#include <list>
#include <ISimpleGameLoop.h>
#include "Element.h"

namespace UI
{
	class ElementSet : public ISimpleGameLoop
	{
	protected:
		typedef std::list<SharedElement> Elements;

		Elements elements;

		void Add(const SharedElement& element);

	public:
		virtual void ProcessEvent(const SDL_Event& Event);

		virtual void Main();

		virtual void Render();
	};
}

#endif
