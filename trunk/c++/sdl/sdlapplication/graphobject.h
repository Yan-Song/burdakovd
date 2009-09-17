#ifndef GOBJECT_H
#define GOBJECT_H

#include <SDL.h>
#include "matrix.h"
#include "Vector.h"

class GraphObject
{
public:
	virtual void Draw(SDL_Surface*) = 0;
	
    virtual void Modify(const Matrix& m) = 0;

    inline void Shift(const Point& d)
    {
        Modify(Matrix::Shift(d));
    }

    inline void Scale(const double kx, const double ky)
    {
        Modify(Matrix::Scale(kx, ky));
    }

    inline void Scale(const Point& base, const double kx, const double ky)
    {
        Modify(Matrix::Scale(base, kx, ky));
    }

    inline void Rotate(const double phi)
    {
        Modify(Matrix::Rotate(phi));
    }

    inline void Rotate(const Point& base, const double phi)
    {
        Modify(Matrix::Rotate(base, phi));
    }
};

#endif
