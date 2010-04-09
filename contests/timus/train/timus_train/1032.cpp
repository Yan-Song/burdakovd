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

int main()
{
	int n;
	cin >> n;
	vector<int> numbers(n);
	for(int i = 0; i < n; ++i)
		cin >> numbers[i];

	vector<int> dp(n, -1);
	dp[0] = 0;

	for(int i = 0; i < n && dp[0] == 0; ++i)
	{
		int cur = numbers[i];
		vector<int> prev = dp;
		for(int j = 0; j < n; ++j)
		{
			if(prev[j] <= 0)
			{
				int m = (j - cur) % n;
				
				if(m < 0)
					m += n;

				if(prev[m] != -1)
				{
					dp[j] = cur;
				}
			}
		}
	}

	if(dp[0] == 0)
	{
		cout << 0 << endl;
	}
	else
	{
		vector<int> ans;

		int s = 0;
		do
		{
			ans.push_back(dp[s]);
			s = ((s - dp[s]) % n + n) % n;
		} while(s != 0);

		cout << ans.size() << endl;
		for(int i = 0; i < ans.size(); ++i)
			cout << ans[i] << endl;
	}

	return 0;
}
