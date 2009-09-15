#line 88 "TheCardShufflingDivOne.cpp"
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

class TheCardShufflingDivOne {
	public:
	int shuffle(int n, int left, int right) {
		int l = 0, m = n, r = 0, h = 0;
		char deck = 'm';
		int pos = 1;

		//cout<<deck<<pos<<endl;
		// h = 0

		if(m % 2 != 0)  // последн€€ карта
		{
			--m;
			++h;
			deck = 'h';
			pos = 1;
		}

		//cout<<deck<<pos<<endl;
		while(m > 0)
		{
			assert(deck=='h' || deck=='m');
			assert(l==0 && r==0);

			r = h / 2;
			h -= r;
			if(deck == 'h')
				if(pos <= r)
				{
					deck = 'r';
					pos = r + 1 - pos;
				}
				else
					pos -= r;

			l = h;
			h = 0;
			if(deck == 'h')
			{
				deck = 'l';
				pos = l + 1 - pos;
			}
			//cout<<deck<<pos<<endl;


			assert(m >= 2);
			if(deck=='r')
				++pos;
			else if(deck == 'm' && pos == 1)
				deck = 'r';
			--m; ++r;

			assert(m >= 1);
			if(deck=='l')
				++pos;
			else if(deck == 'm' && pos == 1)
				deck = 'l';
			--m; ++l;
			

			//cout<<deck<<pos<<endl;
			if(deck == 'r')
			{
				pos = pos + right;
				--pos;
				pos%=r;
				++pos;
			}
	
			if(deck == 'l')
			{
				pos = pos + left;
				--pos;
				pos%=l;
				++pos;
			}

			//cout<<deck<<pos<<endl;
			assert(l==r || l==r+1);

			assert(h==0);

			if(deck == 'l')
			{
				deck = 'h';
				if(l==r)
					pos = (l+r) + 1 - pos*2;
				else
					pos = (l+r) + 2 - pos*2; // same=)

			}

			if(deck == 'r')
			{
				deck = 'h';
				if(l==r)
					pos = (l+r) + 2 - pos*2;
				else
					pos = (l+r) + 1 - pos*2;
			}

			h = l+r;
			l=0;
			r=0;

			//cout<<deck<<pos<<endl;
		}
		assert(deck=='h');
		return pos;
	}
};




// Powered by FileEdit
// Powered by moj 4.12 [modified TZTester]
// Powered by CodeProcessor
