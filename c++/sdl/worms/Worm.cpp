#include <list>
#include "Battle.h"
#include "Config.h"
#include "IWorm.h"
#include "SDLException.h"
#include "SDL.h"
#include "Worm.h"
#include "WormsApplication.h"
#include "WormLogic.h"

void Worm::ConsumeTime(const double dt)
{
	time += dt;
}

void Worm::Tick()
{
	assert(!Dead());

	UpdateEnergy();

	if(Dead())
		return;

	DoLogic();

	CheckLength();
}

void Worm::Go(const WormLogic )
{
	assert(!Dead());
	throw NotImplementedException();

	// отрисовывать себя на экране больше не надо
	// кроме того проще будет и на карте не динамически менять себя
	// а стирать перед движением, и перерисовывать после

	/*SimplePoint head = position.front();

	if(direction == GoDown)
		--head.Y;
	else if(direction == GoLeft)
		--head.X;
	else if(direction == GoRight)
		++head.X;
	else if(direction == GoUp)
		++head.Y;
	else
		throw new NotImplementedException();

	CellType target = app->Map.Get(head.X, head.Y);

	if(target == CellEmpty || target == CellFood)
	{
		// если туда можно идти

		// если там еда...
		if(target == CellFood)
			energy += Config::FoodEnergyPerCell;

		// добавляем голову
		position.push_front(head);

		// занимаем эту ячейку и рисуем
		app->Map.Set(head.X, head.Y, CellWorm);
		app->DrawWormCell(head, this, 0);

		// корректируем длину
		CheckLength();
	}
	else
	{
		// туда идти нельзя, сжимаемся
		position.push_front(position.front());

		// корректируем длину
		CheckLength();
	}*/
}

void Worm::EraseOnMap() const
{
	for(TPosition::const_iterator it = position.begin(); it != position.end(); ++it)
		BattleState->Field.Set(it->X, it->Y, CellEmpty);
}

void Worm::UpdateMap() const
{
	assert(!Dead());
	
	for(TPosition::const_iterator it = position.begin(); it != position.end(); ++it)
		BattleState->Field.Set(it->X, it->Y, CellWorm);
}

void Worm::CheckLength()
{
	assert(!Dead());

	size_t need = static_cast<size_t>(floor(Energy() / Config::WormEnergyPerCell));

	EraseOnMap();
	// пока червь длиннее чем надо - отрезаем ему хвост
	while(position.size() > need)
	{
		position.pop_back();
	}
	UpdateMap();

	// пока длина меньше чем надо, растём если возможно
	while(position.size() < need && Grow())
		;
}

bool Worm::Grow()
{
	assert(!Dead());
	assert(!position.empty());

	const SimplePoint tail = position.back();

	// места где может быть расположен хвост
	std::list<SimplePoint> candidates;
	
	candidates.push_back(SimplePoint(tail.X + 1, tail.Y));
	candidates.push_back(SimplePoint(tail.X - 1, tail.Y));
	candidates.push_back(SimplePoint(tail.X, tail.Y + 1));
	candidates.push_back(SimplePoint(tail.X, tail.Y - 1));

	// во второй тур проходят только пустые ячейки
	std::vector<SimplePoint> candidates2;
	for(std::list<SimplePoint>::const_iterator it = candidates.begin(); it != candidates.end(); ++it)
		if(BattleState->Field.Get(it->X, it->Y) == CellEmpty)
			candidates2.push_back(*it);

	// если вариантов нет - то возвращаем false, иначе выбираем случайную ячейку
	if(candidates2.empty())
	{
		return false;
	}
	else
	{
		const SimplePoint newtail = candidates2[app->Rand(candidates2.size())];

		BattleState->Field.Set(newtail.X, newtail.Y, CellWorm);

		position.push_back(newtail);

		return true;
	}
}

void Worm::Die()
{
	throw NotImplementedException();
	/*EraseOnMap();
	EraseOnScreen();

	if(!position.empty())
		app->MakeFood(position.front().X, position.front().Y, Config::CorpseRadius);

	dead = true;*/
}

bool Worm::Dead() const
{
	return dead;
}

void Worm::UpdateEnergy()
{
	assert(!Dead());

	throw NotImplementedException();
	/*// 1) обновить энергию
	double dt = app->GetTime() - lastUpdateEnergyTime;
	lastUpdateEnergyTime += dt;
	energy -= Config::EnergyLossPerSecond * dt;

	// 2) не пора ли умереть?
	if(energy < Config::DeathEnergyLevel)
	{
		Die();
		return;
	}

	// 3) не пора ли завести детей?
	if(energy > Config::ReplicateEnergyLevel)
	{
		unsigned int n = position.size();
		unsigned int n1 = n / 2;

		// находим середину
		TPosition::iterator middle = position.begin();
		for(unsigned int i = 0; i < n1; ++i)
			++middle;

		// рассчитываем позиции детей
		TPosition pfirst(position.begin(), middle);
		TPosition psecond(middle, position.end());

		// Умереть самому
		Die();

		// создать детей
		SharedSomeWorm first = app->AddWorm(GetClassID(), energy / 2, pfirst, GetColor());
		first->UpdateMap();
		first->Draw();

		SharedSomeWorm second = app->AddWorm(GetClassID(), energy / 2, psecond, GetColor());
		second->UpdateMap();
		second->Draw();
	}*/
}

void Worm::DoLogic()
{
	assert(!Dead());

	throw NotImplementedException();
	/*// возможно стоит сделать while вместо if, если fps маленький (<10), но там может начаться другая печаль
	if(GetLocalTime() < app->GetTime())
	{
		// ещё есть время!
		WormLogic decision = Run();
		if(decision != Stay)
		{
			ConsumeTime(Config::MovementTime);
			Go(decision);
		}
	}
	// также возможно стоит сбрасывать излишки времени в конце функции
	if(time < app->GetTime()) // !!
		time = app->GetTime();*/
}

bool Worm::isPressed(const SDLKey key) const
{
	return app->isPressed(key);
}

int Worm::Rand(const int x, const int y) const
{
	return app->Rand(x, y);
}

int Worm::Rand(const int x) const
{
	return app->Rand(x);
}

CellType Worm::Look(const int x, const int y)
{
	assert(position.size() > 0);
	SimplePoint head = position.front();
	const int distance = abs(head.X - x) + abs(head.Y - y);
	ConsumeTime(Config::DiscoverTime * distance);

	return BattleState->Field.Get(x, y);
}

double Worm::GetGlobalTime() const
{
	return app->GetTime();
}
