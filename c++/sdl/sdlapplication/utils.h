#ifndef UTILS_H
#define UTILS_H

#include <map>

typedef std::pair<int,int> pii;

const double Pi = acos(-1.0);

template<class T>
inline T min(const T& x, const T& y)
{
    return x > y ? y : x;
}

#endif
