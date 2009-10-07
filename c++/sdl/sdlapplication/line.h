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
	OldHomogeneousPoint2D A, B;
	Color colorA, colorB;

	Line(OldHomogeneousPoint2D a, OldHomogeneousPoint2D b): A(a), B(b), colorA(0xffffff), colorB(0xffffff) { }

	Line(OldHomogeneousPoint2D a, OldHomogeneousPoint2D b, Color c): A(a), B(b), colorA(c), colorB(c) { }

    Line(OldHomogeneousPoint2D a, OldHomogeneousPoint2D b, Color ca, Color cb): A(a), B(b), colorA(ca), colorB(cb) { }

	virtual void Draw(const SDLApplication* ) const;

    virtual void Modify(const Matrix& m);
    
    virtual ~Line() {};
};

#endif
