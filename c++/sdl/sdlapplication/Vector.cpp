#include "Vector.h"
#include "matrix.h"
#include <cmath>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const OldHomogeneousVector2D& v)
{
    os<<"OldHomogeneousVector2D("<<v.x<<"; "<<v.y<<"; "<<v.k<<")";
    return os;
}
