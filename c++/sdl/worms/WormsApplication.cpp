#include <iostream>
#include "WormsApplication.h"
#include "Vector.h"
#include <ctime>
#include "ISomeWorm.h"

const Color WormsApplication::EmptyColor = Palette::Black;
const Color WormsApplication::WallColor = Palette::Gray;
const Color WormsApplication::FoodColor = Palette::Red + Palette::Green; // коричневый

WormsApplication::WormsApplication() : Map(ScreenHeight, ScreenWidth)
{
	lasttime = time(NULL);
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Worms", "");

	// создаЄм по одному экземпл€ру каждого черв€ в случайных позици€х, пока что только так \\todo
	for(unsigned int i = 0; i < registrator.Count(); ++i)
	{
		std::cout<<"Creating "<<registrator.ClassName(i)<<std::endl;
		int xx = Rand(ScreenWidth), yy = Rand(ScreenHeight);
		TPosition _position;
		for(int j = 0; j < 10; ++j)
			_position.push_back(SimplePoint(xx, yy));
		ISomeWorm* _ = registrator.Create(i); // удалим в деструкторе
		_->Initialize(this, worms.size(), i, 100, _position, GetTime(), Palette::Red);
		_->UpdateMap();
		worms.push_back(_); 
	}
}

void WormsApplication::ProcessEvent(SDL_Event Event)
{
	if(Event.type == SDL_KEYDOWN)
	{
		SDLKey sym = Event.key.keysym.sym;

		if(sym == SDLK_ESCAPE || sym == SDLK_q)
			Stop();
	}
}

void WormsApplication::Main()
{
    Lock();
	
	Unlock();
	Flip();

	if(lasttime != time(NULL))
	{
		lasttime = time(NULL);
		std::cout<<"Time: "<<GetTime()<<"; FPS = "<<FPS()<<", dt min/avg/max = "<<dtMin()<<"/"<<dtAvg()<<"/"<<dtMax()<<" ms."<<std::endl;
	}
}

void WormsApplication::Render()
{

}

void WormsApplication::DrawCell(const SimplePoint& position, const CellType type) const
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

// возможно index будет использоватьс€ если мы будем к примеру рисовать голову черв€ другим цветом/текстурой чем остальное тело
void WormsApplication::DrawWormCell(const SimplePoint &position, const ISomeWorm *worm, const int index) const
{
	DrawCell(position, worm->GetColor());
}

void WormsApplication::DrawCell(const SimplePoint &position, const Color &color) const
{
	DrawPixel(position.X, position.Y, color);
}

WormsApplication::~WormsApplication()
{
	std::cout<<"Deleting worms..."<<std::endl;
	for(unsigned int i = 0; i < worms.size(); ++i)
	{
		delete worms[i];
	}
}

void WormsApplication::InitialRender()
{
	Lock();
	for(int x = 0; x < Map.Width; ++x)
		for(int y = 0; y < Map.Height; ++y)
		{
			CellType cell = Map.Get(x, y);
			if(cell != CellWorm)
				DrawCell(SimplePoint(x, y), Map.Get(x, y));
		}

	for(int i = 0; i < worms.size(); ++i)
		worms[i]->Draw();

	Unlock();
	Flip();
}