#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <cmath>

typedef std::pair<int,int> pii;

const double Pi = acos(-1.0);

template<class T>
inline T min(const T& x, const T& y)
{
    return x > y ? y : x;
}

template<class T>
inline T max(const T& x, const T& y)
{
    return x < y ? y : x;
}

#define sqr(x) ((x) * (x))

template<typename T>
inline T sgn(const T x)
{
  if(x==0) return 0; 
  return x < 0 ? -1 : 1;
}

#endif
