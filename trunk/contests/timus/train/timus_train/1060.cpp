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

template<typename T>
inline istream& operator >>(istream& is, vector<T>& v)
{
	for(int i = 0; i < v.size(); ++i)
		is >> v[i];

	return is;
}

template<typename T>
inline ostream& operator <<(ostream& os, const vector<T>& v)
{
	for(int i = 0; i < v.size(); ++i)
		os << (i ? " " : "") << v[i];

	return os;
}

typedef string strin;
typedef double doble;
#define cot cout

void reverse(vs& field, const int x, const int y)
{
	if(x >= 0 && x < 4 && y >= 0 && y < 4)
		field[x][y] = 'w' + 'b' - field[x][y];
}

void reverse(vs& field, int c)
{
	const int x = c % 4, y = c / 4;

	reverse(field, x + 1, y);
	reverse(field, x - 1, y);
	reverse(field, x, y + 1);
	reverse(field, x, y - 1);
	reverse(field, x, y);
}

bool nice(vs field, int mask)
{
	for(int i = 0; i < 16; ++i)
		if((1 << i) & mask)
		{
			reverse(field, i);
		}

	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			if(field[i][j] != field[0][0])
				return false;

	return true;
}

int ones(int mask)
{
	int ans = 0;
	while(mask != 0)
	{
		++ans;
		mask &= mask - 1;
	}

	return ans;
}

int main()
{
#ifndef HOME_PC
	//freopen("INPUT.TXT", "r", stdin);
	//freopen("OUTPUT.TXT", "w", stdout);
#endif

	vs field(4);
	cin >> field;

	int best = 17;
	for(int i = 0; i < 1 << 16; ++i)
	{
		if(nice(field, i))
		{
			//debug(i);
			//debug(ones(i));
			best = min(best, ones(i));
		}
	}

	if(best == 17)
		cout << "Impossible" << endl;
	else
		cout << best << endl;

	return 0;
}
