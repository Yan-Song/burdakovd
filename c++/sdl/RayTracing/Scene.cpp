#include <algorithm>
#include <sdlapplication/Color.h>
#include <sdlapplication/SDLApplication.h>
#include <sdlapplication/Vector.h>
#include "IntersectionResult.h"
#include "Ray.h"
#include "Scene.h"

void RT::Scene::DrawBuffer(SDLApplication* const app, const bool rectangles, const size_t Step)
{
	const unsigned int w = static_cast<unsigned int>(app->Screen->w);
	const unsigned int h = static_cast<unsigned int>(app->Screen->h);

	app->ClearScreen();

	// если Step == 1 то прямоугольники вырождаются в точки
	if(rectangles && Step > 1)
	{
		ColorContainer::const_iterator buffer_iterator = buffer.begin();

		for(size_t y = 0; y < h; y += Step)
			for(size_t x = 0; x < w; x += Step)
			{
				const int baseX = static_cast<int>(x);
				const int baseY = static_cast<int>(y);

				const int baseX2 = static_cast<int>(x + Step);
				const int baseY2 = static_cast<int>(y + Step);

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

		for(size_t y = 0; y < h; y += Step)
			for(size_t x = 0; x < w; x += Step)
			{
				app->RawDrawPixel(static_cast<int>(x), static_cast<int>(y), *buffer_iterator);
				++buffer_iterator;
			}

		assert(buffer_iterator == buffer.end());

		app->Unlock();
	}

	app->Flip();
}

bool RT::Scene::Render(SDLApplication *const app, const RT::Scene::SharedCallback &callback, \
		const size_t Step, const bool rectangles, const size_t extra)
{
	const size_t n = static_cast<size_t>(app->Screen->h * app->Screen->w);
	const size_t qh = (static_cast<size_t>(static_cast<unsigned int>(app->Screen->h)) + Step - 1) / Step;
	const size_t qw = (static_cast<size_t>(static_cast<unsigned int>(app->Screen->w)) + Step - 1) / Step;
	const size_t qn = qh * qw;

	// резервируем памяти для максимального качества
	buffer.reserve(n);

	// реально используем для текущего
	buffer.clear();
	buffer.resize(qn, Palette::Black);

	if(camera)
	{
		const size_t updateInterval = std::max<size_t>(qn / 100, 100);

		ColorContainer::iterator buffer_iterator = buffer.begin();

		for(size_t yt = 0, i = 0; yt < static_cast<size_t>(app->Screen->h); yt += Step)
		{
			for(size_t xl = 0; xl < static_cast<size_t>(app->Screen->w); xl += Step, ++i)
			{
				RealColor SummaryColor(Palette::Black);

				// разбиваем окрестность пикселя (x, y)..(x + 1, y + 1) на extra строк и столбцов
				// для каждой ячейки проводим луч и затем берём среднее
				for(size_t ex = 0; ex < extra; ++ex)
					for(size_t ey = 0; ey < extra; ++ey)
					{
						// находим центры каждой ячейки
						const double x = \
								static_cast<double>(xl) + \
								(static_cast<double>(ex) + 0.5) \
								/ static_cast<double>(extra) \
								* static_cast<double>(Step);

						const double y = \
								static_cast<double>(yt) + \
								(static_cast<double>(ey) + 0.5) \
								/ static_cast<double>(extra) \
								* static_cast<double>(Step);

						const RT::Ray ray = camera->GenerateRay(x, y);

						SummaryColor += Trace(ray);
					}

				*buffer_iterator = SummaryColor / double(extra * extra);

				++buffer_iterator;

				if(i % updateInterval == 0)
				{
					const size_t percent = 90 *
						static_cast<size_t>(buffer_iterator - buffer.begin()) / qn;

					if(callback->call(static_cast<double>(percent)))
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
	}


	if(callback->call(95))
		return false;

	// остался последний шаг, перенести всё это на экран

	DrawBuffer(app, rectangles, Step);

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

RealColor RT::Scene::Trace(const RT::Ray &ray) const
{
	if(ray.Power >= MinimumRayPower && RT::CompoundObject::PossibleIntersection(ray))
	{
		const RT::MaybeIntersection result = RT::CompoundObject::FindIntersection(ray);

		if(result.Exists)
		{
			const RT::SharedTracer tracer = static_cast<RT::Intersection>(result).Tracer;

			const RealColor result = tracer->Trace(this);

			// проверяем что не получился отрицательный цвет
			assert(result.R >= 0 && result.G >= 0 && result.B >= 0);

			return result;
		}
	}

	return static_cast<RealColor>(Palette::Black);
}
