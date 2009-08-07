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
#define forletter(c) for(char c='A'; c<='Z'; ++c)

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
const int MOD = 1000000007;

struct CCache
{
    int cache[26];

	inline int& operator[](char j)
	{
		return cache[j-'A'];
	}
};

int cache[101000];
// next[i][c] - сама€ ранн€€ позици€ символа с начина€ с i
CCache next[101000];
string s;
 
int main()
{
	//freopen("e:\\var\\pp.txt", "r", stdin);
    int t;
	scanf("%d\n", &t);
	fo(tt,0,t)
	{
		char s[101000];
		scanf("%s", s);
		//s = string(cs);
		int n = strlen(s);
		//cout<<"<"<<s<<">"<<endl;
		mset(cache, -1);

		CCache cnext;
		forletter(c)
			cnext[c] = n;

		// next[i][char] - первое вхождение символа char в строку, начина€ с i включительно
		next[n] = cnext;
		for(int j=n-1; j>=0; --j)
		{
			cnext[s[j]] = j;
			next[j] = cnext;
		}

		// cache[start] - количество уникальных подпоследовательностей (в том  числе и пустых),
		// первый символ которых расположен
		// не ранее позиции start
		cache[n] = 1; // пуста€

		// cachesum - это количество уникальных подпоследовательностей (не пустых)
		// первый символ которых расположен _после_ start
		i64 cachesum = 0;

		for(int start=n-1; start>=0; --start)
		{
			// в этом цикле вычисл€ем cache[start]

			/// <magic>
			char c = s[start];

			// 
			int oldnextpos = next[start+1][c];
			int olddelta = oldnextpos == n ? 0 : cache[oldnextpos+1];
			cachesum -= olddelta;
			
			int newnextpos = next[start][c]; // == start
			int newdelta = newnextpos == n ? 0 : cache[newnextpos+1];  // == cache[newnextpos+1]
			cachesum += newdelta;
			/// </magic>

			cache[start] = (1 + cachesum) % MOD;

		}
		
		i64 ans = cache[0];		

		printf("%lld\n", ans);
	}
    return 0;
}
