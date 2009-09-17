#include "Vector.h"
#include "matrix.h"
#include <cmath>
#include <iostream>

#define sqr(x) ((x)*(x))

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os<<"Vector("<<v.x<<"; "<<v.y<<"; "<<v.k<<")";
    return os;
}
