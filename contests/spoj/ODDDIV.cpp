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
 
i64 DC[110000];
vector< vector<i64> > numbers(10000);
 
int main()
{
	for(i64 i=1; i<101000; ++i)
	{
		//cout<<i<<endl;
		i64 n = i;
		i64& dc = DC[i];
		dc = 1;
		for(i64 d = 2; d * d <= n; d++)
		{
			i64 _dc = 0;
			while(n % d == 0)
			{
				n /= d;
				++_dc;
			}
			dc *= (2*_dc+1);
		}
		if(n!=1)
			dc *= 3;

		numbers[dc].push_back(i*i);
	}

	//cout<<"precalc done"<<endl;

	

	int c;
	cin>>c;
	fo(cc,0,c)
	{
		int k, cnt=0;
		i64 l, h;
		scanf("%d %lld %lld", &k, &l, &h);
		vector<i64>::iterator lower = lower_bound(ALL(numbers[k]), l);
		vector<i64>::iterator upper = upper_bound(ALL(numbers[k]), h);
		cnt = upper - lower;
		printf("%d\n", cnt);
	}
    return 0;
}
