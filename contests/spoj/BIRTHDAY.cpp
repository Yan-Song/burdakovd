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
 
class shiftv
{
	vi data;
	int sh;
public:
	shiftv(int n): data(n,0), sh(0) {};
	int& operator[](int n)
	{
		n = (n-sh+2*data.size()) % data.size();
		return data[n];
	}
	void operator++()
	{
		++sh;
	}
	int size()
	{
		return data.size();
	}
};

inline int amin(int x, int y)
{
	if(abs(x)<abs(y)) return x;
	if(abs(x)==abs(y)) return max(x,y);
	return y;
}

inline int dist(int start,int finish, int n)
{
	return amin(amin(finish-start,n+finish-start), -n+finish-start);
}


int main()
{
    int n;
	cin>>n;
	vi p(n);
	foreach(i,p)
	{
		scanf("%d", &p[i]);
		--p[i];
	}

	shiftv counts(n);
	
	int positiveCount=0,negativeCount=0,sum=0; // positiveCount really includes "0"
	foreach(i,p)
	{
		int d = dist(i,p[i],n);
		//debug(i);
		//debug(d);
		++counts[d];
		if(d<0) ++negativeCount;
		else ++positiveCount;
		sum += abs(d);
	}

	int ans = sum;
	int limit = n/2 + 1;
	for(int i=0; i<n; i++)
	{
		//vdebug(counts);
		//debug(sum);
		
		sum += positiveCount;
		sum -= negativeCount;
		assert(sum>=0);
		++counts;
		int overflowCount = counts[limit];
		int replacement = limit - n;
		sum += overflowCount * (abs(replacement)-abs(limit));

		ans = min(ans,sum);

		int nullCount = counts[0];
		positiveCount += nullCount;
		negativeCount -= nullCount;

		positiveCount -= overflowCount;
		negativeCount += overflowCount;

	
	}

	cout<<ans<<endl;

    return 0;
}
