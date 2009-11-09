#include "Scene.h"
#include "sdlapplication/SDLApplication.h"

void RT::Scene::Render(SDLApplication *const app, const RT::Scene::SharedCallback &callback)
{
	app->ClearScreen();
	app->Lock();

	const int updateInterval = 1000;

	for(int y = 0; y < app->Screen->h; ++y)
	{
		for(int x = 0; x < app->Screen->w; ++x)
		{
			const RT::Ray ray(Vector3DByCoords(x, y, 0) - SpectatorPosition, SpectatorPosition);

			if(RT::CompoundObject::PossibleIntersection(ray))
			{
				const RT::MaybeIntersection result = RT::CompoundObject::FindIntersection(ray);

				if(result.Exists)
				{
					const RT::SharedTracer tracer = static_cast<RT::Intersection>(result).Tracer;

					app->RawDrawPixel(x, y, tracer->Trace());
				}
			}
		}

		const int percent = 100 * (y + 1) / app->Screen->h;

		if(callback->call(percent))
		{
			app->Unlock();
			return;
		}
	}

	app->Unlock();
	app->Flip();
}
