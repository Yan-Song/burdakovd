#ifndef FILLPOLYGON_H
#define FILLPOLYGON_H

#include <vector>
#include "Vector.h"
#include <algorithm>
#include <functional>
#include <map>
#include <list>
#include "Utils.h"

inline bool simpleYComparator(const ScreenPoint& a, const ScreenPoint& b)
{
	return a[1] < b[1];
}

// ���������� ��� ����� �� �� Y ����������, ������� �� ���� ������ ��� �����
class yComparator
{
public:
	const std::vector<ScreenPoint>& vertices;

	yComparator(const std::vector<ScreenPoint>& _vertices) : vertices(_vertices) {};

	inline bool operator ()(const int i, const int j) const
	{
		return vertices[i][1] < vertices[j][1];
	}
};

// ���������, ������������� �� ������ ����� � ������� ������
class SARRemovePredicate
{
public:
	const std::vector<ScreenPoint>& vertices;
	const int currentY;

	SARRemovePredicate(const std::vector<ScreenPoint>& _vertices, const int _currentY) : vertices(_vertices), currentY(_currentY) {};

	inline bool operator ()(const pii& edge) const
	{
		// �� ��� �� ���������� �����-�� ����� ������
		assert(vertices[edge.second][1] >= currentY);
		return vertices[edge.second][1] == currentY;
	}
};

// ������� �������� ����� ����������� ����� � ������� �������
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

// http://algolist.manual.ru/graphics/fill.php
// ������� FillPolygon ��������� ������ ������ � ����� ������ ������ � �������/������� DrawPixel, ����������� x � y
template<class DrawPixelFunction>
void FillPolygon(const std::vector<ScreenPoint>& vertices, const ScreenPoint& ScreenSize, const DrawPixelFunction& DrawPixel)
{
	int n = vertices.size();
	
	if (n == 0) return;

	// 1) ������ ������� ��� y
	int minY = (*std::min_element(vertices.begin(), vertices.end(), simpleYComparator))[1];

	// 2) ������� ������� ��� y
	int maxY = (*std::max_element(vertices.begin(), vertices.end(), simpleYComparator))[1];

	// ���� �� ����� �� ��������� ������ ������, �� ������ �������� ��� ������
	maxY = std::min(maxY, ScreenSize[1]);

	// 3) ������ ������ ������� ������, ��������������� �� ��������
	std::vector<int> ys(n);
	for(int i = 0; i < n; ++i)
		ys[i] = i;

	std::sort(ALL(ys), yComparator(vertices));

	// 4) �������� � ������������ y, � ������ ��� - ������� �������� �����
	// 5) ����� ����������� � ����� ���� �� ����� �� ��������� ������
	std::list<pii> SAR;
	std::vector<int>::const_iterator nextVertice = ys.begin();

	for(int currentY = minY; currentY <= maxY; )
	{
		assert(nextVertice == ys.end() || vertices[*nextVertice][1] >= currentY); // �� ��� �� ���������� �����-�� �������

		// 6) �������� � ��� �����, ������������ � ������� ������
		// ���� ��� ��������������, �� �� ��������� � ������ ����������
		while(nextVertice != ys.end() && vertices[*nextVertice][1] == currentY) // ���� ������� �� ���� ������
		{
			int cur = *nextVertice;
			++nextVertice;
			int prev = (cur + n - 1) % n;
			int next = (cur + 1) % n;
			
			if(vertices[prev][1] > currentY)
				SAR.push_back(pii(cur, prev));
			else if(vertices[prev][1] == currentY)
				DrawPixels(vertices[prev][0], vertices[cur][0], currentY, ScreenSize, DrawPixel);

			if(vertices[next][1] > currentY)
				SAR.push_back(pii(cur, next));
			// ����� ��� ����� ��������� �� ���������, �.�. ��� ���� ����� � ������ y ��� ����������� ����
		}

		// 7) ������� �� ��� �����, ��������������� �� ���� ������
		SAR.remove_if(SARRemovePredicate(vertices, currentY));

		assert(SAR.size() % 2 == 0); // ������ ������ ���������� ������ ����� �����

		if(nextVertice == ys.end())
		{
			assert(SAR.empty()); // ����� ���� �� ������ ����
			return;  // ������ ��� ������
		}

		// 8) ���������� ������, ���� �� �� ������, ����� �� ��������
		if(currentY < 0)
		{
			// ��� ������, �������� �� ����, ���������� ������
			// ��� �� ��������� ������� ��� ���� ������
			currentY = std::min(vertices[*nextVertice][1], 0);
		}
		else
		{
			// � �������� ������, ����� ��������, ���� �� ����� �� ��������� ������� ��� maxY �������
			int Ylim = std::min(maxY, vertices[*nextVertice][1]);

			for(; currentY <= Ylim; ++currentY)
			{
				std::vector<int> intersections(SAR.size());

				std::transform(SAR.begin(), SAR.end(), intersections.begin(), Intersector(vertices, currentY));

				std::sort(intersections.begin(), intersections.end());

				assert(intersections.size() % 2 == 0);

				for(unsigned int i = 0; i < intersections.size(); i += 2)
					DrawPixels(intersections[i], intersections[i+1], currentY, ScreenSize, DrawPixel);
			}

			--currentY; // ������������ � ��������� ����������� ������

			// ���� ��� ���� ��������� ������, �� �����
			if(currentY == maxY)
				return;

			// ����� ��� ���� ������ � ���������, �� ��������� �������� ��� ����� ����������
		}

	}

	// ?) ���������� ��� ������, ������ ������ ������
}

#endif
