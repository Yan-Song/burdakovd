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


#pragma comment(linker,"/stack:64000000")

int N,R,K;

const int maxN = 300;
int x[maxN],y[maxN];

inline int sqr(int x) { return x*x; }


double dist(int i,int j){
	return sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j])+0.0);
}

double memo[300][300];

double f(int n,int k){


	if(n==0) return 0.0;


	
	//double d = dist(n,n-1);
	double& ret = memo[n][k];
	if(ret >= -0.5)
		return ret;
	ret = f(n-1,k) + dist(n,n-1);
	if(k>0){
		for(int i = 0; i < n; ++i){
		
			int ABx = x[n]-x[i];
			int ABy = y[n]-y[i];

			bool can = sqr(ABx) + sqr(ABy) <= R*R;

			for(int j = i+1; j < n && can; ++j){
				int ACx = x[j]-x[i];
				int ACy = y[j]-y[i];
				if(ABx*ACy - ABy*ACx > 0)
					can = false;
			}

			if(can)
				ret = min(ret,f(i,k-1)+dist(i,n));
		}

	}
	return ret;

}

int main(){
//freopen("in.txt","r",stdin);
freopen("k.in","r",stdin);
freopen("k.out","w",stdout);

	for(int i = 0; i < 300; ++i)
		for(int j = 0; j < 300; ++j)
			memo[i][j] = -1.0;
	scanf("%d %d %d",&N,&K,&R);
	for(int i = 0; i < N ; ++i)
		scanf("%d %d",&x[i],&y[i]);


	printf("%.5lf",f(N-1,K));

	return 0;
}