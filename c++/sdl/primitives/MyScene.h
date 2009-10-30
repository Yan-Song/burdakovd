#ifndef MYSCENE_H
#define MYSCENE_H

#include "Scene.h"

class MyScene : public Scene
{
private:
	int Width, Height;

public:
	MyScene(const int width, const int height) : Width(width), Height(height)
	{
	};

	void Tick(const double dt);
};

#endif