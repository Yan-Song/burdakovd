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
const i64 MOD = 2370823708;

i64 sqr(i64 x)
{
	return x*x%MOD;
}

i64 ipow(i64 x, i64 y)
{
	if(y==0) return 1;
	if(y%2) return x*ipow(x,y-1)%MOD;
	else return sqr(ipow(x,y/2))%MOD;
}

i64 C(i64 k, i64 n)
{
	i64 ans = 1;
	for(int i=k+1; i<=n; i++)
		ans *= i;
	for(int i=1; i<=n-k; i++)
		ans /= i;
	return ans;
}

i64 f(i64 n,i64 k,i64 K)
{
	if(K==1) return 1;

	i64 ans = ipow(K,n);
	for(int i=1; i<k; i++)
	{
		ans -= C(i,K)*f(n,i,i);
		ans %= MOD;
		ans += MOD;
		ans %= MOD; // now ans >=0
	}
	return ans%MOD;
}

i64 solve(i64 m, i64 n, i64 k)
{
	return ipow(f(n,k,7),m);
}

int main()
{
	//cout<<C(1,3)<<endl;
	//return 0;
    i64 m,n,k;
	while(cin>>m>>n>>k)
		cout<<solve(m,n,k)<<endl;
    return 0;
}
