#line 102 "TheLockDivOne.cpp"
#include <ctime>
#include <float.h>
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
const i64 inf=1000000000;

class TheLockDivOne {
	public:
		i64 pow2[62];
	i64 ln(i64 n)
	{
		int ans=0;
		while(n>0)
		{
			++ans;
			n/=2;
		}
		return ans;
	}
	i64 num(i64 n)
	{
		i64 lvl = ln(n);
		if(lvl == 0) return 0;
		i64 ans = i64(1)<<(lvl-1);
		ans += num((n-1)%pow2[lvl-1]);
	}
	i64 f(i64 from, i64 to, i64 k)
	{
		i64 _from(from), _to(to);
		if(from>to) return 0;
		if(k==0) return 0;
		
		i64 ans = 0;
		if(from<pow2[k-1] && to<pow2[k-1])
		{
			return f(from, to, k-1);
		}
		from = max(from, pow2[k-1]);
		from = (from-1) % pow2[k-1];
		to = (to-1) % pow2[k-1];

		
		if(from<=to)
			ans = max(ans, f(from, to, k-1));
		else
		{
			ans = max(ans, f(from, pow2[k-1]-1, k-1));
			ans = max(ans, f(0, to, k-1));
		}
		ans+=pow2[k-1];
		//cout<<"f(from="<<_from<<", to="<<_to<<", bits="<<k<<") = "<<ans<<endl;
		return ans;
			
	}
	string password(int n, long long k) {
		vi pass(n, 0);
		pow2[0] = 1;
		for(int i=0; i<60 ;i++) 
			pow2[i+1] = 2*pow2[i];
		i64 ans =  f(0,k-1,n);
		string sans = "";
		do
		{
			sans = string(1,'0'+char(ans%2)) + sans;
			ans/=2;
		}
		while(ans>0);
		while(sans.size()<n)
			sans = '0' + sans;
		return sans;
	}
};




// Powered by FileEdit
// Powered by moj 4.12 [modified TZTester]
// Powered by CodeProcessor
