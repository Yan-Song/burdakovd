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
#define fosz(i,s,x) for(unsigned int i=s; i<x.size(); i++)
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
 
vector<string> _map;
int islands;
int n, m;

int floodfill(int i, int j)
{
	if(_map[i][j] != '#') // undiscovered land
		return 0;

	_map[i][j] = '@'; // discovered land
	
	int ans = 1;
	for(int di=-1; di<2; ++di)
		for(int dj=-1; dj<2; ++dj)
			ans += floodfill(i + di, j + dj);

	return ans;
}

int main()
{
    int tc;
	cin>>tc;
	fo(tn,0,tc)
	{
		cin>>n>>m;
		_map = vector<string>(n);

		foreach(i, _map)
			cin>>_map[i];

		int islands = 0;

		foreach(i, _map)
			foreach(j, _map[i])
				if(floodfill(i, j) > 0)
					++islands;

		cout<<islands<<endl;
	}
    return 0;
}
