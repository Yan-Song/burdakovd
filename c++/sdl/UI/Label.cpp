#include <Color.h>
#include <Font.h>
#include "Label.h"

UI::Label::Label(SDLApplication* const app_, const std::string& text_, const SharedFont& font_, const Color& color_) 
	: UI::Element(app_), text(text_), font(font_), color(color_), image()
{
	UpdateSprite();
}

void UI::Label::UpdateSprite()
{
	if(text.empty())
	{
		image = SharedSprite();
		SetWidth(0);
		SetHeight(0);
	}
	else
	{
		image = SharedSprite(new Sprite(font, text, Palette::Black));
		SetWidth(image->GetWidth());
		SetHeight(image->GetHeight());
	}
}

const std::string& UI::Label::GetText() const
{
	return text;
}

SharedFont UI::Label::GetFont() const
{
	return font;
}

Color UI::Label::GetColor() const
{
	return color;
}

void UI::Label::SetColor(const Color& color_)
{
	color = color_;
}

void UI::Label::SetText(const std::string &newtext)
{
	text = newtext;

	UpdateSprite();
}

void UI::Label::SetFont(const SharedFont& newfont)
{
	font = newfont;

	UpdateSprite();
}

void UI::Label::Render()
{
	if(image)
	{
		Clip();

		image->BlitOnScreen(app, GetLeftBottom() +
			ScreenPointByCoords(GetWidth() - image->GetWidth(), GetHeight() - image->GetHeight()) / 2);
		
		UnClip();
	}	
}
