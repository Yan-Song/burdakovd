#ifndef LINE_H
#define LINE_H

#include "graphobject.h"
#include "Vector.h"
#include <SDL.h>
#include "color.h"
#include "matrix.h"

class Line : public GraphObject
{
public:
	Point2D A, B;
	Color color;

	Line(Point2D a, Point2D b): A(a), B(b), color(0xffffff) { }

	Line(Point2D a, Point2D b, Color c): A(a), B(b), color(c) { }

	virtual void Draw(const SDLApplication*) const;

    //virtual void Modify(const Matrix& m);
    
    virtual ~Line() {};
};

#endif
