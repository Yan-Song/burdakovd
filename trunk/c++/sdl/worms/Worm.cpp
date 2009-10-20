#include "IWorm.h"
#include "Worm.h"
#include "WormsApplication.h"
#include "WormLogic.h"
#include "Config.h"
#include "SDLException.h"
#include "SDL.h"

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
	UpdateEnergy();

	if(Dead())
		return;

	DoLogic();

	CheckLength();
}

void Worm::Go(const WormLogic direction)
{
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

	CellType target = app->Map.Get(head.X, head.Y);

	if(target == CellEmpty || target == CellFood)
	{
		// ���� ���� ����� ����
		
		// ���� ��� ���...
		if(target == CellFood)
			energy += Config::FoodEnergyPerCell;

		// ��������� ������
		position.push_front(head);
		
		// �������� ��� ������ � ������
		app->Map.Set(head.X, head.Y, CellWorm);
		app->DrawWormCell(head, this, 0);
		
		// ������������ �����
		CheckLength();
	}
	else
	{
		// ���� ���� ������, ���������
		position.push_front(position.front());
		
		// ������������ �����
		CheckLength();
	}
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
		// ������� ��������� ������
		const SimplePoint last = position.back();
		position.pop_back();

		// ���� � ���� ������ �� ���� ������ ����� �����, �� ������� ��� ������
		for(TPosition::const_iterator it = position.begin(); it != position.end(); ++it)
			if(last == *it)
				return;

		app->DrawCell(last, CellEmpty);
		app->Map.Set(last.X, last.Y, CellEmpty);
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

void Worm::UpdateEnergy()
{
	// 1) �������� �������
	double dt = app->GetTime() - lastUpdateEnergyTime;
	lastUpdateEnergyTime += dt;
	energy -= Config::EnergyLossPerSecond * dt;

	// 2) �� ���� �� �������?
	if(energy < Config::DeathEnergyLevel)
	{
		Die();
		return;
	}

	// 3) �� ���� �� ������� �����?
	if(energy > Config::ReplicateEnergyLevel)
	{
		unsigned int n = position.size();
		unsigned int n1 = n / 2;
		unsigned int n2 = n - n1;

		// ������� ��������
		TPosition::iterator middle = position.begin();
		for(unsigned int i = 0; i < n1; ++n1)
			++middle;

		// ������������ ������� �����
		TPosition pfirst(position.begin(), middle);
		TPosition psecond(middle, position.end());

		// ������� ������
		Die();

		// ������� �����
		ISomeWorm* first = app->AddWorm(GetClassID(), energy, pfirst, GetColor());
		first->UpdateMap();
		first->Draw();

		ISomeWorm* second = app->AddWorm(GetClassID(), energy, psecond, GetColor());
		second->UpdateMap();
		second->Draw();
	}
}

void Worm::DoLogic()
{
	// �������� ����� ������� while ������ if, ���� fps ��������� (<10), �� ��� ����� �������� ������ ������
	if(GetTime() < app->GetTime())
	{
		// ��� ���� �����!
		WormLogic decision = Run();
		if(decision != Stay)
		{
			ConsumeTime(Config::MovementTime);
			Go(decision);
		}
	}
	// ����� �������� ����� ���������� ������� ������� � ����� �������
	if(time < app->GetTime()) // !!
		time = app->GetTime();
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