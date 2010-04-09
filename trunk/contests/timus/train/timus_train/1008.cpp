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
	for(vector<T>::size_type i = 0; i < v.size(); ++i)
		is >> v[i];

	return is;
}

template<typename T>
inline ostream& operator <<(ostream& os, const vector<T>& v)
{
	for(vector<T>::size_type i = 0; i < v.size(); ++i)
		os << (i ? " " : "") << v[i];

	return os;
}

typedef string strin;
typedef double doble;
#define cot cout

 
int main()
{
#ifndef HOME_PC
	//freopen("INPUT.TXT", "r", stdin);
	//freopen("OUTPUT.TXT", "w", stdout);
#endif

	strin s;
	getline(cin, s);
	
	if(s.find(' ') == strin::npos)
	{
		int n;
		istringstream is(s);
		is >> n;
		vpii v(n);
		cin >> v;

		set<pii> s(v.begin(), v.end());

		const pii first = *std::min_element(s.begin(), s.end());

		cout << first << endl;
		s.erase(first);

		queue<pii> q;
		q.push(first);

		while(!q.empty())
		{
			//cout << '[' << q.front() << "]: ";
			vector< pair<char, pii> > candidates;

			candidates.push_back(make_pair('R', pii(q.front().first + 1, q.front().second)));
			candidates.push_back(make_pair('T', pii(q.front().first, q.front().second + 1)));
			candidates.push_back(make_pair('L', pii(q.front().first - 1, q.front().second)));
			candidates.push_back(make_pair('B', pii(q.front().first, q.front().second - 1)));

			for(int i = 0; i < candidates.size(); ++i)
				if(s.count(candidates[i].second))
				{
					s.erase(candidates[i].second);
					q.push(candidates[i].second);

					cout << candidates[i].first;
				}

			q.pop();

			cout << (q.empty() ? '.' : ',') << endl;
		}
	}
	else
	{
		istringstream is(s);
		pii first;
		is >> first;

		queue<pii> q;
		q.push(first);

		list<pii> l;

		while(!q.empty())
		{
			l.push_back(q.front());

			string s;
			cin >> s;

			for(int i = 0; i < s.size(); ++i)
			{
				if(s[i] == 'R')
					q.push(pii(q.front().first + 1, q.front().second));

				if(s[i] == 'T')
					q.push(pii(q.front().first, q.front().second + 1));

				if(s[i] == 'L')
					q.push(pii(q.front().first - 1, q.front().second));

				if(s[i] == 'B')
					q.push(pii(q.front().first, q.front().second - 1));
			}

			q.pop();
		}

		vpii v(l.size());
		copy(l.begin(), l.end(), v.begin());

		sort(ALL(v));

		cout << v.size() << endl;
		for(int i = 0; i < v.size(); ++i)
			cout << v[i] << endl;

	}

	return 0;
}
