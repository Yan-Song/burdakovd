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

int M,D,N;
const int maxN = 510;
const int maxM = 210;

int L[maxN];

int f[2][maxN][maxN];

int main(){
//freopen("in.txt","r",stdin);
freopen("m.in","r",stdin);
freopen("m.out","w",stdout);

	memset(f,-1,sizeof(f));

	

	cin>>M>>D>>N;
	for(int i = 0; i < N; ++i)
		cin>>L[i+1];

	int cur = 0;
	int prev = 1;

//	for(int i = 0; i <= M;++i)
//		f[i][0][0] = D;




	for(int m = 1; m <= M; ++m){
		swap(cur,prev);
		memset(f[cur],-1,sizeof(f[cur]));
		for(int i = 0; i <= N;++i)
			f[prev][i][0] = f[cur][i][0] = D;
		for(int n = 1; n <= N; ++n)
			for(int n1 = 1; n1 <= n; ++n1)
			{
				if(f[prev][n][n1]!=-1)
					f[cur][n][n1] = D;
				else
					f[cur][n][n1] = max(f[cur][n-1][n1],f[cur][n-1][n1-1]-L[n]);
			}
	}

	int ans = 0;
	for(int j = 0; j <= N;++j)
		if(f[cur][N][j]!=-1)
			ans = max(ans,j);

	cout<<ans<<endl;

	


	return 0;
}