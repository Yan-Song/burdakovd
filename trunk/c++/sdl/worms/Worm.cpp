#include <algorithm>
#include <list>
#include <set>
#include <vector>
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

void Worm::Go(const WormLogic direction)
{
	assert(!Dead());

	// отрисовывать себя на экране больше не надо
	// кроме того проще будет и на карте не динамически менять себя
	// а стирать перед движением, и перерисовывать после

	SimplePoint head = position.front();

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

	const CellType target = BattleState->Field.Get(head.X, head.Y);

	if(target == CellEmpty || target == CellFood)
	{
		// если туда можно идти

		// если там еда...
		if(target == CellFood)
			energy += Config::FoodEnergyPerCell;

		// добавляем голову
		if(std::find(position.begin(), position.end(), head) != position.end())
			throw NotImplementedException();
		position.push_front(head);

		// занимаем эту ячейку
		BattleState->Field.Set(head.X, head.Y, CellWorm);

		
		// корректируем длину
		CheckLength();
		

		ConsumeTime(Config::MovementTime);
	}
	else
	{
		// туда идти нельзя
	}

	
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

// * инвариант карты
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

// * инвариант карты
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
	EraseOnMap();

	if(!position.empty())
	{
		BattleState->MakeFood(position.front().X, position.front().Y, Config::CorpseRadius);
	}

	dead = true;
}

bool Worm::Dead() const
{
	return dead;
}

// * инвариант карты
void Worm::UpdateEnergy()
{
	assert(!Dead());

	
	// 1) обновить энергию
	const double dt = GetGlobalTime() - lastUpdateEnergyTime;
	lastUpdateEnergyTime += dt;
	energy -= Config::EnergyLossPerSecond * dt;

	// 2) не пора ли умереть?
	if(energy <= Config::DeathEnergyLevel)
	{
		Die();
		return;
	}

	// 3) не пора ли завести детей?
	if(energy > Config::ReplicateEnergyLevel && position.size() >= 2)
	{
		const size_t n = position.size();
		const size_t n1 = n / 2;

		// находим середину
		TPosition::iterator middle = position.begin();
		for(size_t i = 0; i < n1; ++i)
			++middle;

		// рассчитываем позиции детей
		const TPosition pfirst(position.begin(), middle);
		TPosition psecond(middle, position.end());
		psecond.reverse();

		// тут уже два раза ВНЕЗАПНО появлялся баг, из-за которого нарушался Инвариант карты
		// так что код смерти и создания детей стоит редактировать осторожнее
		
		// фокус, укорачиваемся до размера второго сына
		// временно нарушаем инвариант карты, но к концу функции он восстановится
		EraseOnMap();
		position = psecond;
		UpdateMap();

		// создать первого сына
		BattleState->AddWorm(GetClassID(), energy / 2, pfirst, GetRenderer());

		// сдохнуть
		Die();

		// создать второго сына
		BattleState->AddWorm(GetClassID(), energy / 2, psecond, GetRenderer());
	}
	else
	{
		
	}
}

// * инвариант карты
void Worm::DoLogic()
{
	assert(!Dead());

	if(GetLocalTime() < GetGlobalTime())
	{
		// ещё есть время!
		const WormLogic decision = Run();
		if(decision != Stay)
		{
			Go(decision);
		}
	}

	// также возможно стоит сбрасывать излишки времени в конце функции
	if(time < GetGlobalTime())
	{
		time = GetGlobalTime();
	}

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
	const SimplePoint head = position.front();
	const int distance = abs(head.X - x) + abs(head.Y - y);
	ConsumeTime(Config::DiscoverTime * distance);

	return BattleState->Field.Get(x, y);
}

double Worm::GetGlobalTime() const
{
	return BattleState->GetTime();
}

void Worm::ModifyEnergy(const double delta)
{
	energy += delta;
}

SimplePoint Worm::Mouse() const
{
	return BattleState->MousePosition();
}
