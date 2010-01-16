#include <algorithm>
#include <sstream>
#include <string>
#include <SDLException.h>
#include <Sprite.h>
#include "Battle.h"
#include "Config.h"
#include "Engine.h"
#include "IRenderer.h"
#include "ISomeWorm.h"
#include "IWorm.h"
#include "Registrator.h"
#include "WormsApplication.h"

class Battle::Util
{
private:
	

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
			Food("Sprites/Cell/Empty.png") // это не опечатка
		{
			// две клетки на рамку
			SetWidth(Config::CellSize * (Config::FieldWidth + 2));
			SetHeight(Config::CellSize * (Config::FieldHeight + 2));

			// наложить картинку с едой куда надо
			Sprite("Sprites/Cell/Food.png").BlitOnSprite(Food);
		}

	protected:
		void RenderField()
		{
			// прорисовать фон и пищу
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
						// Это не ошибка
						// просто для рендеринга ячейки с червём нужно больше информации (голова/хвост/направление...)
						// Поэтому черви будут рендериться в отдельном цикле
						Empty.BlitOnScreen(app, position);
					}
					else
					{
						throw NotImplementedException();
					}
				}

			// прорисовать червей
			for(Battle::WormCollection::const_iterator it = parent->CurrentGeneration.begin(); it != parent->CurrentGeneration.end(); ++it)
			{
				(*it)->GetRenderer()->Render(*it, this);
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

	// получает картинку из оттенков красного и серого
	// заменяет красный на то что нужно
	static SharedSprite MetaSprite(const std::string& filename, const Color& color)
	{
		SharedSprite sprite(new Sprite(filename));

		for(int x = 0; x < sprite->GetWidth(); ++x)
			for(int y = 0; y < sprite->GetHeight(); ++y)
			{
				const AlphaColor old = sprite->GetPixel(x, y);
				
				const int r = old.color.R, g = old.color.G, b = old.color.B;

				// яркость по белой компоненте
				const int light = (g + b) / 2;

				// яркость по основной цветовой компоненте
				const int main = r - light;

				sprite->SetPixel(x, y, AlphaColor((Palette::White * light + color * main) / 256, old.alpha));
			}

		return sprite;
	}

	static SharedSprite WormSprite(const std::string& filename, const Color& color)
	{
		const SharedSprite background(new Sprite("Sprites/Cell/Empty.png"));

		const SharedSprite raw(MetaSprite(filename, color));

		raw->BlitOnSprite(*background);

		return background;
	}

	static std::string RelativePosition(const SimplePoint& point, const SimplePoint& base)
	{
		if(point.X == base.X)
		{
			if(point.Y == base.Y + 1)
			{
				return "top";
			}
			else if(point.Y == base.Y - 1)
			{
				return "bottom";
			}
		}
		else if(point.Y == base.Y)
		{
			if(point.X == base.X + 1)
			{
				return "right";
			}
			else if(point.X == base.X - 1)
			{
				return "left";
			}
		}

		throw NotImplementedException();
	}

	class Renderer : public IRenderer
	{
	private:
		Renderer(const Renderer& );
		Renderer& operator =(const Renderer& );

	private:
		const SharedSprite
			head_bottom,
			head_top,
			head_left,
			head_right,

			tail_left,
			tail_right,
			tail_top,
			tail_bottom,

			body_lr,
			body_tb,
			body_lt,
			body_lb,
			body_rt,
			body_rb;

		SDLApplication* const app;
		Battle* const battle;
			
	public:
		Renderer(const Color& color, SDLApplication* const app_, Battle* const battle_) : IRenderer(),
			head_bottom(WormSprite("Sprites/Worm/Head/bottom.png", color)),
			head_top(WormSprite("Sprites/Worm/Head/top.png", color)),
			head_left(WormSprite("Sprites/Worm/Head/left.png", color)),
			head_right(WormSprite("Sprites/Worm/Head/right.png", color)),
	
			tail_left(WormSprite("Sprites/Worm/Tail/left.png", color)),
			tail_right(WormSprite("Sprites/Worm/Tail/right.png", color)),
			tail_top(WormSprite("Sprites/Worm/Tail/top.png", color)),
			tail_bottom(WormSprite("Sprites/Worm/Tail/bottom.png", color)),

			body_lr(WormSprite("Sprites/Worm/Body/lr.png", color)),
			body_tb(WormSprite("Sprites/Worm/Body/tb.png", color)),
			body_lt(WormSprite("Sprites/Worm/Body/lt.png", color)),
			body_lb(WormSprite("Sprites/Worm/Body/lb.png", color)),
			body_rt(WormSprite("Sprites/Worm/Body/rt.png", color)),
			body_rb(WormSprite("Sprites/Worm/Body/rb.png", color)),

			app(app_), battle(battle_)
		{
		}

		virtual void Render(const SharedSomeWorm& worm, const UI::Element* UIField) const
		{
			TPosition position = worm->Position();

			// удаляем повторения на всякий случай
			position.unique();

			if(position.size() < 2)
			{
				std::cout << "Warning: worm length < 2, can't render" << std::endl;
				return;
			}

			const TPosition::const_iterator head = position.begin();

			TPosition::const_iterator current = head;
			TPosition::const_iterator next = current; ++next;

			// рисуем голову
			const std::string hpos = RelativePosition(*next, *head);
			const ScreenPoint hsposition = ScreenPointByCoords(UIField->GetLeft() + (head->X + 1) * Config::CellSize, 
				UIField->GetBottom() + (head->Y + 1) * Config::CellSize);
			if(hpos == "left")
			{
				head_left->BlitOnScreen(app, hsposition);
			}
			else if(hpos == "right")
			{
				head_right->BlitOnScreen(app, hsposition);
			}
			else if(hpos == "top")
			{
				head_top->BlitOnScreen(app, hsposition);
			}
			else if(hpos == "bottom")
			{
				head_bottom->BlitOnScreen(app, hsposition);
			}
			else
			{
				throw NotImplementedException();
			}

			// переходим к body
			TPosition::const_iterator previous = current;
			++current; ++next;
			// рисуем в цикле тело
			for(; next != position.end(); ++previous, ++current, ++next)
			{
				const ScreenPoint sposition = ScreenPointByCoords(UIField->GetLeft() + (current->X + 1) * Config::CellSize,
					UIField->GetBottom() + (current->Y + 1) * Config::CellSize);
				const std::string previous_pos = RelativePosition(*previous, *current);
				const std::string next_pos = RelativePosition(*next, *current);
				std::string code = std::string(1, previous_pos[0]) + next_pos[0];
				std::sort(code.begin(), code.end());
				
				if(code == "lr")
				{
					body_lr->BlitOnScreen(app, sposition);
				}
				else if(code == "bt")
				{
					body_tb->BlitOnScreen(app, sposition);
				}
				else if(code == "bl")
				{
					body_lb->BlitOnScreen(app, sposition);
				}
				else if(code == "lt")
				{
					body_lt->BlitOnScreen(app, sposition);
				}
				else if(code == "br")
				{
					body_rb->BlitOnScreen(app, sposition);
				}
				else if(code == "rt")
				{
					body_rt->BlitOnScreen(app, sposition);
				}
				else
				{
					throw NotImplementedException();
				}
			}

			// рисуем хвост
			const std::string tpos = RelativePosition(*previous, *current);
			const ScreenPoint tsposition = ScreenPointByCoords(UIField->GetLeft() + (current->X + 1) * Config::CellSize, 
				UIField->GetBottom() + (current->Y + 1) * Config::CellSize);
			if(tpos == "left")
			{
				tail_left->BlitOnScreen(app, tsposition);
			}
			else if(tpos == "right")
			{
				tail_right->BlitOnScreen(app, tsposition);
			}
			else if(tpos == "top")
			{
				tail_top->BlitOnScreen(app, tsposition);
			}
			else if(tpos == "bottom")
			{
				tail_bottom->BlitOnScreen(app, tsposition);
			}
			else
			{
				throw NotImplementedException();
			}
		}
	};

	static SharedRenderer GenerateWormRenderer(const Color& color, SDLApplication* const app, Battle* const battle)
	{
		return SharedRenderer(new Renderer(color, app, battle));
	}
};

Battle::Battle(Engine* const app_, const Teams& teams_)
	: UI::ElementSet(app_), app(app_), teams(teams_), CurrentGeneration(), NextGeneration(), \
		lastWormID(0), timer(), renderers(), Field(Config::FieldHeight, Config::FieldWidth)
{
	timer.Start();

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

	const Registrator registrator;

	// посоздавать червей сколько было указано в настройках
	for(Teams::const_iterator team = teams.begin(); team != teams.end(); ++team)
	{
		for(size_t i = 0; i < team->Count; ++i)
		{
			SharedSomeWorm worm = registrator.Create(team->ID);

			++lastWormID;
			worm->Initialize(app, this, lastWormID, team->ID, Config::StartEnergy, 
				TPosition(1, GetFreeCell()), GetTime(), GetRenderer(team->color));

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

SharedRenderer Battle::GetRenderer(const Color &color)
{
	if(!renderers.count(color))
	{
		renderers[color] = Util::GenerateWormRenderer(color, app, this);
	}

	return renderers[color];
}
