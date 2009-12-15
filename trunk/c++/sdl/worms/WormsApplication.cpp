#include <ctime>
#include <iostream>
#include <SDL_ttf.h>
#include <Color.h>
#include <Font.h>
#include <Utils.h>
#include <Vector.h>
#include "ISomeWorm.h"
#include "IWorm.h"
#include "MainMenu.h"
#include "WormsApplication.h"

WormsApplication::WormsApplication() : Engine(), printStatsTimer()
{
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);

	SetFPSCap(20);

	printStatsTimer.Start();

	SetCaption("Worms");

	SetState(SharedState(new MainMenu(this)));
}

void WormsApplication::ProcessEvent(const SDL_Event& Event)
{
	GetCurrentState()->ProcessEvent(Event);
}

void WormsApplication::Main()
{
    GetCurrentState()->Main();

	ChangeState();

	// статистика производительности раз в секунду
	if(printStatsTimer.GetTime() >= 1.0)
	{
		printStatsTimer.Start();
		std::cout << "Time: " << GetTime() <<
			"; FPS = " << FPS() << ", dt min/avg/max = " << dtMin() << "/" << dtAvg() << "/" << dtMax() << " ms." << std::endl;
	}
}

void WormsApplication::Render()
{
	GetCurrentState()->Render();
	Flip();
}

WormsApplication::~WormsApplication()
{

}
