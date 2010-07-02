#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <map>


using namespace std;

typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef pair<int,int> pii;
typedef long long i64;

const int inf = 1<<26;
const double eps = 1e-9;


#pragma comment(linker,"/stack:256000000")

//#define FOR(i,start,stop) for(int i = start; i < stop; ++i) 
const int maxN = 17;

double w[maxN][maxN];

i64 x[maxN],y[maxN];
int N;

inline i64 sqr(i64 b) { return b*b;}



inline double dist(int i,int j){
	return sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j])+0.0);
}

int begin;
int M;

double f[16][16][1<<16];
double cycles[1<<17];
//bool was[16][16][1<<16];


inline int bit(int x,int i){
	return x&(1<<i);
}
/*
double f(int begin,int end,int mask){
	if(mask == 0){
		return w[begin][end];
	}

	if(was[begin][end][mask])
		return memo[begin][end][mask];

	was[begin][end][mask] = true;


	double ret = inf;

	for(int i = 0; i < N; ++i){
		if(mask&(1<<i)){
			int newmask = mask^(1<<i);
			ret = min(ret,f(i,end,newmask)+w[begin][i]);
		}
	}
	return memo[begin][end][mask] = ret;
}
*/


int main(){
	//freopen("in.txt","r",stdin);
	freopen("j5.in","r",stdin);
	freopen("j5.out","w",stdout);

	cin>>N;
	int orig_N = N;

	for(int i =0; i < N; ++i)
		cin>>x[i]>>y[i];

	for(int i = 0; i < N; ++i)
		for(int j = 0; j < N; ++j)
			w[i][j] = dist(i,j);

	

	for(int j = 0; j < (1<<N); ++j)
		cycles[j] = 1e9;

	

	N = min(N,16);	

	


	//memset(was,false,sizeof(was));

	int maxMask  = 1<<N;

	for(int i = 0; i < N;++i)
		for(int j = 0; j < N; ++j)
			for(int k = 0; k < maxMask;++k)
				f[i][j][k] = inf;


	for(int i = 0;  i < N; ++i)
		f[i][i][1<<i] = 0;


	

	for(int mask = 1; mask < maxMask; ++mask){
		for(int u = 0; u < N; ++u)
			if(mask&(1<<u))
				for(int v = u+1; v < N; ++v)
					if(mask&(1<<v))
					{
						for(int k = 0; k < N; ++k)
							if(k!=u && (mask & (1<<k)) )
							{
						//	cerr<<"#1";
								double d = w[u][k] + f[k][v][mask^(1<<u)];
								if(f[u][v][mask] > d)
									f[u][v][mask] = d;
								
						//	cerr<<"#2";
							}	
							if(cycles[mask] > f[u][v][mask] + w[u][v])
								cycles[mask] = f[u][v][mask] + w[u][v];
							f[v][u][mask] = f[u][v][mask];
					}
	}
	
	

	

	N = orig_N;

	maxMask = 1<<N;
	
	if(N == 17){

		for(int mask = 0; mask < maxMask; ++mask)
			if(mask & ( 1 << 16)){
				int newmask = mask^(1<<16);
				for(int u = 0; u < 16; ++u)
					if(mask & (1<<u))
						for(int v = u+1 ; v < 16; ++v)
							if(mask&(1<<v)){
								double d = cycles[newmask] + w[u][16] + w[16][v] - w[u][v];
								if(cycles[mask] > d)
									cycles[mask] = d;
							}

			}
	}
	


	int Q;
	cin>>Q;
	int ai;

	for(int i = 0; i < Q;++i){
		scanf("%d",&M);
		//++cur;
		int mask = 0;
		for(int i = 0; i < M;++i)
		{
			scanf("%d",&ai);
			mask|=1<<(ai-1);
			begin = ai-1;
		}
		//mask ^= (1<<(begin));
		printf("%.9lf\n",cycles[mask]);
	}



	return 0;
}