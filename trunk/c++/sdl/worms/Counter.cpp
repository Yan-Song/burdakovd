#include <sstream>
#include <Sprite.h>
#include <UI/Clickable.h>
#include <UI/Label.h>
#include "Counter.h"

namespace
{
	class Button : public UI::Clickable
	{
	private:
		SharedSprite normal, disabled;

		Button(const Button& );
		Button& operator =(const Button& );

	protected:
		UI::Counter* const parent;

	public:
		Button(SDLApplication* const app, const std::string& normalPath, const std::string& disabledPath,
		      UI::Counter* const parent_) :
		UI::Clickable(app), normal(new Sprite(normalPath)), disabled(new Sprite(disabledPath)),
			      parent(parent_)
		{

		}

		virtual void Render()
		{
			SharedSprite img = Enabled() ? normal : disabled;

			img->BlitOnScreen(app, GetLeftBottom() +
				ScreenPointByCoords(GetWidth() - img->GetWidth(), GetHeight() - img->GetHeight()) / 2);
		}
	};
}

class UI::Counter::IncrementButton : public Button
{
public:
	IncrementButton(SDLApplication* const app, Counter* const parent_)
		: Button(app, "Sprites/plus.png", "Sprites/plus-disabled.png", parent_)
	{
	}

	virtual void onClick()
	{
		parent->increment();
	}
};

class UI::Counter::DecrementButton : public Button
{
public:
	DecrementButton(SDLApplication* const app, Counter* const parent_)
		: Button(app, "Sprites/minus.png", "Sprites/minus-disabled.png", parent_)
	{
	}

	virtual void onClick()
	{
		parent->decrement();
	}
};

class UI::Counter::Number : public UI::Label
{
public:
	Number(SDLApplication* const app) : UI::Label(app, "", ::GetFont("Fonts/arialbd.ttf", 20))
	{
	}
};

void UI::Counter::update()
{
	currentValue = std::max(currentValue, minValue);
	currentValue = std::min(currentValue, maxValue);

	inc->SetEnabled(currentValue < maxValue);
	dec->SetEnabled(currentValue > minValue);

	std::ostringstream os;
	os << currentValue;

	num->SetText(os.str());

	num->SetCenter(GetCenter());
}

void UI::Counter::increment()
{
	++currentValue;
	update();
}

void UI::Counter::decrement()
{
	--currentValue;
	update();
}

int UI::Counter::GetValue() const
{
	return currentValue;
}

void UI::Counter::SetValue(const int newvalue)
{
	currentValue = newvalue;
	update();
}

void UI::Counter::onLayoutChanged()
{
	dec->SetHeight(GetHeight());
	dec->SetWidth(GetWidth() / 3);
	dec->SetLeft(GetLeft());
	dec->SetBottom(GetBottom());

	num->SetCenter(GetCenter());

	inc->SetHeight(GetHeight());
	inc->SetWidth(GetWidth() / 3);
	inc->SetLeft(GetLeft() + 2 * GetWidth() / 3);
	inc->SetBottom(GetBottom());
}

UI::Counter::Counter(SDLApplication* const app, const int min, const int max, const int current, const ScreenPoint LeftBottom)
	:
	UI::ElementSet(app),
	inc(new IncrementButton(app, this)),
	dec(new DecrementButton(app, this)),
	num(new Number(app)),
	minValue(min),
	maxValue(max),
	currentValue(current)
{
	SetLeft(LeftBottom[0]);
	SetBottom(LeftBottom[1]);
	SetWidth(72);
	SetHeight(24);

	Add(inc);
	Add(dec);
	Add(num);

	update();
}
