#include "Element.h"

int UI::Element::GetWidth() const
{
	return width;
}

int UI::Element::GetHeight() const
{
	return height;
}

int UI::Element::GetBottom() const
{
	return bottom;
}

int UI::Element::GetLeft() const
{
	return left;
}

void UI::Element::SetWidth(const int w)
{
	width = w;
}

void UI::Element::SetHeight(const int h)
{
	height = h;
}

void UI::Element::SetLeft(const int l)
{
	left = l;
}

void UI::Element::SetBottom(const int b)
{
	bottom = b;
}

void UI::Element::ProcessEvent(const SDL_Event& )
{

}

void UI::Element::Main()
{

}

void UI::Element::Render()
{

}
