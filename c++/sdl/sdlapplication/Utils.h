#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <cmath>
#include "SDLException.h"

typedef std::pair<int,int> pii;

const double Pi = acos(-1.0);

template<class T>
inline T min(const T& x, const T& y)
{
    return x > y ? y : x;
}

template<typename T>
inline T abs(const T& x)
{
	return x < 0 ? -x : x;
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

inline void __assert(const bool x, const std::string& text)
{
	if(!x)
		throw new AssertionException(text);
}

#define assert(assertion) __assert(assertion, #assertion)

#endif
