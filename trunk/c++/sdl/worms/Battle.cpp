#include <SDLException.h>
#include <Sprite.h>
#include "Battle.h"
#include "Config.h"
#include "Engine.h"
#include "IWorm.h"
#include "Registrator.h"
#include "WormsApplication.h"

class Battle::Util
{
private:
	class MetaSprite
	{
	public:
		//SharedSprite Create(
	};

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

			// Border
			borderl("Sprites/UI/Border/l.png"),
			borderr("Sprites/UI/Border/r.png"),
			bordert("Sprites/UI/Border/t.png"),
			borderb("Sprites/UI/Border/b.png"),
			borderlt("Sprites/UI/Border/lt.png"),
			borderlb("Sprites/UI/Border/lb.png"),
			borderrt("Sprites/UI/Border/rt.png"),
			borderrb("Sprites/UI/Border/rb.png"),

			/* // Worm
			worm_h_r("Sprites/Worm/Head/r.png"),
			worm_h_r("Sprites/Worm/Head/l.png"),
			worm_h_r("Sprites/Worm/Head/t.png"),
			worm_h_r("Sprites/Worm/Head/b.png"),*/

			// Cells
			Empty("Sprites/Cell/Empty.png"),
			Food("Sprites/Cell/Empty.png") // ��� �� ��������
		{
			// ��� ������ �� �����
			SetWidth(Config::CellSize * (Config::FieldWidth + 2));
			SetHeight(Config::CellSize * (Config::FieldHeight + 2));

			// �������� �������� � ���� ���� ����
			Sprite("Sprites/Cell/Food.png").BlitOnSprite(Food);
		}

	protected:
		void RenderField()
		{
			// ����������� ��� � ����
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
					else if(cell == CellWorm)
					{
						// ��� �� ������
						// ������ ��� ���������� ������ � ����� ����� ������ ���������� (������/�����/�����������...)
						// ������� ����� ����� ����������� � ��������� �����
						Empty.BlitOnScreen(app, position);
					}
					else
					{
						throw NotImplementedException();
					}
				}

			// ����������� ������
			for(Battle::WormCollection::const_iterator it = parent->CurrentGeneration.begin(); it != parent->CurrentGeneration.end(); ++it)
			{
				const TPosition& position = (*it)->Position();

				// � ����� ����������� �����, ������� ������, ����� ���� � �����
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
	: UI::ElementSet(app_), app(app_), teams(teams_), lastWormID(0), timer(), Field(Config::FieldHeight, Config::FieldWidth)
{
	timer.Start();

	Maximize();

	const int margin = 10;

	const UI::SharedElement f(new Util::UIField(app, this));
	f->SetLeft(margin);
	f->SetBottom(app->Screen->h - margin - f->GetHeight());
	Add(f);
	// ... ��������� ����������� ��������

	// ���������������� ����
	// �������� ������� ���� ��� ����
	for(int x = 0; x < Config::FieldWidth; ++x)
		for(int y = 0; y < Config::FieldHeight; ++y)
		{
			if(app->Rand(Config::FieldWidth * Config::FieldHeight) < Config::InitialFoodCount)
			{
				Field.Set(x, y, CellFood);
			}
		}

	Registrator registrator;

	// ����������� ������ ������� ���� ������� � ����������
	for(Teams::const_iterator team = teams.begin(); team != teams.end(); ++team)
	{
		for(size_t i = 0; i < team->Count; ++i)
		{
			SharedSomeWorm worm = registrator.Create(team->ID);

			++lastWormID;
			worm->Initialize(app, this, lastWormID, team->ID, Config::StartEnergy, TPosition(1, GetFreeCell()), GetTime(), SharedRenderer());

			CurrentGeneration.push_back(worm);
		}
	}
}

void Battle::Render()
{
	app->ClearScreen(Color(0xe0e0f0));

	ElementSet::Render();
}

double Battle::GetTime() const
{
	return timer.GetTime();
}

SimplePoint Battle::GetFreeCell() const
{
	SimplePoint point(0, 0);

	do
	{
		point.X = app->Rand(Field.Width);
		point.Y = app->Rand(Field.Height);
	}
	while(Field.Get(point.X, point.Y) != CellEmpty);

	return point;
}
