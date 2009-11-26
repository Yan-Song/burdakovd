#include "Scene.h"
#include "Projection.h"
#include <vector>
#include <map>
#include <algorithm>
#include "SDLApplication.h"
#include "SDLException.h"
#include "Utils.h"
#include "Color.h"
#include <cmath>

#define W(point) (1.0 / ((point)[1] - SpectatorPosition[1]))

namespace
{
	typedef std::pair<double, double> WPair;

	struct Point
	{
		Point2D p;
		double w;

		Point(const Point2D& _p, const double _w) : p(_p), w(_w) {}
	};

	typedef std::pair<Point, Point> Segment;

	bool operator <(const Point& a, const Point& b)
	{
		return a.p[1] < b.p[1];
	}
}

class Scene3D::Util
{
private:
	inline static void DrawPixel(const int x, const int y, const double w, const Color& color, Scene3D* scene)
	{
		const size_t index = static_cast<unsigned int>(x + y * scene->ScreenSize[0]);

		if(w > scene->WBuffer[index])
		{
			scene->WBuffer[index] = w;
			scene->PixelBuffer[index] = color;
		}
	}

	inline static void DrawPixels(const double x1, const double x2, const double w1, const double dw_dx, const int y, const Color& color, const SDLApplication* app, Scene3D* scene)
	{
		const int start = std::max(0, static_cast<int>(ceil(x1)));
		const int finish = std::min(app->Screen->w - 1, static_cast<int>(floor(x2)));

		double w = w1 + dw_dx * (start - x1);

		for(int x = start; x <= finish; ++x, w += dw_dx)
			DrawPixel(x, y, w, color, scene);
	}

public:
	// функция получает два отрезка и закрашивает пространство между ними
	// заранее известно, что у каждого отрезка первая точка имеет Y не больше чем вторая
	// а также p левее q
	inline static void FillInside(const Segment& p, const Segment& q, const Color& color, const SDLApplication* app, Scene3D* scene)
	{
		const int ystart = std::max(0, static_cast<int>(ceil(std::max(p.first.p[1], q.first.p[1]))));
		const int yfinish = std::min(app->Screen->h - 1, static_cast<int>(floor(std::min(p.second.p[1], q.second.p[1]))));

		// d##_dy - это производная ## по y (константа, так как эти переменные линейны по x и по y), смысл переменных ## - объяснен ниже
		// если отрезок p горизонтален, то dpw_dy, dpx_dy не имеет смысла, так что пусть будет 0
		const double dpw_dy = (p.second.p[1] == p.first.p[1]) ? 0 : (p.second.w - p.first.w) / (p.second.p[1] - p.first.p[1]);
		const double dpx_dy = (p.second.p[1] == p.first.p[1]) ? 0 : (p.second.p[0] - p.first.p[0]) / (p.second.p[1] - p.first.p[1]);

		// если отрезок q горизонтален, то dqw_dy, dqx_dy не имеет смысла, так что пусть будет 0
		const double dqw_dy = (q.second.p[1] == q.first.p[1]) ? 0 : (q.second.w - q.first.w) / (q.second.p[1] - q.first.p[1]);
		const double dqx_dy = (q.second.p[1] == q.first.p[1]) ? 0 : (q.second.p[0] - q.first.p[0]) / (q.second.p[1] - q.first.p[1]);

		// нахождение dw_dx
		// кроме вырожденных случаев, только на одном y выполняется deltax = qx - px == 0 (в точке пересечения)
		// так как dw_dx не зависит от y, то можно сложить равенства deltaw = deltax * dw_dx, для двух разных y
		// и получить (deltaw1 + deltaw2) = (deltax1 + deltax2) * dw_dx
		// dw_dx = (deltaw1 + deltaw2) / (deltax1 + deltax2)
		// возьмем в качестве двух разных y ystart и yfinish
		// в знаменателе будет 0 только в вырожденном случае (если ystart = yfinish = ординате точки пересечения)
		// в этом случае рисуем только одну точку и dw_dx не имеет значения
		const double deltax1 = (q.first.p[0] + (ystart - q.first.p[1]) * dqx_dy) - (p.first.p[0] + (ystart - p.first.p[1]) * dpx_dy);
		const double deltax2 = (q.first.p[0] + (yfinish - q.first.p[1]) * dqx_dy) - (p.first.p[0] + (yfinish - p.first.p[1]) * dpx_dy);
		const double deltaw1 = (q.first.w + (ystart - q.first.p[1]) * dqw_dy) - (p.first.w + (ystart - p.first.p[1]) * dpw_dy);
		const double deltaw2 = (q.first.w + (yfinish - q.first.p[1]) * dqw_dy) - (p.first.w + (yfinish - p.first.p[1]) * dpw_dy);
		const double dw_dx = (deltax1 + deltax2 == 0) ? 0 : (deltaw1 + deltaw2) / (deltax1 + deltax2);

		// pw - это значение w в точке пересечения прямой, содержащей отрезок p и прямой Y = y, сейчас Y = ystart
		double pw = p.first.w + (ystart - p.first.p[1]) * dpw_dy;
		// px - это значение x в точке пересечения прямой, содержащей отрезок p и прямой Y = y, сейчас Y = ystart
		double px = p.first.p[0] + (ystart - p.first.p[1]) * dpx_dy;
		// qx - это значение x в точке пересечения прямой, содержащей отрезок q и прямой Y = y, сейчас Y = ystart
		double qx = q.first.p[0] + (ystart - q.first.p[1]) * dqx_dy;

		for(int y = ystart; y <= yfinish; ++y)
		{
			DrawPixels(px, qx, pw, dw_dx, y, color, app, scene);

			pw += dpw_dy;
			px += dpx_dy;
			qx += dqx_dy;
		}
	}
};

// http://algolist.manual.ru/graphics/3dfaq/articles/33.php
// здесь я использую тот факт, что w = 1 / (dist + z),
// где dist - расстояние от наблюдателя до картинной плоскости
// z - расстояние от точки до той же плоскости
// так вот w - зависит в пределах грани линейно от sx, sy - экранных координат
// то есть зная w в вершинах треугольника можно найти и w для любой точки на экране внутри проекции этого треугольника
// и вместо z-буффера использовать w-буффер
void Scene3D::DrawTriangle(const Point3D &A, const Point3D &B, const Point3D &C, const Color& color)
{
	// ---------------------------------------------------------------------------------------
	// вспомогательные вычисления
	// нормаль
	const Vector3D& n = (B - A) ^ (C - A);

	if(n.Length() ==  0)
		return; // вырожденный треугольник

	// центр треугольника
	const Point3D& medium = (A + B + C) / 3.0;
	// вектор к зрителю
	const Vector3D SpectatorV = SpectatorPosition - medium;

	// ---------------------------------------------------------------------------------------
	// проверить угол между нормалью к треугольнику и направлением к зрителю
	// и если треугольник повернут "задом" то его не рисовать
	if(n * SpectatorV < 0)
	{
		return;
	}

	// ---------------------------------------------------------------------------------------
	// рассчитаем освещенность грани (считая что она освещена равномерно)
	// освещенность это сумма рассеянного освещения (ambient)
	// плюс сумма мощностей источников света, умноженных на косинусы углов падения света на грань
	// и в конце нормирую эту сумму, чтобы вместе с ambient она могла дать максимум 1.0
	const double ambient = 0.6;
	const size_t nlight = Light.size(); // количество источников
	double sumpower = 0; // сумма мощностей
	double lightness = 0; // освещенность, без учета ambient и не нормированная

	for(unsigned int i = 0; i < nlight; ++i)
	{
		const double power = Light[i].second;
		const Point3D position = Light[i].first;
		const Point3D l = position - medium;
		const double cosphi = n * l / n.Length() / l.Length();

		sumpower += power;
		lightness += power * cosphi;
	}

	// итоговая освещенность
	const double light = ambient + (sumpower == 0 ? 0 : lightness / sumpower * 0.4);
	assert(light >= 0.0 && light <= 1.0);

	// на основе освещенности рассчитываем новый цвет грани
	const Color realcolor = static_cast<RealColor>(color) * light;

	// ---------------------------------------------------------------------------------------
	// проекция
	const Projection::Matrix projector = Projection::PerspectiveProjection<1>(SpectatorPosition);

	// вершины треугольника, спрецированные на экранную плоскость
	const Point2D a = Projection::GetXZ(projector * A);
	const Point2D b = Projection::GetXZ(projector * B);
	const Point2D c = Projection::GetXZ(projector * C);

	// соответствующие им w
	const double wa = W(A);
	const double wb = W(B);
	const double wc = W(C);

	// Отсортировав вершины треугольника по y, вместе с их значениями w
	std::vector<Point> v;
	v.push_back(Point(a, wa));
	v.push_back(Point(b, wb));
	v.push_back(Point(c, wc));
	std::sort(v.begin(), v.end());

	const Point p = v[0], q = v[1], r = v[2];

	// можно закрасить его верхнюю и нижнюю половину
	if(VectorMultiplication2D(q.p - p.p, r.p - p.p) < 0) // делаю чтобы первый сегмент был левее второго
	{
		Util::FillInside(Segment(p, q), Segment(p, r), realcolor, app, this);
		Util::FillInside(Segment(q, r), Segment(p, r), realcolor, app, this);
	}
	else
	{
		Util::FillInside(Segment(p, r), Segment(p, q), realcolor, app, this);
		Util::FillInside(Segment(p, r), Segment(q, r), realcolor, app, this);
	}
}

void Scene3D::ClearBuffers()
{
	const size_t n = static_cast<size_t>(ScreenSize[0] * ScreenSize[1]);

	memcpy(&*(WBuffer.begin()), &*(CleanWBuffer.begin()), n * sizeof(*(WBuffer.begin())));
	memcpy(&*(PixelBuffer.begin()), &*(CleanPixelBuffer.begin()), n * sizeof(*(PixelBuffer.begin())));
}

void Scene3D::DrawPixelBuffer()
{
	const size_t xmax = static_cast<size_t>(ScreenSize[0]), \
	ymax = static_cast<size_t>(ScreenSize[1]), \
	xmin = 0, ymin = 0;

	if(Smoothing)
	{

		for(size_t y = ymin + 1; y + 1 < ymax; ++y)
			for(size_t x = xmin + 1; x + 1 < xmax; ++x)
			{
				const size_t index = x + y * xmax;
				const size_t indexl = index - 1, indexr = index + 1, indext = index + xmax, indexb = index - xmax;

				if(WBuffer[index] == 0 && WBuffer[indexl] == 0 && WBuffer[indexr] == 0 && WBuffer[indext] == 0 && WBuffer[indexb] == 0)
					continue;

				app->RawDrawPixel(static_cast<int>(x), static_cast<int>(y),
					(PixelBuffer[indexl] + PixelBuffer[indexr] + PixelBuffer[indext] + PixelBuffer[indexb] + PixelBuffer[index]) / 5
					);
			}
	}
	else
	{
		for(size_t y = ymin, index = 0; y < ymax; ++y)
			for(size_t x = xmin; x < xmax; ++x)
				{
					if(WBuffer[index] != 0)
						app->RawDrawPixel(static_cast<int>(x), static_cast<int>(y), PixelBuffer[index]);

					++index;
				}
	}
}

void Scene3D::Render()
{
	assert((ScreenSize[0] == app->Screen->w) && (ScreenSize[1] == app->Screen->h));

	ClearBuffers();
	app->ClearScreen();

	CompoundObject3D::Draw(Vector000, this);

	app->Lock();
	DrawPixelBuffer();
	app->Unlock();

	app->Flip();
}

Scene3D::Scene3D(const Vector3D& _SpectatorPosition, const ScreenPoint& _ScreenSize, SDLApplication* const _app) :
	ScreenSize(_ScreenSize), app(_app), n(static_cast<size_t>(ScreenSize[0] * ScreenSize[1])),
	WBuffer(n), CleanWBuffer(n, 0.0),
	PixelBuffer(n), CleanPixelBuffer(n, Palette::Black),
	Light(),
	SpectatorPosition(_SpectatorPosition),
	Smoothing(false)
{

}

Scene3D::~Scene3D()
{

}
