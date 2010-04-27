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
#include <list>
 
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

struct ob
{
	int l, r;
	int number;

	ob(int numberr, int ll, int rr) : number(numberr), l(ll), r(rr)
	{
	}

	ob() : number(0), l(0), r(0)
	{
	}

	inline int rleft(const int h) const
	{
		return h - l;
	}

	inline int rright(const int h) const
	{
		return h - r;
	}
};
 
int main()
{
	int h, n;
	cin >> h >> n;

	vector< vector<int> > lefts(h + 1);

	int delta = 1000000;
	ob fst;
	for(int i = 0; i < n; ++i)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		ob o(i + 1, l, r);

		if(i == 0)
			fst = o;

		if(l - r != delta && delta != 1000000)
		{
			cout << 0 << endl;
			return 0;
		}

		delta = l - r;

		lefts[o.l].push_back(o.number);
	}
	
	fst = ob(lefts[fst.l].back(), fst.l, fst.l - delta);
	lefts[fst.l].pop_back();

	list<int> ans;
	ans.push_back(fst.number);

	int needl = fst.r, needr = fst.l;

	for(int i = 1; i < n; ++i)
	{
		ob next;
		bool right, reverse = false;
		if(!lefts[needl].empty())
		{
			next = ob(lefts[needl].back(), needl, needl - delta);
			right = true;
		}
		else if(h - needl + delta >= 0 && h - needl + delta < lefts.size() && !lefts[h - needl + delta].empty())
		{
			next = ob(lefts[h - needl + delta].back(), h - needl + delta, h - needl);
			right = true;
			reverse = true;
		}
		else if(needr + delta >= 0 && needr + delta < lefts.size() && !lefts[needr + delta].empty())
		{
			next = ob(lefts[needr + delta].back(), needr + delta, needr);
			right = false;
		}
		else if(!lefts[h - needr].empty())
		{
			next = ob(lefts[h - needr].back(), h - needr, h - needr - delta);
			right = false;
			reverse = true;
		}
		else
		{
			cout << 0 << endl;
			return 0;
		}

		lefts[next.l].pop_back();

		if(right)
		{
			if(reverse)
			{
				ans.push_back(-next.number);
				needl = next.rleft(h);
			}
			else
			{
				ans.push_back(next.number);
				needl = next.r;
			}
		}
		else
		{
			if(reverse)
			{
				ans.push_front(-next.number);
				needr = next.rright(h);
			}
			else
			{
				ans.push_front(next.number);
				needr = next.l;
			}
		}
	}


	for(list<int>::const_iterator it = ans.begin(); it != ans.end(); ++it)
	{
		printf("%s%d", (it == ans.begin() ? "" : " "), *it);
	}

	printf("\n");

	return 0;
}
