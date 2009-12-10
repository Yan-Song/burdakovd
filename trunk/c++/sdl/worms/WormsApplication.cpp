#include <ctime>
#include <iostream>
#include <Color.h>
#include <Utils.h>
#include <Vector.h>
#include "ISomeWorm.h"
#include "IWorm.h"
#include "WormsApplication.h"

const Color WormsApplication::EmptyColor = Palette::Black;
const Color WormsApplication::WallColor = Palette::Gray;
const Color WormsApplication::FoodColor = (Palette::Red + Palette::Green) / 5; // коричневый

const int WormsApplication::FieldWidth = 800;
const int WormsApplication::FieldHeight = 600;


WormsApplication::WormsApplication() : Map(FieldHeight, FieldWidth), printStatsTimer(), nextWormID(0)
{
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SetFPSCap(20);
	printStatsTimer.Start();

	SetCaption("Worms");

	const unsigned int ncolors = 5;
	Color wcolors[ncolors] = { Palette::Green, Palette::Blue, Palette::Gray, Palette::Red, Palette::Yellow };
	// создаём по 10 экземпляров каждого червя в случайных позициях, пока что только так \\todo: выбор условий, и не по одному
	// прорисуются они в InitialRender
	for(unsigned int i = 0; i < registrator.Count(); ++i)
	{
		std::cout<<"Creating "<<registrator.ClassName(i)<<" instances."<<std::endl;
		
		for(int j = 0; j < 100; ++j)
		{
			int xx, yy;
			do
			{
				xx = Rand(FieldWidth);
				yy = Rand(FieldHeight);
			}
			while(Map.Get(xx, yy) != CellEmpty);
			
			TPosition _position;
			_position.push_back(SimplePoint(xx, yy));

			AddWorm(i, 100, _position, wcolors[i % ncolors])->UpdateMap();
		}
	}
}

void WormsApplication::ProcessEvent(SDL_Event Event)
{
	if(Event.type == SDL_KEYDOWN)
	{
		SDLKey sym = Event.key.keysym.sym;

		if(sym == SDLK_ESCAPE || sym == SDLK_q)
			Stop();

		if(sym == SDLK_f)
		{
			Lock();
			MakeFood();
			Unlock();
			Flip();
		}
	}
}

void WormsApplication::Main()
{
    Lock();
	
	// перекидываем содержимое worms во временный контейнер
	// итерируем по tmp
	// затем по мере обработки переносим обратно тех, которые не погибнут
	// такие фокусы делаю потому, что внутри цикла возможно будут погибать/появляться новые черви, а я хз как себя поведёт итератор 
	// когда контейнер модифицируется внутри цикла
	// сейчас же удалять не придётся ничего, т.к. мёртвые просто не будут переноситься обратно
	// а добавляться новорожденные будут в worms (AddWorm()), так что и тут конфликта с итератором не будет
	SomeWorms tmp = worms;
	worms.clear();

	for(SomeWorms::const_iterator it = tmp.begin(); it != tmp.end(); ++it)
	{
		(*it)->Tick();

		if((*it)->Dead())
		{
			// этот червь мертв, удаляем его
			delete *it;
		}
		else
		{
			// жив, переносим в список живых
			worms.push_back(*it);
		}
	}
	
	// теперь в worms содержатся только живые черви

	Unlock();
	Flip();

	// статистика производительности раз в секунду
	if(printStatsTimer.GetTime() >= 1.0)
	{
		printStatsTimer.Start();
		std::cout << "Time: " << GetTime() << "; total worms: " << worms.size() << 
			"; FPS = " << FPS() << ", dt min/avg/max = " << dtMin() << "/" << dtAvg() << "/" << dtMax() << " ms." << std::endl;
	}
}

void WormsApplication::Render()
{
	// тут ничего нет, т.к. картинка не рендерится на каждом кадре заново, а по мере движения червей в Main() прорисовываются изменения
}

void WormsApplication::DrawCell(const SimplePoint& position, const CellType type)
{
	if(type == CellEmpty)
		DrawCell(position, EmptyColor);
	else if(type == CellFood)
		DrawCell(position, FoodColor);
	else if(type == CellWall)
		DrawCell(position, WallColor);
	else
		throw new std::invalid_argument("DrawCell(const pii& position, const CellType type) const");
}

// возможно index будет использоваться если мы будем к примеру рисовать голову червя другим цветом/текстурой чем остальное тело
void WormsApplication::DrawWormCell(const SimplePoint &position, const ISomeWorm *worm, const int index)
{
	DrawCell(position, worm->GetColor());
}

void WormsApplication::DrawCell(const SimplePoint &position, const Color &color)
{
	/*FillRectangle(
		ScreenPointByCoords(position.X * 10, ScreenHeight - position.Y * 10 - 10),
		ScreenPointByCoords(position.X * 10 + 10, ScreenHeight - position.Y * 10),
		color);*/
	DrawPixel(position.X, ScreenHeight - position.Y, color);
}

WormsApplication::~WormsApplication()
{
	for(unsigned int i = 0; i < worms.size(); ++i)
	{
		delete worms[i];
	}
}

void WormsApplication::InitialRender()
{
	Lock();
	
	DrawMap();
	// ещё тут будет прорисовка чего-то кроме карты, что не меняется на каждом кадре, рамки к примеру

	Unlock();
	Flip();
}

void WormsApplication::DrawMap()
{
	for(int x = 0; x < Map.Width; ++x)
		for(int y = 0; y < Map.Height; ++y)
		{
			CellType cell = Map.Get(x, y);
			if(cell != CellWorm)
				DrawCell(SimplePoint(x, y), Map.Get(x, y));
		}

	for(unsigned int i = 0; i < worms.size(); ++i)
		worms[i]->Draw();
}

ISomeWorm* WormsApplication::AddWorm(const int ClassID, const double energy, const TPosition& position, const Color& color)
{
	ISomeWorm* worm = registrator.Create(ClassID);
	worm->Initialize(this, nextWormID, ClassID, energy, position, GetTime(), color);
	++nextWormID;
	worms.push_back(worm);
	return worm;
}

void WormsApplication::MakeFood()
{
	int xx = Rand(FieldWidth), yy = Rand(FieldHeight);
	// тут какая-то фигня с компилятором, пока что приходится писать int()
	int sz = min(int(FieldHeight), int(FieldWidth));
	int r = Rand(sz / 20, sz / 10);
	MakeFood(xx, yy, r);
}

void WormsApplication::MakeFood(const int xx, const int yy, const int r)
{
	Point2D center = Vector2DByCoords(xx, yy);

	for(int x = xx - r; x < xx + r; ++x)
		for(int y = yy - r; y < yy + r; ++y)
			if(center.Distance(Vector2DByCoords(x, y)) < r)
				if(Map.Get(x, y) == CellEmpty)
				{
					Map.Set(x, y, CellFood);
					DrawCell(SimplePoint(x, y), CellFood);
				}
}
