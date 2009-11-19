#include <sdlapplication/Color.h>
#include <sdlapplication/SDLApplication.h>
#include "IntersectionResult.h"
#include "Ray.h"
#include "Scene.h"

void RT::Scene::DrawBuffer(SDLApplication* const app, const bool rectangles, const unsigned int Quality)
{
	const unsigned int w = static_cast<unsigned int>(app->Screen->w);
	const unsigned int h = static_cast<unsigned int>(app->Screen->h);

	app->ClearScreen();

	// если Quality == 1 то прямоугольники вырождаются в точки
	if(rectangles && Quality > 1)
	{
		ColorContainer::const_iterator buffer_iterator = buffer.begin();

		for(unsigned int y = 0; y < h; y += Quality)
			for(unsigned int x = 0; x < w; x += Quality)
			{
				const int baseX = static_cast<int>(x) - static_cast<int>(Quality / 2);
				const int baseY = static_cast<int>(y) - static_cast<int>(Quality / 2);

				const int baseX2 = static_cast<int>(x + Quality / 2);
				const int baseY2 = static_cast<int>(y + Quality / 2);

				app->FillRectangle(ScreenPointByCoords(baseX, baseY), \
					ScreenPointByCoords(baseX2, baseY2), *buffer_iterator);

				++buffer_iterator;
			}

		assert(buffer_iterator == buffer.end());
	}
	else
	{
		app->Lock();

		ColorContainer::const_iterator buffer_iterator = buffer.begin();

		for(unsigned int y = 0; y < h; y += Quality)
			for(unsigned int x = 0; x < w; x += Quality)
			{
				app->RawDrawPixel(static_cast<int>(x), static_cast<int>(y), *buffer_iterator);
				++buffer_iterator;
			}

		assert(buffer_iterator == buffer.end());

		app->Unlock();
	}
	app->Flip();
}

bool RT::Scene::Render(SDLApplication *const app, const RT::Scene::SharedCallback &callback, const unsigned int Quality, const bool rectangles)
{	
	const size_t n = static_cast<size_t>(app->Screen->h * app->Screen->w);
	const size_t qh = (static_cast<size_t>(app->Screen->h) + Quality - 1) / Quality;
	const size_t qw = (static_cast<size_t>(app->Screen->w) + Quality - 1) / Quality;
	const size_t qn = qh * qw;

	// по идее реальное выделение памяти будет происходить только в первый раз
	// резервируем памяти для максимального качества
	buffer.reserve(n);

	// реально используем для текущего
	buffer.clear();
	buffer.resize(qn, Palette::Black);

	const unsigned int updateInterval = std::max<unsigned int>(qn / 100, 100);

	ColorContainer::iterator buffer_iterator = buffer.begin();

	for(unsigned int y = 0, i = 0; y < static_cast<unsigned int>(app->Screen->h); y += Quality)
	{
		for(unsigned int x = 0; x < static_cast<unsigned int>(app->Screen->w); x += Quality, ++i)
		{
			const RT::Ray ray(Vector3DByCoords(x, y, 0) - SpectatorPosition, SpectatorPosition);
			
			if(RT::CompoundObject::PossibleIntersection(ray))
			{
				const RT::MaybeIntersection result = RT::CompoundObject::FindIntersection(ray);

				if(result.Exists)
				{
					const RT::SharedTracer tracer = static_cast<RT::Intersection>(result).Tracer;

					*buffer_iterator = tracer->Trace(this);

					// проверяем что не получился отрицательный цвет
					assert(buffer_iterator->R >= 0 && buffer_iterator->G >= 0 && buffer_iterator->B >= 0);
				}
			}

			++buffer_iterator;
			
			if(i % updateInterval == 0)
			{
				const unsigned int percent = 90 *
					static_cast<unsigned int>(buffer_iterator - buffer.begin()) / qn;

				if(callback->call(percent))
				{
					return false;
				}
			}
		}
	}
	assert(buffer_iterator == buffer.end());


	// тут можно делать tonemapping
	// найти максимум
	double mx = 0;
	for(ColorContainer::const_iterator it = buffer.begin(); it != buffer.end(); ++it)
	{
		mx = std::max(mx, std::max(it->R, std::max(it->G, it->B)));
	}
	// нормирую цвет
	if(mx != 0)
	{
		const double n = 255.0 / mx;
		for(ColorContainer::iterator it = buffer.begin(); it != buffer.end(); ++it)
		{
			*it = *it * n;
		}
	}


	if(callback->call(95))
		return false;

	// остался последний шаг, перенести всё это на экран
	
	DrawBuffer(app, rectangles, Quality);

	callback->call(100);

	return true;
}

RealColor RT::Scene::CalculateLightness(const Point3D &point, const RT::NormalizedVector3D &n) const
{
	const double epsilon = 1e-9; // сколько брать???

	RealColor sum(ambient);

	for(LightContainer::const_iterator it = lights.begin(); it != lights.end(); ++it)
	{
		const double cosphi = static_cast<Vector3D>(n) * ((*it)->Position() - point) / point.Distance((*it)->Position());

		if(cosphi > 0)
		{
			const double QDistance = point.QDistance((*it)->Position());
			// источник света с нужной стороны
			// испускаем луч из источника света в направлении нужной точки,
			// если он ни с чем не пересечется по пути, то точка освещена этим источником

			RT::Ray ray(point - (*it)->Position(), (*it)->Position());

			RT::MaybeIntersection result = CompoundObject::FindIntersection(ray);

			if(result.Exists)
			{
				RT::Intersection intersection(result);

				if((*it)->Position().QDistance(intersection.Point) < QDistance * (1 - epsilon))
				{
					// свет заслонён
					continue;
				}
			}

			// свет не заслонён
			sum += (*it)->Color() * cosphi / QDistance;
		}
	}

	return sum;
}
