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
	vector<vector<string> > names(n), names1(n);
	for(int i = 0; i < n; ++i)
	{
		vector<string> _(3);
		for(int j = 0; j < 3; ++j)
			cin >> _[j];
		sort(_.begin(), _.end());
		names1[i] = _;
	}
	for(int i = 0; i < n; ++i)
	{
		int d;
		cin >> d;
		names[i] = names1[d-1];
	}

	string current = "";
	vector<string> ans;
	for(int i = 0; i < n; ++i)
	{
		vector<string>::const_iterator it = names[i].begin();

		while(it != names[i].end() && *it < current)
			++it;

		if(it == names[i].end())
		{
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
		else
		{
			ans.push_back(*it);
			current = *it;
		}
	}

	for(int i = 0; i < ans.size(); ++i)
	{
		cout << ans[i] << endl;
	}
	return 0;
}
