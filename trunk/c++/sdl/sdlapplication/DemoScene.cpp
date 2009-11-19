#include "DemoScene.h"
#include "Vector.h"
#include "Pencil.h"
#include "Tetragon.h"
#include "Cube.h"
#include "CompoundObject.h"
#include "Affine.h"
#include <cmath>

DemoScene::DemoScene(const Vector3D &center)
{
	Center = center;

	const double PaperWidth = 300;
	const double PaperHeight = 500;
	const Vector3D PaperA = 0.5 * Vector3DByCoords(-PaperWidth, PaperHeight, 0);
	const Vector3D PaperB = 0.5 * Vector3DByCoords(-PaperWidth, -PaperHeight, 0);
	const Vector3D PaperC = 0.5 * Vector3DByCoords(PaperWidth, -PaperHeight, 0);
	const Vector3D PaperD = 0.5 * Vector3DByCoords(PaperWidth, PaperHeight, 0);

	const double PencilX = 60;
	const double PencilY = 45;
	const double PencilHeight = 450;
	const Vector3D PencilBase = PaperA + Vector3DByCoords(PencilX, -PencilY, 0);
	const Vector3D PencilCenter = PencilBase + Vector3DByCoords(0, 0, PencilHeight / 2);

	const double PencilRotateX = -0.2;
	const double PencilRotateY = 0.8;
	const Color PaperColor(0xef6010);

	// лист бумаги можно предствить как параллелепипед или растянутый куб очень маленькой высоты
	const double hh = 0.1;
	GraphObject3D* paper = new Cube(Vector000, hh, PaperColor);
	paper->Scale(Vector3DByCoords(PaperWidth / hh, PaperHeight / hh, 1));
	paper->Move(Vector3DByCoords(0, 0, -hh / 2));
	CompoundObject3D::Add(paper);
	
	GraphObject3D* pencil = new Pencil(PencilCenter, PencilHeight, Color(0x30D5C8), Color(0xffff7f), Color(0x3f3f3f));
	pencil->RotateRelative(Affine::X, PencilRotateX, PencilBase);
	pencil->RotateRelative(Affine::Y, PencilRotateY, PencilBase);
	CompoundObject3D::Add(pencil);

	const double CubeXOffset = 120;
	const double CubeYoffset = 100;
	const double CubeHeight = 50;

	const Vector3D CubeCenter = PaperC + Vector3DByCoords(-CubeXOffset, CubeYoffset, CubeHeight / 2);
	const Vector3D Cube2Center = CubeCenter + Vector3DByCoords(CubeHeight, 0, 0);
	const Vector3D Cube3Center = CubeCenter + Vector3DByCoords(CubeHeight, CubeHeight, 0);
	const Vector3D Cube4Center = CubeCenter + Vector3DByCoords(0, CubeHeight, 0);
	const Vector3D Cube5Center = CubeCenter + Vector3DByCoords(CubeHeight / 2, CubeHeight / 2, CubeHeight);

	CompoundObject3D::Add(new Cube(CubeCenter, CubeHeight, Color(0xd0d0d0)));
	CompoundObject3D::Add(new Cube(Cube2Center, CubeHeight, Color(0x000080)));
	CompoundObject3D::Add(new Cube(Cube3Center, CubeHeight, Color(0x008000)));
	CompoundObject3D::Add(new Cube(Cube4Center, CubeHeight, Color(0x808000)));
	CompoundObject3D::Add(new Cube(Cube5Center, CubeHeight, Color(0x800080)));
}
