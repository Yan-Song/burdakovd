#include "Vector.h"
#include "matrix.h"
#include <cmath>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os<<"Vector("<<v.x<<"; "<<v.y<<"; "<<v.k<<")";
    return os;
}
