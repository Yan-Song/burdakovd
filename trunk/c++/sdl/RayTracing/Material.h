#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include "Shared.h"
#include "sdlapplication/Vector.h"
#include "sdlapplication/Color.h"
#include "NormalizedVector3D.h"
#include "Ray.h"
#include <map>

namespace RT
{
	// �������� - ����� ��������� ��������.
	// � ��������� ��� �������� ����� � ������ ��������, ���� ������� ���������/������������
	class Material
	{
	public:
		typedef shared_ptr<const Texture> SharedTexture;

	private:
		bool has_texture;
		Point2D base;
		Vector2D dx, dy;
		SharedTexture Texture;
		RealColor color;
		
	private:
		RealColor GetPixel(const Point2D& MaterialPoint) const;
		
		Point2D TexturePoint(const Point2D& MaterialPoint) const;

	public:		
			
	public:
		Material(const RealColor& _color = Palette::White);

		// ���������� ����, ���� ������ ���� ������������ �������� - ��� ��������
		void SetColor(const RealColor& _color);

		// ���������� ��������
		// base, dx, dy ����� � ���������� �������������� � Trace
		// ���� � ���, ��� ���������� �� ������� (�����������/�����) ����� �� ��������������� ����������� ��������
		// � ���������� ������� ����� ������������ � ���������� �� �������� ��������� �������:
		// TexturePoint = base + MaterialPoint.x * dx + MaterialPoint.y * dy
		// ����� ������� ���� ����� ��������� ��������� �������� �� ������� ������, �����
		// ������ ��������� dx, dy
		// ����� ���������� ����������� ����������
		void SetTexture(const SharedTexture& texture, const Point2D& base, const Vector2D& dx, const Vector2D& dy);

		// �������� ����� ��������� � ������� base, dx, dy
		// ����� �������������� � ��������� ��������
		// ���������� ��� ���������� �� ����������, � ������������
		// ������ ������ ��� ����� ���������� � ����������
		Material Cut(const Point2D& base, const Vector2D& dx, const Vector2D& dy) const;

		RealColor Trace(const Point3D& point, const Point2D& MaterialPoint, const NormalizedVector3D& n, const Ray& ray) const;
	};
}

#endif
