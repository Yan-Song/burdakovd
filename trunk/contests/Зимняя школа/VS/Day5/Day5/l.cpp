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

#define sqr(x) ((x)*(x))
#pragma comment(linker,"/stack:64000000")


const int maxN = 2100;

double dp[maxN][maxN];


int main(){
//freopen("in.txt","r",stdin);
freopen("l.in","r",stdin);
freopen("l.out","w",stdout);
	int S,R;
	cin>>S>>R;

	if(S%2 == 1){
		printf("0");
		return 0;
	}	

	for(int i = 0; i < maxN;++i)
	{
		dp[i][0] = 0.0;
		dp[0][i] = 1.0;
	}

	for(int s = 2; s <= S; s+=2)
		for(int r = 1;  r <= R; ++r)
		{
			dp[s][r] = (s-1)*dp[s-2][r] + 2*r*dp[s][r-1];
			dp[s][r] /= s+2*r-1;
		}

	printf("%.9lf",dp[S][R]);

	return 0;
}