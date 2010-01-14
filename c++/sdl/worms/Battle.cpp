#include <SDLException.h>
#include <Sprite.h>
#include "Battle.h"
#include "Config.h"
#include "Engine.h"

class Battle::Util
{
public:
	class UIField : public UI::Element
	{
	private:
		UIField(const UIField& );
		UIField& operator =(const UIField& );

	private:
		Engine* const app;
		Battle* const parent;

	private: // sprites
		const Sprite borderl, borderr, bordert, borderb, borderlt, borderlb, borderrt, borderrb;
		const Sprite Empty;
		Sprite Food;

	public:
		UIField(Engine* const app_, Battle* const parent_)
			: UI::Element(app_), app(app_), parent(parent_),
			borderl("Sprites/border-l.png"),
			borderr("Sprites/border-r.png"),
			bordert("Sprites/border-t.png"),
			borderb("Sprites/border-b.png"),
			borderlt("Sprites/border-lt.png"),
			borderlb("Sprites/border-lb.png"),
			borderrt("Sprites/border-rt.png"),
			borderrb("Sprites/border-rb.png"),

			Empty("Sprites/EmptyCell.png"),
			Food("Sprites/EmptyCell.png") // это не опечатка
		{
			// две клетки на рамку
			SetWidth(Config::CellSize * (Config::FieldWidth + 2));
			SetHeight(Config::CellSize * (Config::FieldHeight + 2));

			// наложить картинку с едой куда надо
			Sprite("Sprites/FoodCell.png").BlitOnSprite(Food);
		}

	protected:
		void RenderField()
		{
			for(int y = 0; y < Config::FieldHeight; ++y)
				for(int x = 0; x < Config::FieldWidth; ++x)
				{
					const CellType cell = parent->Field.Get(x, y);
					const ScreenPoint position = ScreenPointByCoords(
						GetLeft() + (x + 1) * Config::CellSize, 
						GetBottom() + (y + 1) * Config::CellSize);

					if(cell == CellEmpty)
					{
						Empty.BlitOnScreen(app, position);
					}
					else if(cell == CellFood)
					{
						Food.BlitOnScreen(app, position);
					}
					else
					{
						throw NotImplementedException();
					}
				}
		}

		void RenderBorder()
		{
			const int bottom = GetBottom(), top = GetBottom() + GetHeight() - Config::CellSize;
			const int left = GetLeft(), right = GetLeft() + GetWidth() - Config::CellSize;

			// corners
			borderlb.BlitOnScreen(app, ScreenPointByCoords(left, bottom));
			borderlt.BlitOnScreen(app, ScreenPointByCoords(left, top));
			borderrb.BlitOnScreen(app, ScreenPointByCoords(right, bottom));
			borderrt.BlitOnScreen(app, ScreenPointByCoords(right, top));

			// just borders
			for(int i = 0; i < Config::FieldWidth; ++i)
			{
				bordert.BlitOnScreen(app, ScreenPointByCoords(left + (i + 1) * Config::CellSize, top));
				borderb.BlitOnScreen(app, ScreenPointByCoords(left + (i + 1) * Config::CellSize, bottom));
			}

			for(int i = 0; i < Config::FieldHeight; ++i)
			{
				borderl.BlitOnScreen(app, ScreenPointByCoords(left, bottom + (i + 1) * Config::CellSize));
				borderr.BlitOnScreen(app, ScreenPointByCoords(right, bottom + (i + 1) * Config::CellSize));
			}
		}

		virtual void Render()
		{
			RenderField();
			RenderBorder();
		}
	};

	class Graph : public UI::Element
	{
	};

	class Table : public UI::Element
	{
	};

	class Timer : public UI::Element
	{
	};

	class Speedometer : public UI::Element
	{
	};


};

Battle::Battle(Engine* const app_, const Teams& teams_)
	: UI::ElementSet(app_), app(app_), teams(teams_), Field(Config::FieldHeight, Config::FieldWidth)
{
	Maximize();

	const int margin = 10;

	const UI::SharedElement f(new Util::UIField(app, this));
	f->SetLeft(margin);
	f->SetBottom(app->Screen->h - margin - f->GetHeight());
	Add(f);
	// ... остальные графические элементы

	// инициализировать поле
	// накидать сколько надо еды туда
	for(int x = 0; x < Config::FieldWidth; ++x)
		for(int y = 0; y < Config::FieldHeight; ++y)
		{
			if(app->Rand(Config::FieldWidth * Config::FieldHeight) < Config::InitialFoodCount)
			{
				Field.Set(x, y, CellFood);
			}
		}
}

void Battle::Render()
{
	app->ClearScreen(Color(0xe0e0f0));

	ElementSet::Render();
}
