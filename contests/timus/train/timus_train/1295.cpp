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

// только для натуральных чисел
struct Long
{
	vi data;

	Long(int n) : data()
	{
		while(n)
		{
			data.push_back(n % 10);
			n /= 10;
		}
	}

	Long(const vi& v) : data(v)
	{
	}

	inline int dig(const int id) const
	{
		return id < data.size() ? data[id] : 0;
	}
};

Long& operator +=(Long& x, const Long& y)
{
	int _ = 0;
	const int n = max(x.data.size(), y.data.size());
	x.data.resize(n);

	for(int i = 0; i < n; ++i)
	{
		_ += x.dig(i) + y.dig(i);
		x.data[i] = _ % 10;
		_ /= 10;
	}

	if(_)
	{
		x.data.push_back(_);
	}

	return x;
}

Long operator *(const Long& a, const Long& b)
{
	const int an = a.data.size(), bn = b.data.size();

	const int n = an + bn;

	vi ans(n);

	for(int ai = 0; ai < an; ++ai)
	{
		int _ = 0;

		for(int bi = 0; bi < bn; ++bi)
		{
			ans[ai + bi] += a.data[ai] * b.data[bi];
			ans[ai + bi + 1] += ans[ai + bi] / 10;
			ans[ai + bi] %= 10;
		}
	}

	if(ans.back() == 0)
	{
		ans.pop_back();
	}

	while(ans.size() > 10)
	{
		ans.pop_back();
	}

	return Long(ans);
}

template<class T>
T fastpow(const T& x, const int pow)
{
	if(pow == 0)
	{
		return T(1);
	}
	else if(pow % 2)
	{
		return x * fastpow(x, pow - 1);
	}
	else // if(pow % 2 == 0)
	{
		const Long l = fastpow(x, pow / 2);
		return l * l;
	}
}
 
int main()
{
	Long x(0);

	int n;
	cin >> n;

	x += fastpow(Long(2), n);
	x += x * x;
	x += fastpow(Long(3), n);
	x += Long(1);

	int ans = 0;
	while(x.data[ans] == 0)
	{
		++ans;
	}

	cout << ans << endl;

	return 0;
}
