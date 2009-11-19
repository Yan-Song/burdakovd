#ifndef MATERIAL_H
#define MATERIAL_H

#include <map>
#include <sdlapplication/Color.h>
#include <sdlapplication/Shared.h>
#include <sdlapplication/Vector.h>
#include "IEngine.h"
#include "NormalizedVector3D.h"
#include "Ray.h"
#include "Texture.h"

namespace RT
{
	// Материал - некое обобщение текстуры.
	// в дальнеёшем тут возможно будут и другие парметры, типа степень отражения/прозрачность
	class Material
	{
	public:
		typedef Shared::shared_ptr<const RT::Texture> SharedTexture;

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

		// установить цвет, если раньше была использована текстура - она удалится
		void SetColor(const RealColor& _color);

		// установить текстуру
		// base, dx, dy будут в дальнейшем использоваться в Trace
		// дело в том, что координаты на объекте (треугольник/сфера) могут не соответствовать координатам текстуры
		// и координаты объекта будут переводиться в координаты на текстуре следующим образом:
		// TexturePoint = base + MaterialPoint.x * dx + MaterialPoint.y * dy
		// Таким образом если нужно растянуть маленькую текстуру на большой объект, можно
		// задать маленькие dx, dy
		// здесь координаты указываются текстурные
		void SetTexture(const SharedTexture& texture, const Point2D& base, const Vector2D& dx, const Vector2D& dy);

		// вырезать кусок материала с другими base, dx, dy
		// может использоваться в составных объектах
		// координаты тут указыаются не текстурные, а материальные
		// внутри метода они будут переведены в текстурные
		Material Cut(const Point2D& base, const Vector2D& dx, const Vector2D& dy) const;

		RealColor Trace(const Point3D& point, const Point2D& MaterialPoint, \
			const NormalizedVector3D& n, const Ray& ray, const RT::IEngine* engine) const;
	};
}

#endif
