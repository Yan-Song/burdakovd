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
#include <cstdio>
 
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

inline void clean(vs& a, const int i,const int j)
{
	if(i < 0 || i >= a.size() || j < 0 || j >= a[0].size() || a[i][j] == '0')
	{
		return;
	}

	a[i][j] = '0';
	for(int di = -1; di <= 1; ++di)
		for(int dj = -1; dj <= 1; ++dj)
		{
			if(di || dj)
			{
				clean(a, i + di, j + dj);
			}
		}
}

typedef char (*Getter)(const vs&, const int, const int);

inline char __get(const vs& a, const int i, const int j)
{
	if(i < 0 || j < 0 || i >= a.size() ||  j >= a[0].size())
	{
		return '0';
	}
	else
	{
		return a[i][j];
	}
}


inline int pdfs(const vs& a, const int ii, const int jj, Getter get)
{
	int g;
	for(g = 0; get(a, ii + g, jj) == '1'; ++g)
	{
	}

	bool ok = g > 1;

	// check ones
	for(int gg = 0; gg < g; ++gg)
	{
		ok &= get(a, ii + gg, jj) == '1';
		ok &= get(a, ii + gg, jj + g - 1) == '1';
		ok &= get(a, ii, jj + gg) == '1';
		ok &= get(a, ii + g - 1, jj + gg) == '1';
	}

	// check external nulls
	for(int gg = -1; gg <= g; ++gg)
	{
		ok &= get(a, ii + gg, jj - 1) == '0';
		ok &= get(a, ii + gg, jj + g) == '0';
		ok &= get(a, ii - 1, jj + gg) == '0';
		ok &= get(a, ii + g, jj + gg) == '0';
	}

	// check internal nulls
	for(int gg = 1; gg < g - 1; ++gg)
	{
		ok &= get(a, ii + gg, jj + 1) == '0';
		ok &= get(a, ii + gg, jj + g - 2) == '0';
		ok &= get(a, ii + 1, jj + gg) == '0';
		ok &= get(a, ii + g - 2, jj + gg) == '0';
	}

	return ok ? 1 : 0;
}

inline int ddfs(const vs& a, const int ii, const int jj, Getter get)
{
	int g;
	for(g = 0; get(a, ii + g, jj + g) == '1'; ++g)
	{
	}

	bool ok = g > 1;

	// check ones
	for(int gg = 0; gg < g; ++gg)
	{
		ok &= get(a, ii + gg, jj + gg) == '1';
		ok &= get(a, ii + gg, jj - gg) == '1';
		ok &= get(a, ii + 2 * (g - 1) - gg, jj - gg) == '1';
		ok &= get(a, ii + 2 * (g - 1) - gg, jj + gg) == '1';
	}

	// check nulls
	for(int gg = 0; gg < g + 2; ++gg)
	{
		ok &= get(a, ii - 2 + gg, jj + gg) == '0';
		ok &= get(a, ii - 2 + gg, jj - gg) == '0';
		ok &= get(a, ii - 2 + 2 * (g + 2 - 1) - gg, jj - gg) == '0';
		ok &= get(a, ii - 2 + 2 * (g + 2 - 1) - gg, jj + gg) == '0';
	}

	// check nulls
	for(int gg = 0; gg < g + 1; ++gg)
	{
		ok &= get(a, ii - 1 + gg, jj + gg) == '0';
		ok &= get(a, ii - 1 + gg, jj - gg) == '0';
		ok &= get(a, ii - 1 + 2 * (g + 1 - 1) - gg, jj - gg) == '0';
		ok &= get(a, ii - 1 + 2 * (g + 1 - 1) - gg, jj + gg) == '0';
	}

	// check nulls
	for(int gg = 0; gg < g - 1; ++gg)
	{
		ok &= get(a, ii + 1 + gg, jj + gg) == '0';
		ok &= get(a, ii + 1 + gg, jj - gg) == '0';
		ok &= get(a, ii + 1 + 2 * (g - 1 - 1) - gg, jj - gg) == '0';
		ok &= get(a, ii + 1 + 2 * (g - 1 - 1) - gg, jj + gg) == '0';
	}

	// check nulls
	for(int gg = 0; gg < g - 2; ++gg)
	{
		ok &= get(a, ii + 2 + gg, jj + gg) == '0';
		ok &= get(a, ii + 2 + gg, jj - gg) == '0';
		ok &= get(a, ii + 2 + 2 * (g - 2 - 1) - gg, jj - gg) == '0';
		ok &= get(a, ii + 2 + 2 * (g - 2 - 1) - gg, jj + gg) == '0';
	}

	return ok ? 1 : 0;
}


inline int Dfs(vs& a, const int i, const int j)
{
	int ans;
	if(i == a.size() - 1)
	{
		ans = 0;
	}
	else if(a[i + 1][j] == '1')
	{
		ans = pdfs(a, i, j, __get);
	}
	else
	{
		ans = ddfs(a, i, j, __get);
	}

	clean(a, i, j);

	return ans;
}

int main()
{
	int t;
	scanf("%d\n", &t);

	for(int ti = 0; ti < t; ++ti)
	{
		int n, m;
		scanf("%d %d\n", &n, &m);

		vs a(n);

		for(int i = 0; i < n; ++i)
		{
			char cs[300];
			gets(cs);

			a[i] = cs;
		}

		int ans = 0;
		vi path;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(a[i][j] == '1')
				{
					ans += Dfs(a, i, j);
				}

		printf("%d\n", ans);
	}
}
