#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <SDLApplication.h>
#include <SDLException.h>
#include <Sprite.h>
#include <Timer.h>
#include <Utils.h>
#include <UI/Button.cpp>
#include "Battle.h"
#include "Config.h"
#include "Engine.h"
#include "IRenderer.h"
#include "ISomeWorm.h"
#include "IWorm.h"
#include "MainMenu.h"
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
		const Sprite Empty, Food, Selected;

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

			// Cells
			Empty("Sprites/Cell/Empty.png"),
			Food("Sprites/Cell/Food.png"),
			Selected("Sprites/Cell/Selected.png")
		{
			// две клетки на рамку
			SetWidth(Config::CellSize * (Config::FieldWidth + 2));
			SetHeight(Config::CellSize * (Config::FieldHeight + 2));
		}

		// над какой ячейкой находится указатель мыши
		SimplePoint MousePosition(const int x, const int y) const
		{
			const int sdx = x - GetLeft(), sdy = y - GetBottom();

			const int dx = sdx / Config::CellSize - 1;
			const int dy = sdy / Config::CellSize - 1;

			return SimplePoint(dx, dy);
		}

		SimplePoint MousePosition() const
		{
			const ScreenPoint p = app->GetMousePosition();

			return MousePosition(p[0], p[1]);
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

					Empty.BlitOnScreen(app, position);

					if(cell == CellEmpty)
					{
					}
					else if(cell == CellFood)
					{
						Food.BlitOnScreen(app, position);
					}
					else if(cell == CellWorm)
					{
					}
					else
					{
						throw NotImplementedException();
					}

					if(SimplePoint(x, y) == MousePosition())
					{
						Selected.BlitOnScreen(app, position);
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
	private:
		Graph(const Graph& );
		Graph& operator =(const Graph& );

	private:
		Engine* const app;
		const Battle* const battle;

		typedef std::list<double> TeamGraphStats;
		typedef std::map<size_t, TeamGraphStats> TeamsGraphStats;
		TeamsGraphStats stats;

		Timer tickTimer;
		

	public:
		Graph(Engine* const app_, Battle* const battle_) : UI::Element(app_), app(app_), battle(battle_), stats(), tickTimer()
		{
			SetPadding(10);

			for(Teams::const_iterator it = battle->teams.begin(); it != battle->teams.end(); ++it)
			{
				stats[it->ID] = TeamGraphStats();
			}

			tickTimer.Start();
		}

	private:
		void RemoveOld()
		{
			for(TeamsGraphStats::iterator team = stats.begin(); team != stats.end(); ++team)
			{
				const size_t limit = static_cast<size_t>(GetInnerWidth()) * 9 / 10 / Config::GraphStep; // 90%

				while(team->second.size() > limit)
				{
					team->second.pop_front();
				}
			}
		}

		double maxCount() const
		{
			double ans = 1;

			for(TeamsGraphStats::const_iterator team = stats.begin(); team != stats.end(); ++team)
			{
				if(!team->second.empty())
				{
					ans = std::max(ans, *std::max_element(team->second.begin(), team->second.end()));
				}
			}

			return ans;
		}

		void RenderBorder() const
		{
			// \todo
		}

		void RenderGraph() const
		{
			const SimplePoint a(GetInnerLeft(), GetInnerBottom());
			const SimplePoint b(GetInnerRight(), GetInnerTop());

			// фон
			app->FillRectangle(ScreenPointByCoords(a.X, a.Y), ScreenPointByCoords(b.X, b.Y), Config::GraphBackground);

			const double high = maxCount(); // чтоб сверху отступ был
			const double bottomPadding = 0.1;
			const double topPadding = 0.1;

			// сами графики
			for(Teams::const_iterator team = battle->teams.begin(); team != battle->teams.end(); ++team)
			{
				std::list<int> ys;

				const TeamsGraphStats::const_iterator tstats = stats.find(team->ID);

				for(TeamGraphStats::const_iterator it = tstats->second.begin(); it != tstats->second.end(); ++it)
				{
					ys.push_back(static_cast<int>(
						GetBottom() +
						GetInnerHeight() * (*it + bottomPadding * high)
						/ (1 + topPadding + bottomPadding) / high));
				}

				if(ys.size() > 1)
				{
					std::list<int>::const_iterator current = ys.begin(), next = ys.begin();
					++next;

					for(int curx = GetInnerLeft(); next != ys.end(); curx += Config::GraphStep, ++current, ++next)
					{
						const int nextx = curx + Config::GraphStep;

						app->DrawSegment(ScreenPointByCoords(curx, *current), ScreenPointByCoords(nextx, *next), team->color);
					}
				}
			}
		}

	protected:
		virtual void Main()
		{
			// если пришло время обновить график
			if(tickTimer.GetTime() >= Config::GraphUpdateFrequency)
			{
				// сначала всем записываем 0.0
				for(TeamsGraphStats::iterator it = stats.begin(); it != stats.end(); ++it)
				{
					it->second.push_back(0.0);
				}

				// проходя по списку всех червей, добавляем командам их хп
				for(Battle::WormCollection::const_iterator it = battle->CurrentGeneration.begin(); it != battle->CurrentGeneration.end(); ++it)
				{
					double& teamHP = stats[(*it)->GetClassID()].back();
					teamHP += (*it)->Energy() - Config::DeathEnergyLevel;
				}
				
				RemoveOld();

				// сбросить таймер
				tickTimer.Start();
			}
		}

		virtual void Render()
		{
			RenderBorder();
			RenderGraph();
		}

		virtual void UpdateLayout()
		{
			RemoveOld();
		}

		
	};

	class TeamsTable : public UI::Element
	{
	private:
		TeamsTable(const TeamsTable& );
		TeamsTable& operator =(const TeamsTable& );

	private:
		Engine* const app;
		Battle* const battle;

	public:
		TeamsTable(Engine* const app_, Battle* const battle_) : UI::Element(app_), app(app_), battle(battle_)
		{
		}

	protected:
		virtual void Render()
		{
			const int xoffset = GetInnerLeft();
			const int itemHeight = 50;

			int index = 0;
			for(Teams::const_iterator team = battle->teams.begin(); team != battle->teams.end(); ++team, ++index)
			{
				const int yoffset = GetInnerTop() - index * itemHeight;

				const SharedSprite name(new Sprite(GetFont("Fonts/arialbd.ttf", 14), battle->registrator.ClassName(team->ID), team->color));
				std::ostringstream info;

				int count = 0;
				double hp = 0.0;

				for(Battle::WormCollection::const_iterator it = battle->CurrentGeneration.begin(); it != battle->CurrentGeneration.end(); ++it)
				{
					if((*it)->GetClassID() == team->ID)
					{
						++count;
						hp += (*it)->Energy();
					}
				}

				const int ihp = static_cast<int>(hp);

				info << "Count: " << count << ",  " << "Energy: " << ihp;

				const SharedSprite sinfo(new Sprite(GetFont("Fonts/arial.ttf", 10), info.str(), Palette::Black));

				const int distance = 3;
				name->BlitOnScreen(app, ScreenPointByCoords(xoffset, yoffset - name->GetHeight()));
				sinfo->BlitOnScreen(app, ScreenPointByCoords(xoffset, yoffset - name->GetHeight() - distance - sinfo->GetHeight()));
			}
		}
	};

	class Timer : public UI::Element
	{
	private:
		Timer(const Timer& );
		Timer& operator =(const Timer& );

	private:
		Engine* const app;
		const Battle* const battle;

	public:
		Timer(Engine* const app_, Battle* const battle_) : UI::Element(app_), app(app_), battle(battle_)
		{
		}

	private:
		void RenderBorder() const
		{
			// \todo
		}

		void RenderText() const
		{
			const int time = static_cast<int>(battle->GetTime());
			const int hours = time / 60 / 60;
			const int minutes = time / 60 % 60;
			const int seconds = time % 60;
			
			std::ostringstream text;
			text << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2) << seconds;

			// \todo: рамка
			const SharedSprite stext(new Sprite(SharedFont(new Font("Fonts/arialbd.ttf", 32)), text.str(), Palette::Black));

			stext->Draw(app, GetCenter());
		}

	protected:
		virtual void Render()
		{
			RenderBorder();
			RenderText();
		}
	};

	class ExitButton : public UI::Button
	{
	private:
		ExitButton(const ExitButton& );
		ExitButton& operator =(const ExitButton& );

	private:
		Engine* const app;
		Battle* const battle;

	public:
		ExitButton(Engine* const app_, Battle* const battle_) : UI::Button(app_, "Menu"), app(app_), battle(battle_)
		{
		}

	protected:
		virtual void onClick()
		{
			battle->Pause();
			app->SetNextState(SharedState(new MainMenu(app, app->GetCurrentState())));
		}
	};

	class RestartButton : public UI::Button
	{
	private:
		RestartButton(const RestartButton& );
		RestartButton& operator =(const RestartButton& );

	private:
		Engine* const app;
		Battle* const battle;

	public:
		RestartButton(Engine* const app_, Battle* const battle_) : UI::Button(app_, "Restart"), app(app_), battle(battle_)
		{
		}

	protected:
		virtual void onClick()
		{
			app->SetNextState(SharedState(new Battle(app, battle->teams)));
		}
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
		return MetaSprite(filename, color);
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
			body_rb,
			
			Selected;

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

			Selected(new Sprite("Sprites/Cell/Selected.png")),

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
				const ScreenPoint sposition = ScreenPointByCoords(
					UIField->GetLeft() + (current->X + 1) * Config::CellSize,
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

			bool selected = false;
			for(TPosition::const_iterator p = position.begin(); p != position.end(); ++p)
			{
				if(*p == dynamic_cast<const ::Battle::Util::UIField*>(UIField)->MousePosition())
				{
					selected = true;
				}
			}

			if(selected)
			{
				for(TPosition::const_iterator p = position.begin(); p != position.end(); ++p)
				{
					const ScreenPoint tsposition = ScreenPointByCoords(UIField->GetLeft() + (p->X + 1) * Config::CellSize, 
						UIField->GetBottom() + (p->Y + 1) * Config::CellSize);

					Selected->BlitOnScreen(app, tsposition);
				}
			}
		}
	};

	static SharedRenderer GenerateWormRenderer(const Color& color, SDLApplication* const app, Battle* const battle)
	{
		return SharedRenderer(new Renderer(color, app, battle));
	}
};

Battle::Battle(Engine* const app_, const Teams& teams_)
	: UI::ElementSet(app_), app(app_), teams(teams_), CurrentGeneration(), NextGeneration(), lastWormID(0), timer(), \
	foodMade(0), background(new Sprite("Sprites/UI/Battle/background.png")), Field(Config::FieldHeight, Config::FieldWidth), registrator()
{
	timer.Start();

	Maximize();

	const int margin = 10;

	const UI::SharedElement f(new Util::UIField(app, this));
	f->SetLeft(margin);
	f->SetBottom(GetHeight() - margin - f->GetHeight());
	Add(f);

	const UI::SharedElement g(new Util::Graph(app, this));
	g->SetLeft(margin);
	g->SetBottom(margin);
	g->SetHeight(GetHeight() - 3 * margin - f->GetHeight());
	g->SetWidth(f->GetWidth());
	Add(g);

	const UI::SharedElement t(new Util::Timer(app, this));
	t->SetLeft(2 * margin + f->GetWidth());
	t->SetHeight(50);
	t->SetBottom(GetHeight() - margin - t->GetHeight());
	t->SetWidth(GetWidth() - 3 * margin - f->GetWidth());
	Add(t);

	const Shared::shared_ptr<UI::Button> quitButton(new Util::ExitButton(app, this));
	quitButton->SetCenter(ScreenPointByCoords(t->GetCenter()[0], t->GetBottom() - margin - quitButton->GetHeight() / 2));
	quitButton->SetButtonCancel(true);
	Add(quitButton);

	const Shared::shared_ptr<UI::Button> restartButton(new Util::RestartButton(app, this));
	restartButton->SetCenter(ScreenPointByCoords(t->GetCenter()[0], quitButton->GetBottom() - margin - restartButton->GetHeight() / 2));
	Add(restartButton);

	const UI::SharedElement tt(new Util::TeamsTable(app, this));
	tt->SetLeft(2 * margin + f->GetWidth());
	tt->SetWidth(GetWidth() - 3 * margin - f->GetWidth());
	tt->SetHeight(GetHeight() - 5 * margin - t->GetHeight() - quitButton->GetHeight() - restartButton->GetHeight());
	tt->SetBottom(margin);
	tt->SetPadding(10);
	Add(tt);

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

	NextGeneration.clear();
	// посоздавать червей сколько было указано в настройках
	for(Teams::const_iterator team = teams.begin(); team != teams.end(); ++team)
	{
		for(size_t i = 0; i < team->Count; ++i)
		{
			AddWorm(team->ID, Config::StartEnergy, TPosition(1, GetFreeCell()), SharedRenderer(new Util::Renderer(team->color, app, this)));
		}
	}
	CurrentGeneration = NextGeneration;
}

void Battle::Render()
{
	background->Draw(app, GetCenter());

	ElementSet::Render();
}

double Battle::GetTime() const
{
	return timer.GetTime();
}

SimplePoint Battle::GetFreeCell() const
{
	typedef std::vector<SimplePoint> Points;
	Points candidates;
	candidates.reserve(Field.Width * Field.Height);

	for(int x = 0; x < Field.Width; ++x)
		for(int y = 0; y < Field.Height; ++y)
			if(Field.Get(x, y) == CellEmpty)
				candidates.push_back(SimplePoint(x, y));

	if(candidates.empty())
	{
		throw std::overflow_error("Field overflow");
	}
	else
	{
		return candidates[app->Rand(candidates.size())];
	}
}

SharedRenderer Battle::GetRenderer(const Color &color)
{
	return Util::GenerateWormRenderer(color, app, this);
}

void Battle::Main()
{
	// make food
	while(foodMade < timer.GetTime() * Config::FoodPerSecond)
	{
		++foodMade;
		try
		{
			const SimplePoint free = GetFreeCell();

			Field.Set(free.X, free.Y, CellFood);
		}
		catch(std::overflow_error& )
		{
		}
	}

	NextGeneration.clear();
	NextGeneration.reserve(CurrentGeneration.size());

	// do worm logic
	for(WormCollection::const_iterator it = CurrentGeneration.begin(); it != CurrentGeneration.end(); ++it)
	{
		(*it)->Tick();
	}
	for(WormCollection::const_iterator it = CurrentGeneration.begin(); it != CurrentGeneration.end(); ++it)
	{
		if(!(*it)->Dead())
		{
			NextGeneration.push_back(*it);
		}
	}

	CurrentGeneration = NextGeneration;
	NextGeneration.clear();

	// вызвать Main вложенным объектам
	ElementSet::Main();
}

SharedSomeWorm Battle::AddWorm(const size_t classID, const double initialEnergy, const TPosition &initialPosition, const SharedRenderer &renderer)
{
	const SharedSomeWorm worm = registrator.Create(classID);

	++lastWormID;
	worm->Initialize(app, this, lastWormID, classID, initialEnergy,	initialPosition, GetTime(), renderer);

	NextGeneration.push_back(worm);

	return worm;
}

void Battle::MakeFood(const int X, const int Y, const int r)
{
	for(int x = X - r; x <= X + r; ++x)
		for(int y = Y - r; y <= Y + r; ++y)
			if(Field.Get(x, y) == CellEmpty && sqr(X - x) + sqr(Y - y) <= sqr(r))
			{
				Field.Set(x, y, CellFood);
			}
}

void Battle::Pause()
{
	timer.Pause();
}

void Battle::Resume()
{
	timer.Resume();
}
