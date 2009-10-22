#include "Manual.h"
#include "SDL.h"
#include "WormLogic.h"
#include <iostream>
#include "Vector.h"

unsigned int Manual::LeaderID = 2<<31;
SimplePoint Manual::LeaderPosition = SimplePoint(0,0);
double Manual::LastLeaderPresenceTime = 0;

WormLogic Manual::Run()
{
	// ������������ ����������, ���� ������ �� ���� � ������� ����� �������, ������� �� ����
	if(GetGlobalTime() - LastLeaderPresenceTime > 1)
	{
		InitiateElections();
		std::cout<<"Initiate elections ["<<GetID()<<"]"<<std::endl;
	}

	// ���� ��� ID ������ ��� � ������, �� ����������� ������
	if(GetID() < LeaderID)
		LeaderID = GetID();

	if(GetID() == LeaderID)
	{
		// � �����, �������������� ������ ������� �� �����������
		LastLeaderPresenceTime = GetGlobalTime();
		LeaderPosition = Position().front();
		
		if(isPressed(SDLK_RIGHT))
			return GoRight;
		else if(isPressed(SDLK_LEFT))
			return GoLeft;
		else if(isPressed(SDLK_UP))
			return GoUp;
		else if(isPressed(SDLK_DOWN))
			return GoDown; 
	}
	else
	{
		// �������������� ������ - ��������� �� �������
		SimplePoint head = Position().front();
		double distance = Vector2DByCoords(head.X, head.Y).Distance(Vector2DByCoords(LeaderPosition.X, LeaderPosition.Y));

		if(distance > 50)	
		{
			int dx = sgn(LeaderPosition.X - head.X);
			int dy = sgn(LeaderPosition.Y - head.Y);
			SimplePoint pdx = head; pdx.X += dx;
			SimplePoint pdy = head; pdy.Y += dy;
			int deltax = abs(LeaderPosition.X - head.X);
			int deltay =  abs(LeaderPosition.Y - head.Y);

			if(Rand(deltax + deltay) < deltax)
			{
				CellType cdx = Look(pdx.X, pdx.Y);

				if(cdx == CellEmpty || cdx == CellFood)
					return dx == 1 ? GoRight : GoLeft;
				else
					return dy == 1 ? GoUp : GoDown;
			}
			else
			{
				CellType cdy = Look(pdy.X, pdy.Y);

				if(cdy == CellEmpty || cdy == CellFood)
					return dy == 1 ? GoUp : GoDown;
				else
					return dx == 1 ? GoRight : GoLeft;
			}
		}
	}
	return FindFood();
}

void Manual::InitiateElections()
{
	// ��������� ���� ����������� �� ���� ������, ���� � ����-�� ID ������ - �������� LeaderID
	LeaderID = GetID();
	LastLeaderPresenceTime = GetGlobalTime();
	
}

WormLogic Manual::FindFood()
{
	SimplePoint head = Position().front();

	if(Look(head.X + 1, head.Y) == CellFood)
		return GoRight;
	if(Look(head.X - 1, head.Y) == CellFood)
		return GoLeft;
	if(Look(head.X, head.Y + 1) == CellFood)
		return GoUp;
	if(Look(head.X, head.Y - 1) == CellFood)
		return GoDown;

	return static_cast<WormLogic>(Rand(1, 4));
}