#line 124 "TwistedMatrix.cpp"
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
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
 
const double pi=2*acos(0.0);
const i64 inf=1000000000;

class TwistedMatrix {
	public:
	
	void rotate(char& a, char& b, char& c, char& d) const
	{
		char t = a;
		a = b;
		b = c;
		c = d;
		d = t;
	}
	
	void rotate(vs& m, int i, int j, bool clock) const
	{
		if(clock)
			rotate(m[i][j], m[i][j+1], m[i+1][j+1], m[i+1][j]);
		else
			rotate(m[i][j], m[i+1][j], m[i+1][j+1], m[i][j+1]);
	}
	
	bool match(const vs& pattern, const vs& m) const
	{
		foreach(i,pattern)
			foreach(j, pattern[i])
				if(pattern[i][j]!='?' && m[i][j]!='?' && pattern[i][j]!=m[i][j])
					return false;
		
		return true;
	}
	
	vector<string> lex(const vs& m, const vs& known)
	{
		vs ans = m;
		foreach(i,ans)
			foreach(j,ans[i])
				if(ans[i][j]=='?')
					if(known[i][j]=='?')
						ans[i][j] = '0';
					else
						ans[i][j] = known[i][j];
		return ans;
	}
	
	vector <string> solve(vector <string> A, vector <string> B) {
		vs smin;
		bool found=false;
		
		for(int i=0; i+1<A.size(); ++i)
			for(int j=0; j+1<A[0].size(); ++j)
				for(int dir=0; dir<2; ++dir)
				{
					vs c = A;
					rotate(c,i,j,dir==1);
					
					if(match(B, c))
					{
						c = lex(c, B);
						//debug(c[0]);
						//debug(c[1]);
						
						if(!found || c<smin)
						{
							smin = c;
							found = true;
						}
					}
				}
		
		return found  ? smin  : vs(); 
	}
};




// Powered by FileEdit
// Powered by moj 4.12 [modified TZTester]
// Powered by CodeProcessor
