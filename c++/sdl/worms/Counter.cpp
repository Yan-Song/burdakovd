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
		SharedSprite normal, disabled, hovered;

		Button(const Button& );
		Button& operator =(const Button& );

	protected:
		UI::Counter* const parent;

	public:
		Button(SDLApplication* const app, const std::string& normalPath, const std::string& disabledPath,
			const std::string& hoveredPath, UI::Counter* const parent_) :
		UI::Clickable(app), normal(new Sprite(normalPath)), disabled(new Sprite(disabledPath)), hovered(new Sprite(hoveredPath)),
			      parent(parent_)
		{
			SetWidth(normal->GetWidth());
			SetHeight(normal->GetHeight());
		}

		virtual void Render()
		{
			const SharedSprite img = Enabled() ? (isMouseOver() ? hovered : normal) : disabled;

			img->Draw(app, GetCenter());
		}
	};
}

class UI::Counter::IncrementButton : public Button
{
public:
	IncrementButton(SDLApplication* const app, Counter* const parent_)
		: Button(app, "Sprites/UI/Button/Plus/normal.png", "Sprites/UI/Button/Plus/disabled.png", "Sprites/UI/Button/Plus/active.png", parent_)
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
		: Button(app, "Sprites/UI/Button/Minus/normal.png", "Sprites/UI/Button/Minus/disabled.png", "Sprites/UI/Button/Minus/active.png", parent_)
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
	Number(SDLApplication* const app) : UI::Label(app, "", ::GetFont("Fonts/Luismimurder.ttf", 20))
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
	dec->SetCenter(ScreenPointByCoords(GetLeft() + dec->GetWidth() / 2, GetCenter()[1]));

	num->SetCenter(GetCenter());

	inc->SetCenter(ScreenPointByCoords(GetRight() - inc->GetWidth() / 2, GetCenter()[1]));
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
	
	const int textWidth = 30;
	
	SetWidth(inc->GetWidth() + textWidth + dec->GetWidth());
	SetHeight(inc->GetHeight());

	Add(inc);
	Add(dec);
	Add(num);

	update();
}
