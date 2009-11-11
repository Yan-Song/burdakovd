#include "Scene.h"
#include "sdlapplication/SDLApplication.h"
#include "sdlapplication/Color.h"

void RT::Scene::DrawBuffer(SDLApplication* const app, const bool rectangles, const int Quality)
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
		ColorContainer::const_iterator buffer_iterator = buffer.begin();

		for(int y = 0; y < h; y += Quality)
			for(int x = 0; x < w; x += Quality)
			{
				const int baseX = x - Quality / 2;
				const int baseY = y - Quality / 2;

				app->FillRectangle(ScreenPointByCoords(baseX, baseY), ScreenPointByCoords(baseX + Quality, baseY + Quality), *buffer_iterator);

				++buffer_iterator;
			}

		assert(buffer_iterator == buffer.end());
	}
	else
	{
		app->Lock();

		ColorContainer::const_iterator buffer_iterator = buffer.begin();

		for(int y = 0; y < h; y += Quality)
			for(int x = 0; x < w; x += Quality)
			{
				app->RawDrawPixel(x, y, *buffer_iterator);
				++buffer_iterator;
			}

		assert(buffer_iterator == buffer.end());

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

	// по идее реальное выделение памяти будет происходить только в первый раз
	// резервируем памяти для максимального качества
	buffer.reserve(n);

	// реально используем для текущего
	buffer.clear();
	buffer.resize(qn, Palette::Black);

	const int updateInterval = std::max(qn / 100, 100);

	ColorContainer::iterator buffer_iterator = buffer.begin();

	for(int y = 0, i = 0; y < app->Screen->h; y += Quality)
	{
		for(int x = 0; x < app->Screen->w; x += Quality, ++i)
		{
			const RT::Ray ray(Vector3DByCoords(x, y, 0) - SpectatorPosition, SpectatorPosition);
			
			if(RT::CompoundObject::PossibleIntersection(ray))
			{
				const RT::MaybeIntersection result = RT::CompoundObject::FindIntersection(ray);

				if(result.Exists)
				{
					const RT::SharedTracer tracer = static_cast<RT::Intersection>(result).Tracer;

					*buffer_iterator = tracer->Trace();

					// проверяем что не получился отрицательный цвет
					assert(buffer_iterator->R >= 0 && buffer_iterator->G >= 0 && buffer_iterator->B >= 0);
				}
			}

			++buffer_iterator;
			
			if(i % updateInterval == 0)
			{
				const int percent = 100 * (buffer_iterator - buffer.begin()) / qn;

				if(callback->call(percent))
				{
					return false;
				}
			}
		}
	}
	assert(buffer_iterator == buffer.end());

	// тут можно делать tonemapping
	// ...

	if(callback->call(95))
		return false;

	// остался последний шаг, перенести всё это на экран
	
	DrawBuffer(app, rectangles, Quality);

	callback->call(100);

	return true;
}

