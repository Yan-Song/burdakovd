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
	// ����� �������� ����� ���������� ������� ������� � ����� �������
	// ����� ���� ����� ��������� �� �� ��������
	CheckLength(); // ��������� ����� ��� �������
	// ����������� (�������) ��� ���������� ��������� ��������� �������� �������, ������ ��� ��������� ������� �� ��������� ��������
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
		// ������� ��������� ������
		const SimplePoint last = position.back();
		position.pop_back();

		// ���� � ���� ������ �� ���� ������ ����� �����, �� ������� ��� ������
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
