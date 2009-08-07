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
#define assert(b) {if(!(b)) throw "o_O";}

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
 
vector<i64> vcache[256][16];
i64 ccache[256][16];

i64 count(i64 m, i64 n)
{
	assert(m>=0);
	assert(n>=0);

	if(m==0)
		return 1;

	if(n==0)
		return 0;

	if(ccache[m][n]!=-1)
		return ccache[m][n];
	else
	{
		i64& ans = ccache[m][n];
		ans = 0;
		for(int first = 0; first * n <= m; ++first)
			ans += count(m - first * n, n - 1);

		return ans;
	}
}

vector<i64> p(i64 m, i64 n, i64 k)
{
	assert(m>=0);

	if(m==0)
	{
		vector<i64> ans;
		fo(i,0,n)
			ans.push_back(0);
		return ans;
	}

	/*if(vcache[m][n].size()!=0)
		return vcache[m][n];*/

	i64 was = 0;

	for(i64 first = 0; first * n <= m; ++first)
	{
		i64 left = m - first * n;
		i64 d = count(left, n-1);
		if(was + d <= k)
		{
			was += d;
		}
		else
		{
			assert(was<=k);
			assert(was+d>k);
			vector<i64> t = p(left, n - 1, k-was);
			vector<i64> ans;
			ans.push_back(first);
			foreach(i, t)
				ans.push_back(first + t[i]);
			//vcache[m][n] = ans;
			return ans;
		}
	}
	throw "o_O";
}

int main()
{
	mset(ccache, -1);
	mset(vcache, 0);
    int t;
	cin>>t;
	fo(tt, 0, t)
	{
		i64 m,n,k;
		cin>>m>>n>>k;
		vector<i64> ans = p(m-n,n,k-1);
		foreach(i, ans)
			cout<<(i?" ":"")<<ans[i] +1;
		cout<<endl;
	}
    return 0;
}
