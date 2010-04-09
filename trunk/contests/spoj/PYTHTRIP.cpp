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

template<typename T>
inline T sqr(T x)
{
	return x * x;
}


int main()
{
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i)
	{
		int a, b;
		cin >> a >> b;

		const int c2 = sqr(a) + sqr(b);
		const double cc = sqrt(1.0 * c2);

		const int cand1 = floor(cc);
		const int cand2 = ceil(cc);

		if(sqr(cand1) == c2)
			cout << "YES " << int(cand1) << endl;
		else if(sqr(cand2) == c2)
			cout << "YES " << int(cand2) << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}
