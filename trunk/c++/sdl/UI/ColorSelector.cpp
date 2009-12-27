#include <SDLApplication.h>
#include "ColorSelector.h"

UI::ColorSelector::ColorSelector(SDLApplication *const app) : UI::Clickable(app), color(RandomColor())
{
}

void UI::ColorSelector::onClick()
{
	color = RandomColor();
}

void UI::ColorSelector::Render()
{
	Clip();

	const ScreenPoint LeftBottom = ScreenPointByCoords(GetLeft(), GetBottom());
	const ScreenPoint WidthHeight = ScreenPointByCoords(GetWidth(), GetHeight());

	app->FillRectangle(LeftBottom, LeftBottom + WidthHeight, color);

	UnClip();
}

Color UI::ColorSelector::RandomColor()
{
	return Color(app->Rand(256), app->Rand(256), app->Rand(256));
}
