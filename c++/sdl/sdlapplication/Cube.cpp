#include "Cube.h"
#include "Polygon.h"
#include "Color.h"
#include "Vector.h"
#include "CompoundObject.h"
#include "Tetragon.h"

Cube::Cube(const Vector3D &center, const double edgeLength, const Color &color)
{
	// сначала строим стандартный маленький кубик, затем масштабируем и перемещаем его куда надо

	// стандартные вершины (центр: начало координат, ребро: 2)
	const Point3D& A = Vector3DByCoords(-1, -1, -1);
	const Point3D& B = Vector3DByCoords(-1, +1, -1);
	const Point3D& C = Vector3DByCoords(+1, +1, -1);
	const Point3D& D = Vector3DByCoords(+1, -1, -1);

	const Point3D& E = Vector3DByCoords(-1, -1, +1);
	const Point3D& F = Vector3DByCoords(-1, +1, +1);
	const Point3D& G = Vector3DByCoords(+1, +1, +1);
	const Point3D& H = Vector3DByCoords(+1, -1, +1);

	// добавляем грани, вершины каждой грани перечисляем против часовой стрелки, если смотреть извне
	Add(new Tetragon(A, B, C, D, color)); // нижняя
	Add(new Tetragon(E, H, G, F, color)); // верхняя

	Add(new Tetragon(A, D, H, E, color));
	Add(new Tetragon(D, C, G, H, color));
	Add(new Tetragon(C, B, F, G, color));
	Add(new Tetragon(A, E, F, B, color));

	// стандартный куб построен, масштабируем
	Scale(Vector111 * edgeLength * 0.5);

	// переносим его в заданную точку
	Move(center);	
}
