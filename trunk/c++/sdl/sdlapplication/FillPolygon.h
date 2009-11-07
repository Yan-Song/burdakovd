#ifndef FILLPOLYGON_H
#define FILLPOLYGON_H

#include <vector>
#include "Vector.h"
#include <algorithm>
#include <functional>
#include <map>
#include <list>
#include "Utils.h"

namespace __FillPolygonUtils
{
	inline bool YComparatorByValue(const ScreenPoint& a, const ScreenPoint& b)
	{
		return a[1] < b[1];
	}

	// сравнивает две точки по их Y координате, получая на вход номера тих точек
	class YComparatorByIndex
	{
	public:
		const std::vector<ScreenPoint>& vertices;

		YComparatorByIndex(const std::vector<ScreenPoint>& _vertices) : vertices(_vertices) {};

		inline bool operator ()(const int i, const int j) const
		{
			return vertices[i][1] < vertices[j][1];
		}
	};

	// проверяет, заканчивается ли данное ребро в текущей строке
	class SARRemovePredicate
	{
	public:
		const std::vector<ScreenPoint>& vertices;
		const int currentY;

		SARRemovePredicate(const std::vector<ScreenPoint>& _vertices, const int _currentY) : vertices(_vertices), currentY(_currentY) {};

		inline bool operator ()(const pii& edge) const
		{
			// то что не пропустили какое-то ребро раньше
			assert(vertices[edge.second][1] >= currentY);
			return vertices[edge.second][1] == currentY;
		}
	};

	// находит абсциссу точки пересечения ребра с текущей строкой
	class Intersector
	{
	public:
		const std::vector<ScreenPoint>& vertices;
		const int currentY;

		Intersector(const std::vector<ScreenPoint>& _vertices, const int _currentY) : vertices(_vertices), currentY(_currentY) {};

		inline int operator ()(const pii& edge) const
		{
			const ScreenPoint& first = vertices[edge.first];
			const ScreenPoint& second = vertices[edge.second];

			const int x1 = first[0], x2 = second[0], y1 = first[1], y2 = second[1];
			const int y = currentY;

			return x1 + (x2 - x1) * (y - y1) / (y2 - y1);
		}
	};

	template<class DrawPixelFunction>
	inline void DrawPixels(const int x1, const int x2, const int y, const ScreenPoint& ScreenSize, const DrawPixelFunction& DrawPixel)
	{
		int xs = std::max(std::min(x1, x2), 0);
		int xf = std::min(std::max(x1, x2), ScreenSize[0]);

		for(int x = xs; x <= xf; ++x)
			DrawPixel(x, y);
	}
}

// http://algolist.manual.ru/graphics/fill.php
// функция FillPolygon принимает вектор вершин а также размер экрана и функцию/функтор DrawPixel, принимающую x и y
template<class DrawPixelFunction>
void FillPolygon(const std::vector<ScreenPoint>& vertices, const ScreenPoint& ScreenSize, const DrawPixelFunction& DrawPixel)
{
	int n = vertices.size();
	
	if (n == 0) return;

	// 1) нижняя граница для y
	int minY = (*std::min_element(vertices.begin(), vertices.end(), __FillPolygonUtils::YComparatorByValue))[1];

	// 2) верхняя граница для y
	int maxY = (*std::max_element(vertices.begin(), vertices.end(), __FillPolygonUtils::YComparatorByValue))[1];

	// если мы дошли до последней строки экрана, то дальше рисовать нет смысла
	maxY = std::min(maxY, ScreenSize[1]);

	// 3) создаём вектор номеров вершин, отсортированный по ординате
	std::vector<int> ys(n);
	for(int i = 0; i < n; ++i)
		ys[i] = i;

	std::sort(ALL(ys), __FillPolygonUtils::YComparatorByIndex(vertices));

	// 4) начинаем с минимального y, с пустым САР - списком активных ребер
	// 5) далее закрашиваем в цикле пока не дойдём до последней строки
	std::list<pii> SAR;
	std::vector<int>::const_iterator nextVertice = ys.begin();

	for(int currentY = minY; currentY <= maxY; )
	{
		assert(nextVertice == ys.end() || vertices[*nextVertice][1] >= currentY); // то что не пропустили какую-то вершину

		// 6) добавить в САР ребра, начинающиеся с текущей строки
		// если они горизонтальные, то не добавлять а просто нарисовать
		while(nextVertice != ys.end() && vertices[*nextVertice][1] == currentY) // ищем вершины на этой строке
		{
			int cur = *nextVertice;
			++nextVertice;
			int prev = (cur + n - 1) % n;
			int next = (cur + 1) % n;
			
			if(vertices[prev][1] > currentY)
				SAR.push_back(pii(cur, prev));
			else if(vertices[prev][1] == currentY)
				__FillPolygonUtils::DrawPixels(vertices[prev][0], vertices[cur][0], currentY, ScreenSize, DrawPixel);

			if(vertices[next][1] > currentY)
				SAR.push_back(pii(cur, next));
			// здесь нет нужды проверять на равенство, т.к. все пары точек с равным y уже прорисованы выше
		}

		// 7) удалить из САР ребра, заканчивающиеся на этой строке
		SAR.remove_if(__FillPolygonUtils::SARRemovePredicate(vertices, currentY));

		assert(SAR.size() % 2 == 0); // каждую строку пересекает четное число ребер

		if(nextVertice == ys.end())
		{
			assert(SAR.empty()); // Ребер тоже не должно быть
			return;  // больше нет вершин
		}

		// 8) нарисовать строку, если мы на экране, иначе не рисовать
		if(currentY < 0)
		{
			// вне экрана, рисовать не надо, пропускаем строки
			// идём до ближайшей вершины или края экрана
			currentY = std::min(vertices[*nextVertice][1], 0);
		}
		else
		{
			// в пределах экрана, нужно рисовать, пока не дойдём до ближайшей вершины или maxY включая
			int Ylim = std::min(maxY, vertices[*nextVertice][1]);

			for(; currentY <= Ylim; ++currentY)
			{
				std::vector<int> intersections(SAR.size());

				std::transform(SAR.begin(), SAR.end(), intersections.begin(), __FillPolygonUtils::Intersector(vertices, currentY));

				std::sort(intersections.begin(), intersections.end());

				assert(intersections.size() % 2 == 0);

				for(unsigned int i = 0; i < intersections.size(); i += 2)
					__FillPolygonUtils::DrawPixels(intersections[i], intersections[i+1], currentY, ScreenSize, DrawPixel);
			}

			--currentY; // возвращаемся к последней закрашенной строке

			// если это была последняя строка, то выход
			if(currentY == maxY)
				return;

			// иначе это была строка с вершинами, на следующей итерации они будут обработаны
		}

	}

	// ?) обработали все строки, больше делать нечего
}

#endif
