#ifndef GOBJECT_H
#define GOBJECT_H

#include <SDL.h>
#include "matrix.h"
#include "Vector.h"
#include "sdlapplication.h"

class GraphObject
{
public:
	virtual void Draw(const SDLApplication*) const = 0;
	
    /*virtual void Modify(const Matrix& m) = 0;

    inline void Shift(const OldHomogeneousPoint2D& d)
    {
        Modify(Matrix::Shift(d));
    }

    inline void Scale(const OldHomogeneousPoint2D& base, const double kx, const double ky)
    {
        Modify(Matrix::Scale(base, kx, ky));
    }

    inline void Rotate(const OldHomogeneousPoint2D& base, const double phi)
    {
        Modify(Matrix::Rotate(base, phi));
    }

    inline void ReflectX(const double x)
    {
        Modify(Matrix::ReflectX(x));
    }

    inline void ReflectY(const double y)
    {
        Modify(Matrix::ReflectY(y));
    }
    */
    virtual ~GraphObject() {};
};

#endif
