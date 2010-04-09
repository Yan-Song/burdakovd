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

 
int main()
{
	int n;
	cin >> n;

	vi ans;
	for(int i = n; i >= 1 && n; --i)
	{
		int s = 0;
		for(int j = i; j > 0; j /= 10)
			s += j % 10;

		if(s <= n)
		{
			ans.push_back(i);
			n -= s;
		}
	}
	
	cout << ans.size() << endl << ans << endl;

	return 0;
}
