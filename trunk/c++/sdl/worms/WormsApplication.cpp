#include <iostream>
#include "WormsApplication.h"
#include "Vector.h"
#include <ctime>
#include "ISomeWorm.h"
#include "utils.h"

const Color WormsApplication::EmptyColor = Palette::Black;
const Color WormsApplication::WallColor = Palette::Gray;
const Color WormsApplication::FoodColor = Palette::Red + Palette::Green; // ����������

WormsApplication::WormsApplication() : Map(ScreenHeight, ScreenWidth), nextWormID(0)
{
	lasttime = time(NULL);

	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);

	SDL_WM_SetCaption("Worms", "");

	const unsigned int ncolors = 5;
	Color wcolors[ncolors] = { Palette::Green, Palette::Blue, Palette::Gray, Palette::Red, Palette::Yellow };
	// ������ �� ������ ���������� ������� ����� � ��������� ��������, ���� ��� ������ ��� \\todo: ����� �������, � �� �� ������
	// ����������� ��� � InitialRender
	for(unsigned int i = 0; i < registrator.Count(); ++i)
	{
		std::cout<<"Creating "<<registrator.ClassName(i)<<" instance."<<std::endl;
		
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
	
	// ������������ ���������� worms �� ��������� ���������
	// ��������� �� tmp
	// ����� �� ���� ��������� ��������� ������� ���, ������� �� ��������
	// ����� ������ ����� ������, ��� ������ ����� �������� ����� ��������/���������� ����� �����, � � �� ��� ���� ������ �������� 
	// ����� ��������� �������������� ������ �����
	// ������ �� ������� �� ������� ������, �.�. ������ ������ �� ����� ������������ �������
	// � ����������� ������������� ����� � worms (AddWorm()), ��� ��� � ��� ��������� � ���������� �� �����
	SomeWorms tmp = worms;
	worms.clear();

	for(SomeWorms::const_iterator it = tmp.begin(); it != tmp.end(); ++it)
	{
		(*it)->Tick();

		if((*it)->Dead())
		{
			// ���� ����� �����, ������� ���
			delete *it;
		}
		else
		{
			// ���, ��������� � ������ �����
			worms.push_back(*it);
		}
	}
	
	// ������ � worms ���������� ������ ����� �����

	Unlock();
	Flip();

	// ���������� ������������������ ��� � �������
	if(lasttime != time(NULL))
	{
		lasttime = time(NULL);
		std::cout<<"Time: "<<GetTime()<<"; FPS = "<<FPS()<<", dt min/avg/max = "<<dtMin()<<"/"<<dtAvg()<<"/"<<dtMax()<<" ms."<<std::endl;
	}
}

void WormsApplication::Render()
{
	// ��� ������ ���, �.�. �������� �� ���������� �� ������ ����� ������, � �� ���� �������� ������ � Main() ��������������� ���������
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

// �������� index ����� �������������� ���� �� ����� � ������� �������� ������ ����� ������ ������/��������� ��� ��������� ����
void WormsApplication::DrawWormCell(const SimplePoint &position, const ISomeWorm *worm, const int index) const
{
	DrawCell(position, worm->GetColor());
}

void WormsApplication::DrawCell(const SimplePoint &position, const Color &color) const
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
	for(int x = 0; x < Map.Width; ++x)
		for(int y = 0; y < Map.Height; ++y)
		{
			CellType cell = Map.Get(x, y);
			if(cell != CellWorm)
				DrawCell(SimplePoint(x, y), Map.Get(x, y));
		}

	for(unsigned int i = 0; i < worms.size(); ++i)
		worms[i]->Draw();

	Unlock();
	Flip();
}

ISomeWorm* WormsApplication::AddWorm(const int ClassID, const double energy, const TPosition& position, const Color& color)
{
	ISomeWorm* worm = registrator.Create(ClassID);
	worm->Initialize(this, nextWormID, ClassID, energy, position, GetTime(), color);
	++nextWormID;
	worms.push_back(worm);
	return worm;
}