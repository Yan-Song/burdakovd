#ifndef SCENE_H
#define SCENE_H

#include "SDLApplication.h"
#include "CompoundObject.h"
#include "GraphObject.h"
#include "Interfaces.h"
#include "Color.h"
#include <vector>
#include <map>
#include "sdlapplication/Shared.h"

class Scene2D : public CompoundObject2D
{
public:
	// добавить объект
	// объект, указатель на который передан, будет удалён в деструкторе, вызывыющая сторона не должна этим заниматься
	inline void Add(GraphObject2D* const object)
	{
		CompoundObject2D::Add(object);
	}
};

class Scene3D : private CompoundObject3D, public ITriangleDrawer
{
public:
	void DrawTriangle(const Point3D& A, const Point3D& B, const Point3D& C, const Color& color);

private:
	const ScreenPoint ScreenSize;

	SDLApplication* const app;
	size_t n;
	std::vector<double> WBuffer;
	std::vector<double> CleanWBuffer;
	std::vector<Color> PixelBuffer;
	std::vector<Color> CleanPixelBuffer;
	std::vector<std::pair<Point3D, double> > Light;

	void ClearBuffers();
	void DrawPixelBuffer();

	Scene3D(const Scene3D& );
	Scene3D operator=(const Scene3D& );

	class Util;
	friend class Util;


public:
	Vector3D SpectatorPosition;
	bool Smoothing;

	Scene3D(const Vector3D& spectatorPosition, const ScreenPoint& ScreenSize, SDLApplication* const _app);

	void Render();

	inline void Add(GraphObject3D* const object)
	{
		CompoundObject3D::Add(object);
	}

	inline void AddLight(const Point3D& position, const double power)
	{
		Light.push_back(std::pair<Point3D, double>(position, power));
	}

	inline void ClearLights()
	{
		Light.clear();
	}

	inline unsigned int LightCount() const
	{
		return Light.size();
	}

	virtual ~Scene3D();
};

#endif
