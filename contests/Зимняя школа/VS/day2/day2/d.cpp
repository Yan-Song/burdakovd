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

#pragma comment(linker,"/stack:64000000")

typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef pair<int,int> pii;

/*
class Fenwick1d{
	const int maxN = 1050;
	int a[maxN];
	
	void update(int i,int x)
	{

}
*/
/*
template<int maxN,int neutral> class SegmentTree1d{
	int a[2*maxN+1];



};
*/

const int maxN = 1<<7;

int a[maxN][maxN][maxN];
int f[maxN][maxN][maxN];

inline int sum(int i1,int i2,int j1,int j2,int k1,int k2){
	//return f[i2][j2] - f[i1-1][j2] - f[i2][j1-1] + f[i1-1][j1-1];
	return f[i2][j2][k2] - f[i1-1][j2][k2] - f[i2][j1-1][k2] - f[i2][j2][k1-1]
						+ f[i1-1][j1-1][k2] + f[i1-1][j2][k1-1] + f[i2][j1-1][k1-1]
						- f[i1-1][j1-1][k1-1];
						
}

int main(){
//freopen("in.txt","r",stdin);
freopen("d2.in","r",stdin);
freopen("d2.out","w",stdout);

	int n,m,K;
	scanf("%d %d %d",&n,&m,&K);
	for(int i = 1; i <= n ; ++i)
		for(int j = 1 ; j <= m; ++j)
			for(int j1 = 1 ; j1 <= K; ++j1)
				scanf("%d",&a[i][j][j1]);

	
	memset(f,0,sizeof(f));
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <=m ; ++j)
			for(int k = 0; k <= K; ++k)
				//f[i][j] = f[i-1][j] + f[i][j-1] + a[i][j] - f[i-1][j-1];
				f[i][j][k] = a[i][j][k] + f[i-1][j][k] + f[i][j-1][k] + f[i][j][k-1]
				- f[i-1][j-1][k] - f[i-1][j][k-1] - f[i][j-1][k-1]
										+f[i-1][j-1][k-1];

	

//	cout<<sum(1,2,1,3,1,5)<<endl;
//	cout<<f[2][3][5]<<endl;

//	cout<<sum(1,1,1,1,1,1)<<endl;
//	cout<<f[1][1][1]<<endl;

//	return 0;
	int q;
	scanf("%d",&q);
	int lx,rx,ly,ry,lz,rz;
	for(int i = 0; i < q; ++i){
		scanf("%d %d %d %d %d %d",&lx,&ly,&lz,&rx,&ry,&rz);
		if(i) printf("\n");
		printf("%d",sum(lx,rx,ly,ry,lz,rz));
	}



	return 0;
}