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


#pragma comment(linker,"/stack:256000000")

const int maxN = 120000;
int a[maxN];

int deg2[32];
const int inf = 1<<30;

struct StaticMin{
	int d[18][1<<18];
	int size;
	StaticMin(int b[],int n):size(n){

		for(int j = 0; j < 18; ++j)
			for(int i = 0; i < (1<<18); ++i)
				d[j][i] = inf;


		for(int i = 0; i < n; ++i)
			d[0][i] = b[i+1];

		for(int j = 1; j < 18; ++j){
			for(int i = 0; i < n; ++i)
				d[j][i] = min(d[j-1][i],d[j-1][i+deg2[j-1]]);
		}
	}

	inline int minimum(int l,int r){
		--l; --r;
		if(l>r) swap(l,r);
		int len = r-l+1;
		int j = 0;
		for(;(1<<j)<=len;j++);
		--j;
		
		return min(d[j][l],d[j][r-deg2[j]+1]);
		
	}

};

int main(){
//freopen("in.txt","r",stdin);
 freopen("j2.in","r",stdin);
freopen("j2.out","w",stdout);

	for(int i = 0; i < 32;++i)
		deg2[i] = 1<<i;

	//int b[10] = {1,2,3,4,5,6,7,8,9,10};	
	//StaticMin T1(b,10);

	//int t = T1.minimum(9,9);
	//printf("%d\n",t);

	//return 0;

	int n,m,a0;
	cin>>n>>m>>a0;


	a[1] = a0;
	for(int i = 2; i <=n ; ++i)
		a[i] = (23*a[i-1] + 21563) % 16714589;

	//for(int i = 0; i < n; ++i) cout<<a[i+1]<<" ";
	int u,v,ans;
	cin>>u>>v;

	StaticMin T(a,n);

	for(int i = 1; i < m;++i){
		ans = T.minimum(u,v);
		u = ((17*u + 751 + ans + 2*(i)) %n)  +1;
		v = ((13*v + 593 + ans + 5*(i)) %n) +1;
	}
	
	ans = T.minimum(u,v);
	printf("%d %d %d\n",u,v,ans);

	return 0;
}