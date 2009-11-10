#include "Scene.h"
#include "sdlapplication/SDLApplication.h"
#include <vector>

typedef std::vector<RealColor> ColorContainer;

void DrawBuffer(SDLApplication* const app, const bool rectangles, const int Quality, const ColorContainer& buffer)
{
	const int n = app->Screen->h * app->Screen->w;
	const int qh = (app->Screen->h + Quality - 1) / Quality;
	const int qw = (app->Screen->w + Quality - 1) / Quality;
	const int qn = qh * qw;
	const int w = app->Screen->w;
	const int h = app->Screen->h;

	app->ClearScreen();

	// если Quality == 1 то прямоугольники вырождаются в точки
	if(rectangles && Quality > 1)
	{
		int index = 0;
		for(int y = 0; y < h; y += Quality)
			for(int x = 0; x < w; x += Quality)
			{
				const int baseX = x - Quality / 2;
				const int baseY = y - Quality / 2;

				app->FillRectangle(ScreenPointByCoords(baseX, baseY), ScreenPointByCoords(baseX + Quality, baseY + Quality), buffer[index]);

				++index;
			}
		assert(index == qn);
	}
	else
	{
		app->Lock();

		int index = 0;
		for(int y = 0; y < h; y += Quality)
			for(int x = 0; x < w; x += Quality)
			{
				app->RawDrawPixel(x, y, buffer[index]);
				++index;
			}
		assert(index == qn);

		app->Unlock();
	}
	app->Flip();
}

bool RT::Scene::Render(SDLApplication *const app, const RT::Scene::SharedCallback &callback, const int Quality, 
					   const bool rectangles)
{	
	const int n = app->Screen->h * app->Screen->w;
	const int qh = (app->Screen->h + Quality - 1) / Quality;
	const int qw = (app->Screen->w + Quality - 1) / Quality;
	const int qn = qh * qw;

	ColorContainer buffer(qn, Palette::Black);

	const int updateInterval = 1000;

	int index = 0;
	for(int y = 0; y < app->Screen->h; y += Quality)
	{
		for(int x = 0; x < app->Screen->w; x += Quality)
		{
			const RT::Ray ray(Vector3DByCoords(x, y, 0) - SpectatorPosition, SpectatorPosition);

			if(RT::CompoundObject::PossibleIntersection(ray))
			{
				const RT::MaybeIntersection result = RT::CompoundObject::FindIntersection(ray);

				if(result.Exists)
				{
					const RT::SharedTracer tracer = static_cast<RT::Intersection>(result).Tracer;

					buffer[index] = tracer->Trace();
				}
			}
			++index;

			if(index % updateInterval == 0)
			{
				const int percent = 99 * (y + 1) / app->Screen->h;

				if(callback->call(percent))
				{
					return false;
				}
			}
		}
	}
	assert(index == qn);

	// остался последний процент, перенести всё это на экран
	
	DrawBuffer(app, rectangles, Quality, buffer);

	callback->call(100);

	return true;
}

