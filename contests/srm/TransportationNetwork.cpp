#line 91 "TransportationNetwork.cpp"
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
//#include <list>

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

#define sqr(x) ((x)*(x))

class TransportationNetwork {
	vi X, Y;
	double rcost, acost;
	
	inline double cost(int a, int b)
	{
		if(a == X.size()) return acost;
		if(b == X.size()) return acost;
		double ans = sqrt(sqr(X[a]-X[b]) + sqr(Y[a]-Y[b])) * rcost;
//		cout<<"cost("<<a<<", "<<b<<") = "<<ans<<endl;
		return ans;
	}
	
	double solve(int n)
	{
		vector<queue<pair<double,int> > > dists;
		double ans=0;
		for(int a=0; a<n; ++a)
		{
			vector<pair<double,int> > h;
			for(int b=0; b<n; ++b)
				h.push_back(pair<double,int>(cost(a,b), b));
			
			sort(h.begin(), h.end());
			
			queue<pair<double,int> > qq;
			foreach(jj,h)
				qq.push(h[jj]);
				
			dists.push_back(qq);
		}
	
		vector<bool> used(n, false);
		
		used[0] = true;
		
		for(int i=1; i<n; ++i)
		{
			int mina=-1, minb=-1;
			double mind = 1e9;
			for(int a=0; a<n; ++a)
				if(used[a])
				{
				
				while(!dists[a].empty() && used[dists[a].front().second])
					dists[a].pop();
				
				if(!dists[a].empty())
				{
					int b = dists[a].front().second;
					double d = dists[a].front().first;
					
					if(d<mind)
					{
						mind=d;
						mina=a;
						minb=b;
					}
				}
				}
			
			assert(mina!=-1);
			ans += mind;
			
			used[minb] = true;
			dists[mina].pop();
			
			//cout<<"["<<n<<"] connect "<<mina<<" with "<<minb<<": "<<mind<<endl;
					
		}
		
		return ans;
	}
	
	public:
	double minCost(vector <int> cityX, vector <int> cityY, double roadCost, double airportCost) {
        X = cityX;
        Y = cityY;
        rcost = roadCost;
        acost = airportCost;
        double witha = solve(X.size()+1);
        double withouta = solve(X.size());
       // debug(witha);
        //debug(withouta);
        return min(witha, withouta);
	}
};




// Powered by FileEdit
// Powered by moj 4.12 [modified TZTester]
// Powered by CodeProcessor
