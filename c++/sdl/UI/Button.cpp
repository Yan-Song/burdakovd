#include <Color.h>
#include <Utils.h>
#include "Button.h"

const std::string UI::Button::FontName = "Fonts/arial.ttf";
const int UI::Button::FontSize = 11;

UI::Button::Button(SDLApplication* const app, const std::string& caption_)
: Clickable(app), caption(caption_)
{
	SetWidth(73);
	SetHeight(21);
	updateSprites();
}

void UI::Button::onLayoutChanged()
{
	updateSprites();
}

void UI::Button::Render()
{
	(isElementPressed() ? pressed : (isMouseOver() ? hovered : normal))->Draw(app, GetCenter());
}

void UI::Button::updateSprites()
{
	const SharedSprite text(new Sprite(GetFont(FontName, FontSize), caption, Palette::Black));
	
	normal = SharedSprite(new Sprite("button-normal.bmp"));
	normal->SetColorKey(Color(0x00ff00));
	hovered = SharedSprite(new Sprite("button-hover.bmp"));
	hovered->SetColorKey(Color(0x00ff00));
	pressed = SharedSprite(new Sprite("button-pressed.bmp"));
	pressed->SetColorKey(Color(0x00ff00));

	text->Blit(*normal, ScreenPointByCoords(GetWidth() / 2, GetHeight() / 2));
	text->Blit(*hovered, ScreenPointByCoords(GetWidth() / 2, GetHeight() / 2));
	text->Blit(*pressed, ScreenPointByCoords(GetWidth() / 2, GetHeight() / 2));
}
