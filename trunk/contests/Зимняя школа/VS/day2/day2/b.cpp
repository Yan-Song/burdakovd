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

const int maxN = 1<<10;

int a[maxN][maxN];
int f[maxN][maxN];

inline int sum(int i1,int i2,int j1,int j2){
	return f[i2][j2] - f[i1-1][j2] - f[i2][j1-1] + f[i1-1][j1-1];
}

int main(){
//freopen("in.txt","r",stdin);
freopen("c2.in","r",stdin);
freopen("c2.out","w",stdout);

	int n,m;
	scanf("%d %d",&n,&m);
	for(int i = 1; i <= n ; ++i)
		for(int j = 1 ; j <= m; ++j)
			scanf("%d",&a[i][j]);

	
	memset(f,0,sizeof(f));
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <=m ; ++j)
			f[i][j] = f[i-1][j] + f[i][j-1] + a[i][j] - f[i-1][j-1];

	
	int q;
	scanf("%d",&q);
	int lx,rx,ly,ry;
	for(int i = 0; i < q; ++i){
		scanf("%d %d %d %d",&lx,&ly,&rx,&ry);
		if(i) printf("\n");
		printf("%d",sum(lx,rx,ly,ry));
	}



	return 0;
}