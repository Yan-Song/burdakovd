#include "Scene.h"
#include "Projection.h"
#include <vector>
#include <map>
#include <algorithm>
#include "SDLApplication.h"
#include "SDLException.h"
#include "Utils.h"
#include <cmath>

#define W(point) (1.0/((point)[1] - SpectatorPosition[1]))
const double epsilon = 1e-9;

typedef std::pair<double, double> WPair;

struct Point
{
	ScreenPoint p;
	double w;

	Point(const ScreenPoint& _p, const double _w) : p(_p), w(_w) {}
};

typedef std::pair<Point, Point> Segment;

inline bool operator <(const Point& a, const Point& b)
{
	return a.p[1] < b.p[1];
}

inline void DrawPixel(const int x, const int y, const double w, const Color& color, Scene3D* scene)
{
	const int index = x + y * scene->ScreenSize[0];

	// условие +epsilon нужно, т.к. иначе даже при практически неподвижной сцене границы объектов "плывут", создавая печальный вид
	if(w > scene->WBuffer[index] + epsilon)
	{
		scene->WBuffer[index] = w;
		scene->PixelBuffer[index] = color;
	}
	// условие -epsilon чтоб не было резких переходов на границах двух соприкасающихся объектов
	else if(w > scene->WBuffer[index] - epsilon)
	{
		scene->WBuffer[index] = w;
		scene->PixelBuffer[index] = (scene->PixelBuffer[index] + color) / 2;
	}
}

inline void DrawPixels(const int x1, const int x2, const double w1, const double w2, const int y, const Color& color, const SDLApplication* app, Scene3D* scene)
{
	assert(x1 <= x2);

	const int start = std::max(0, x1);
	const int finish = std::min(app->Screen->w - 1, x2);

	const double dw_dx = (x2 == x1) ? 0 : (w2 - w1) / (x2 - x1);
	double w = w1 + dw_dx * (start - x1);

	for(int x = start; x <= finish; ++x, w += dw_dx)
		DrawPixel(x, y, w, color, scene);
}

// функция получает два отрезка и закрашивает пространство между ними
// заранее известно, что у каждого отрезка первая точка имеет Y не больше чем вторая
// а также p левее q
inline void FillInside(const Segment& p, const Segment& q, const Color& color, const SDLApplication* app, Scene3D* scene)
{
	const int ystart = std::max(0, std::max(p.first.p[1], q.first.p[1]));
	const int yfinish = std::min(app->Screen->h - 1, std::min(p.second.p[1], q.second.p[1]));

	const double dpw_dy = (p.second.w - p.first.w) / (p.second.p[1] - p.first.p[1]);
	double pw = p.first.w + (ystart - p.first.p[1]) * dpw_dy;

	const double dqw_dy = (q.second.w - q.first.w) / (q.second.p[1] - q.first.p[1]);
	double qw = q.first.w + (ystart - q.first.p[1]) * dqw_dy;

	for(int y = ystart; y <= yfinish; ++y)
	{
		const int px = (p.second.p[1] == p.first.p[1]) ? std::min(p.first.p[0], p.second.p[0]) :
			p.first.p[0] + (y - p.first.p[1]) * (p.second.p[0] - p.first.p[0]) / (p.second.p[1] - p.first.p[1]);

		const int qx = (q.second.p[1] == q.first.p[1]) ? std::max(q.first.p[0], q.second.p[0]) :
			q.first.p[0] + (y - q.first.p[1]) * (q.second.p[0] - q.first.p[0]) / (q.second.p[1] - q.first.p[1]);

		DrawPixels(px, qx, pw, qw, y, color, app, scene);

		pw += dpw_dy;
		qw += dqw_dy;
	}
}

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
	const unsigned int nlight = Light.size(); // количество источников
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
	const Color realcolor = static_cast<DoubleColor>(color) * light;

	// ---------------------------------------------------------------------------------------
	// проекция
	const Projection::Matrix projector = Projection::PerspectiveProjection<1>(SpectatorPosition);
	
	const ScreenPoint a = Projection::GetXZ(projector * A);
	const ScreenPoint b = Projection::GetXZ(projector * B);
	const ScreenPoint c = Projection::GetXZ(projector * C);

	const double wa = W(projector * A);
	const double wb = W(projector * B);
	const double wc = W(projector * C);

	// Отсортировав вершины треугольника по y
	std::vector<Point> v;
	v.push_back(Point(a, wa));
	v.push_back(Point(b, wb));
	v.push_back(Point(c, wc));
	std::sort(v.begin(), v.end());

	const Point p = v[0], q = v[1], r = v[2];

	// можно закрасить его верхнюю и нижнюю половину
	if(VectorMultiplication2D(q.p - p.p, r.p - p.p) < 0) // делаю чтобы первый сегмент был левее второго
	{
		FillInside(Segment(p, q), Segment(p, r), realcolor, app, this);
		FillInside(Segment(q, r), Segment(p, r), realcolor, app, this);
	}
	else
	{
		FillInside(Segment(p, r), Segment(p, q), realcolor, app, this);
		FillInside(Segment(p, r), Segment(q, r), realcolor, app, this);
	}
}

void Scene3D::ClearBuffers()
{
	const int n = ScreenSize[0] * ScreenSize[1];

	memcpy(WBuffer, CleanWBuffer, n * sizeof(*WBuffer));
	memcpy(PixelBuffer, CleanPixelBuffer, n * sizeof(*PixelBuffer));
}

void Scene3D::DrawPixelBuffer()
{
	const int xmax = ScreenSize[0], ymax = ScreenSize[1], xmin = 0, ymin = 0;

	if(Smoothing)
	{
		
		for(int y = ymin + 1; y + 1 < ymax; ++y)
			for(int x = xmin + 1; x + 1 < xmax; ++x)
			{
				const int index = x + y * xmax;
				const int indexl = index - 1, indexr = index + 1, indext = index + xmax, indexb = index - xmax;

				if(WBuffer[index] == 0 && WBuffer[indexl] == 0 && WBuffer[indexr] == 0 && WBuffer[indext] == 0 && WBuffer[indexb] == 0)
					continue;
	
				app->RawDrawPixel(x, y,
					(PixelBuffer[indexl] + PixelBuffer[indexr] + PixelBuffer[indext] + PixelBuffer[indexb] + PixelBuffer[index]) / 5
					);
			}
	}
	else
	{
		for(int y = ymin, index = 0; y < ymax; ++y)
			for(int x = xmin; x < xmax; ++x)
				{
					if(WBuffer[index] != 0)
						app->RawDrawPixel(x, y, PixelBuffer[index]);

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

Scene3D::Scene3D(const Vector3D& spectatorPosition, const ScreenPoint& _ScreenSize, SDLApplication* const _app)
: SpectatorPosition(spectatorPosition), ScreenSize(_ScreenSize), app(_app), Smoothing(false)
{
	const int n = ScreenSize[0] * ScreenSize[1];

	// индексировать: [x + y * ScreenSize[0]]
	WBuffer = new double[n];
	PixelBuffer = new Color[n];

	CleanWBuffer = new double[n];
	CleanPixelBuffer = new Color[n];

	for(int i = 0; i < n; ++i)
		CleanPixelBuffer[i] = 0;

	for(int i = 0; i < n; ++i)
		CleanWBuffer[i] = 0;
}

Scene3D::~Scene3D()
{
	delete[] WBuffer;
	delete[] PixelBuffer;
	delete[] CleanWBuffer;
	delete[] CleanPixelBuffer;
}
