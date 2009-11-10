#include "Scene.h"
#include "sdlapplication/SDLApplication.h"
#include <vector>

bool RT::Scene::Render(SDLApplication *const app, const RT::Scene::SharedCallback &callback, const int Quality)
{	
	typedef std::vector<RealColor> ColorContainer;

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
	
	const int w = app->Screen->w;
	const int h = app->Screen->h;

	index = 0;

	app->ClearScreen();
	app->Lock();

	for(int y = 0; y < h; y += Quality)
		for(int x = 0; x < w; x += Quality)
		{
			app->RawDrawPixel(x, y, buffer[index]);
			++index;
		}
	assert(index == qn);

	app->Unlock();
	app->Flip();

	callback->call(100);

	return true;
}
