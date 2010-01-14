#include <Color.h>
#include <Font.h>
#include <Utils.h>
#include "Button.h"

const std::string UI::Button::FontName = "Fonts/arial.ttf";
const int UI::Button::FontSize = 11;

UI::Button::Button(SDLApplication* const app, const std::string& caption_)
: Clickable(app), caption(caption_), normal(), hovered(), pressed()
{
	SetWidth(73);
	SetHeight(21);
}

void UI::Button::onLayoutChanged()
{
	updateSprites();
}

void UI::Button::Render()
{
	Clip();

	(isElementPressed() ? pressed : (isMouseOver() ? hovered : normal))->BlitOnScreen(app, GetLeftBottom());

	UnClip();
}

void UI::Button::updateSprites()
{
	const SharedSprite text(new Sprite(GetFont(FontName, FontSize), caption, Palette::Black));

	normal = SharedSprite(new Sprite("Sprites/UI/Button/normal.bmp"));
	normal->SetColorKey(Color(0x00ff00));
	hovered = SharedSprite(new Sprite("Sprites/UI/Button/hover.bmp"));
	hovered->SetColorKey(Color(0x00ff00));
	pressed = SharedSprite(new Sprite("Sprites/UI/Button/pressed.bmp"));
	pressed->SetColorKey(Color(0x00ff00));

	text->BlitOnSprite(*normal, ScreenPointByCoords(GetWidth() / 2, GetHeight() / 2));
	text->BlitOnSprite(*hovered, ScreenPointByCoords(GetWidth() / 2, GetHeight() / 2));
	text->BlitOnSprite(*pressed, ScreenPointByCoords(GetWidth() / 2, GetHeight() / 2));
}
