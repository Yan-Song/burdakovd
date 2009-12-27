#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <cstring>
#include <map>
#include <SDL.h>
#include "SDLException.h"

#define mset(x, v) memset(x, v, sizeof(x))

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
  if(x == 0) return 0; 
  return x < 0 ? -1 : 1;
}

namespace
{
	inline void __assert(const bool assertion, const std::string& description)
	{
		if(!assertion)
			throw AssertionException(description);
	}
}

inline int iround(const double num) {
    return static_cast<int>((num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5));
}

#define assert(assertion) __assert(assertion, #assertion)

#define ALL(v) v.begin(), v.end()

SDL_Rect Intersect(const SDL_Rect& first, const SDL_Rect& second);

#endif
