#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <complex>
#include <cassert>
#include <iomanip>
#include <sstream>
 
#pragma comment(linker, "/STACK:16777216")
 
#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define fosz(i,s,x) for(int i=s; i<x.size(); i++)
#define foreach(i,x) fosz(i,0,x)
#define debug(x) cerr<<(#x)<<" = "<<(x)<<endl
#define adebug(x,n) fo(i,0,n) cerr<<(#x)<<"["<<i<<"] = "<<x[i]<<endl
#define vdebug(x) foreach(i,x) cerr<<(#x)<<"["<<i<<"] = "<<x[i]<<endl
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()
#define sqr(t) ((t)*(t))

using namespace std;
 
typedef long long i64;
typedef unsigned long long u64;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<i64> v64;
typedef vector<i64> vv64;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
 
const double pi=2*acos(0.0);
const int inf=1<<25;

inline int gcd(const int x, const int y)
{
	return y ? gcd(y, x % y) : x;
}

template<typename P, typename Q>
inline istream& operator >>(istream& is, pair<P, Q>& p)
{
	return is >> p.first >> p.second;
}

template<typename P, typename Q>
inline ostream& operator <<(ostream& os, const pair<P, Q>& p)
{
	return os << p.first << ' ' << p.second;
}

template<typename T>
inline istream& operator >>(istream& is, vector<T>& v)
{
	for(typename vector<T>::size_type i = 0; i < v.size(); ++i)
		is >> v[i];

	return is;
}

template<typename T>
inline ostream& operator <<(ostream& os, const vector<T>& v)
{
	for(typename vector<T>::size_type i = 0; i < v.size(); ++i)
		os << (i ? " " : "") << v[i];

	return os;
}

typedef string strin;
typedef double doble;
#define cot cout

struct Point
{
	i64 x, y;

	Point() : x(0), y(0) {}

	Point(const i64 x_, const i64 y_) : x(x_), y(y_) {}

	inline i64 qsize() const
	{
		return sqr(x) + sqr(y);
	}
};

typedef Point Vector;

struct Segment
{
	Point a, b;

	Segment() : a(), b() {}

	Segment(const Point& a_, const Point& b_) : a(a_), b(b_) {}
};

inline bool operator ==(const Point& a, const Point& b)
{
	return a.x == b.x && a.y == b.y;
}

inline Point operator -(const Point& a, const Point& b)
{
	return Point(a.x - b.x, a.y - b.y);
}

inline Point operator +(const Point& a, const Point& b)
{
	return Point(a.x + b.x, a.y + b.y);
}

inline i64 operator *(const Point& a, const Point& b)
{
	return a.x * b.x + a.y * b.y;
}

inline i64 operator ^(const Point& a, const Point& b)
{
	return a.x * b.y - a.y * b.x;
}

inline istream& operator >>(istream& is, Point& p)
{
	return is >> p.x >> p.y;
}

inline istream& operator >>(istream& is, Segment& s)
{
	return is >> s.a >> s.b;
}

inline bool niceAngle(const Vector& v1, const Vector& v2)
{
	return (v1 ^ v2) != 0 && v1 * v2 >= 0;
}

inline bool niceAngle(const Segment& l, const Segment& r, const Point& common)
{
	const Vector v1 = l.a - common + l.b - common;
	const Vector v2 = r.a - common + r.b - common;

	return niceAngle(v1, v2);
}

inline bool hasCommonEndWithNiceAngle(const Segment& l, const Segment& r)
{
	if (l.a == r.a || l.a == r.b) return niceAngle(l, r, l.a);
	else if (l.b == r.a || l.b == r.b) return niceAngle(l, r, l.b);
	else return false;
}

inline bool sonapr(const Vector& a, const Vector& b)
{
	return (a * b > 0) && ((a ^ b) == 0);
}

inline bool has(const Segment& s, const Point& p)
{
	return sonapr(s.b - s.a, p - s.a) && sonapr(s.a - s.b, p - s.b);
}

inline bool not4(const Segment& s, const Point& p)
{
	const i64 d1 = (p - s.a).qsize();
	const i64 d2 = (p - s.b).qsize();

	return (d1 <= 16 * d2) && (d2 <= 16 * d1);
}

inline bool isA(const Segment& middle, const Segment& l, const Segment& r)
{
	return hasCommonEndWithNiceAngle(l, r) &&
		has(l, middle.a) &&
		has(r, middle.b) &&
		not4(l, middle.a) &&
		not4(r, middle.b);
}

int main()
{
	int tc;
	cin >> tc;

	for(int ti = 0; ti < tc; ++ti)
	{
		Segment a, b, c;
		cin >> a >> b >> c;
		cout << ((isA(a, b, c) || isA(a, c, b) || isA(b, a, c) || isA(b, c, a) || isA(c, a, b) || isA(c, b, a)) ? "YES" : "NO") << endl;
	}

	return 0;
}
