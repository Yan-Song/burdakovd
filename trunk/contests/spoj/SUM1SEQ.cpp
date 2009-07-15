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
const int inf=1000000000;
 
v64 solution;

i64 ggabs(i64 n)
{
	return n<0 ? -n : n;
}

bool rec(i64 n,i64 s)
{
	if(s>n*(n-1)/2) return false;
	if(s<-n*(n-1)/2) return false;
	if(n/2%2 != ggabs(s)%2) return false;

	if(n==1) return true;

	//int prev = solution.size();

	//if(rec(n-1,s))
	//	solution.push_back(0);

	if(s>=0)
	{
		assert(rec(n-1,s-(n-1)));
		solution.push_back(+1);
	}
	else
	{
		assert(rec(n-1,s+(n-1)));
		solution.push_back(-1);
	}

	return true;
}

void solve(i64 n, i64 s)
{
	solution.clear();
	if(rec(n,s))
	{
		i64 sum = 0;
		cout<<sum<<endl;
		for(int i=solution.size()-1; i>=0; i--)
		{
			sum += solution[i];
			cout<<sum<<endl;
		}
	}
	else
		cout<<"No"<<endl;

}

 
int main()
{
	//assert(false);
    i64 tc;
	cin>>tc;
	fo(i,0,tc)
	{
		i64 n,s;
		cin>>n>>s;
		solve(n,s);
	}
    return 0;
}
