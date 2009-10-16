#include <iostream>
#include "WormsApplication.h"
#include "Vector.h"
#include <ctime>

const Color WormsApplication::EmptyColor = Palette::Black;
const Color WormsApplication::WallColor = Palette::Gray;
const Color WormsApplication::FoodColor = Palette::Red + Palette::Green; // коричневый

WormsApplication::WormsApplication()
{
	lasttime = time(NULL);
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SDL_WM_SetCaption("Worms", "");

	// создаЄм по одному экземпл€ру каждого черв€ в случайных позици€х, пока что только так \\todo
	for(unsigned int i = 0; i < registrator.Count(); ++i)
	{
		std::cout<<"Creating "<<registrator.ClassName(i)<<std::endl;
		int xx = Rand(ScreenWidth), yy = Rand(ScreenHeight);
		vector<pii> _position;
		for(int j = 0; j < 10; ++j)
			_position.push_back(pii(xx, yy));
		ISomeWorm* _ = registrator.Create(i); // удалим в деструкторе
		_->Initialize(this, worms.size(), i, 100, _position, GetTime(), Palette::Red);
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
	SDL_Flip(Screen);

	if(lasttime != time(NULL))
	{
		lasttime = time(NULL);
		std::cout<<"Time: "<<GetTime()<<"; FPS = "<<FPS()<<", dt min/avg/max = "<<dtMin()<<"/"<<dtAvg()<<"/"<<dtMax()<<" ms."<<std::endl;
	}
}

void WormsApplication::Render()
{

}

void WormsApplication::DrawCell(const pii& position, const CellType type) const
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

void WormsApplication::DrawWormCell(const pii &position, const ISomeWorm *worm) const
{
	DrawCell(position, worm->GetColor());
}

void WormsApplication::DrawCell(const pii &position, const Color &color) const
{
	DrawPixel(position.first, position.second, color);
}

WormsApplication::~WormsApplication()
{
	std::cout<<"Deleting worms..."<<std::endl;
	for(unsigned int i = 0; i < worms.size(); ++i)
	{
		std::cout<<"  deleting "<<registrator.ClassName(worms[i]->GetClassID())<<", ID="<<worms[i]->GetID()<<std::endl;
		delete worms[i];
	}
}
