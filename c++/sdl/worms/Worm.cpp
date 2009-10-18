#include "IWorm.h"
#include "Worm.h"
#include "WormsApplication.h"
#include "WormLogic.h"
#include "Config.h"
#include "SDLException.h"

void Worm::Draw() const
{
	int i = 0;
	for(TPosition::const_iterator it = position.begin(); it != position.end(); ++it, ++i)
		app->DrawWormCell(*it, this, i);
}

void Worm::ConsumeTime(const double dt)
{
	time += dt;
}

void Worm::Tick()
{
	if(Dead())
		return;
	// также возможно стоит сбрасывать излишки времени в конце функции
	// кроме того нужно уменьшать хп со временем
	CheckLength(); // подогнать длину под энергию
	// размножение (деление) при превышении некоторой пороговой величины энергии, смерть при понижении энергии до пороговой величины
	// возможно стоит сделать while вместо if, если fps маленький (<10), но там может начатьс€ друга€ печаль
	if(GetTime() < app->GetTime())
	{
		// ещЄ есть врем€!
		WormLogic decision = Run();
		if(decision != Stay)
		{
			ConsumeTime(Config::MovementTime);
			Go(decision);
		}
	}
}

void Worm::Go(const WormLogic direction)
{
	throw new NotImplementedException();
}

void Worm::EraseOnMap() const
{
	for(TPosition::const_iterator it = position.begin(); it != position.end(); ++it)
		app->Map.Set(it->X, it->Y, CellEmpty);
}

void Worm::UpdateMap() const
{
	for(TPosition::const_iterator it = position.begin(); it != position.end(); ++it)
		app->Map.Set(it->X, it->Y, CellWorm);
}

void Worm::EraseOnScreen() const
{
	for(TPosition::const_iterator it = position.begin(); it != position.end(); ++it)
		app->DrawCell(*it, CellEmpty);
}

void Worm::AntiGrow()
{
	if(position.size() == 0)
	{
		throw new std::out_of_range("My length is 0, can't AntiGrow()");
	}
	else
	{
		// удал€ем последнюю €чейку
		const SimplePoint last = position.back();
		position.pop_back();

		// если в этой клетке не было других €чеек черв€, то стираем эту клетку
		for(TPosition::const_iterator it = position.begin(); it != position.end(); ++it)
			if(*it == last)
				return;

		app->DrawCell(last, CellEmpty);
	}
}

void Worm::CheckLength()
{
	unsigned int need = static_cast<unsigned int>(floor(Energy() / Config::WormEnergyPerCell));

	while(position.size() < need)
		Grow();

	while(position.size() > need)
		AntiGrow();
}

void Worm::Die()
{
	EraseOnMap();
	EraseOnScreen();
	dead = true;
}

void Worm::Grow()
{
	position.push_back(position.back());
}

bool Worm::Dead()
{
	return dead;
}
