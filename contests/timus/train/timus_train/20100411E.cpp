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

struct point
{
	i64 x, y;

	point(i64 xx, i64 yy) : x(xx), y(yy)
	{

	}

	point() : x(0), y(0)
	{
	}
};

inline istream& operator >>(istream& is, point& p)
{
	return is >> p.x >> p.y;
}

i64 intersect(i64 p1, i64 p2, i64 q1, i64 q2)
{
	if(p1 > p2)
		swap(p1, p2);

	if(q1 > q2)
		swap(q1, q2);

	int left = max(p1, q1), right = min(p2, q2);

	return right - left;
}

int main()
{
	point p1, p2, q1, q2;

	cin >> p1 >> p2 >> q1 >> q2;

	const i64 w = intersect(p1.x, p2.x, q1.x, q2.x), h = intersect(p1.y, p2.y, q1.y, q2.y);

	const bool pdir = (p2.x > p1.x) == (p2.y > p1.y);
	const bool qdir = (q2.x > q1.x) == (q2.y > q1.y);

	if(w >= 0 && h >= 0)
	{
		cout << (pdir == qdir ? w + h : max(w, h)) << endl;
	}
	else
	{
		cout << 0 << endl;
	}

	return 0;
}
