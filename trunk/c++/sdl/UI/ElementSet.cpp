#include "ElementSet.h"

UI::ElementSet::ElementSet(SDLApplication* const app) : UI::Element(app)
{

}

void UI::ElementSet::Add(const SharedElement &element)
{
	elements.push_back(element);
}

void UI::ElementSet::ProcessEvent(const SDL_Event &Event)
{
	for(Elements::const_iterator it = elements.begin(); it != elements.end(); ++it)
		(*it)->ProcessEvent(Event);
}

void UI::ElementSet::Main()
{
	for(Elements::const_iterator it = elements.begin(); it != elements.end(); ++it)
		(*it)->Main();
}

void UI::ElementSet::Render()
{
	Clip();

	for(Elements::const_iterator it = elements.begin(); it != elements.end(); ++it)
		(*it)->Render();

	UnClip();
}
