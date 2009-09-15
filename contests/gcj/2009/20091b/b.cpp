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
const int inf=1e9;
 

 
int main()
{
	freopen("e:\\in.txt", "r", stdin);
	freopen("e:\\out.txt", "w", stdout);

	int tc;
	cin>>tc;
	for(int cas=1; cas<=tc; ++cas) {
		string data;
		cin>>data;
		string orig = data, ans;
		if(next_permutation(data.begin(), data.end()))
			ans = data;
		else
		{
			ans = "";
			foreach(i,orig)
				if(orig[i]!='0')
					ans += orig[i];

			sort(ALL(ans));

			while(ans.size()<=orig.size())
				ans.insert(1,"0");
		}
		cout<<"Case #"<<cas<<": "<<ans<<endl;
	}

    return 0;
}
