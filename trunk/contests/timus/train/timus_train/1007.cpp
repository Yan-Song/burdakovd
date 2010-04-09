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
	
	string s;
	while(cin >> s)
	{
		if(s.size() == n)
		{
			int p = 0;
			for(int i = 0; i < n; ++i)
				if(s[i] == '1')
				{
					p += i + 1;
				}

			p %= n + 1;

			if(p != 0)
			{
				s[p - 1] = '0';
			}

			cout << s << endl;
		}
		else if(s.size() == n - 1)
		{
			vi psum(n), pcount(n);
			for(int i = 1; i < n; ++i)
			{
				if(s[i - 1] == '1')
				{
					pcount[i] = pcount[i - 1] + 1;
					psum[i] = psum[i - 1] + i;
				}
				else
				{
					pcount[i] = pcount[i - 1];
					psum[i] = psum[i - 1];
				}
			}

			for(int i = 0; i < n; ++i)
			{
				const int will_0 = psum[n - 1] + (pcount[n - 1] - pcount[i]);
				const int will_1 = will_0 + i + 1;

				if(will_0 % (n + 1) == 0)
				{
					s.insert(s.begin() + i, '0');
					break;
				}

				if(will_1 % (n + 1) == 0)
				{
					s.insert(s.begin() + i, '1');
					break;
				}
			}

			cout << s << endl;
		}
		else if(s.size() == n + 1)
		{
			vi psum(n + 2, 0), pcount(n + 2, 0);

			for(int i = 1; i <= n + 1; ++i)
			{
				if(s[i - 1] == '1')
				{
					pcount[i] = pcount[i - 1] + 1;
					psum[i] = psum[i - 1] + i;
				}
				else
				{
					pcount[i] = pcount[i - 1];
					psum[i] = psum[i - 1];
				}
			}

			for(int i = 0; i < n + 1; ++i)
			{
				const int will = psum[n + 1] - (s[i] == '1' ? i + 1 : 0) - (pcount[n + 1] - pcount[i + 1]);

				if(will % (n + 1) == 0)
				{
					s.erase(i, 1);
					break;
				}
			}

			cout << s << endl;
		}
		else
			throw 0;
	}

	return 0;
}
