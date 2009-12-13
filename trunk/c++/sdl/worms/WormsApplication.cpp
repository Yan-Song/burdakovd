#include <ctime>
#include <iostream>
#include <Color.h>
#include <Utils.h>
#include <Vector.h>
#include "ISomeWorm.h"
#include "IWorm.h"
#include "MainMenu.h"
#include "WormsApplication.h"

WormsApplication::WormsApplication() : CurrentState(new MainMenu()), printStatsTimer()
{
	InitializeSDL(ScreenHeight, ScreenWidth, ColorDepth, SDLflags);
	SetFPSCap(20);
	printStatsTimer.Start();

	SetCaption("Worms");
}

void WormsApplication::ProcessEvent(const SDL_Event& Event)
{
	CurrentState->ProcessEvent(Event);
}

void WormsApplication::Main()
{
    CurrentState->Main();

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
	CurrentState->Render();
}
