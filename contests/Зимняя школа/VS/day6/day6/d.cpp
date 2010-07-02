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

#define adebug2d(a,n,m) for(int i = 0; i < n; ++i,cout<<endl) for(int j = 0; j < m; ++j) cout<<a[i][j]<<" ";

typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef pair<int,int> pii;
typedef long long i64;

const int inf = 1<<26;
const double eps = 1e-9;

inline i64 sqr(i64 b) { return b*b;}
#pragma comment(linker,"/stack:64000000")


struct Query{
	int i,j,t,n;
	Query() {}
	Query(int n,int i,int j,int t){
		this->n = n;
		this->i = i;
		this->j = j;
		this->t = t;
	}
	bool operator<(const Query& Q) const{
		return t < Q.t;
	}
};


int di[] = {0,0,1,-1};//{ 0, 1,  1, 1, 0 , -1 , -1 ,-1};
int dj[] = {1,-1,0,0};//{ 1, 1,  0, -1 ,-1 ,-1 , 0, 1};

const int maxN = 310;
int a[2][maxN][maxN];

Query queries[400000];
int ans[400000];

int main(){
	//freopen("in.txt","r",stdin);
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	int n,m;
	scanf("%d %d",&n,&m);
	int q;
	scanf("%d",&q);

	memset(a,0,sizeof(a));
	
	int cur = 0,prev = 1;
	//a[cur][1][1] = 1;
	for(int i = 1; i <= n ; ++i)
		for(int j = 1; j <= m; ++j)
			scanf("%d",&a[cur][i][j]);

	//memset(a,0,sizeof(a));
	int r,c,t;
	for(int i = 0; i < q; ++i){
		scanf("%d %d %d",&r,&c,&t);
		//--r; --c;
		queries[i] = Query(i,r,c,t);
	}


	sort(queries,queries+q);


	int cq = 0;

	bool modified = true;;
	for(t = 0;modified;++t){
		while(queries[cq].t == t){
			ans[queries[cq].n] = a[cur][queries[cq].i][queries[cq].j];
			++cq;
		}
		swap(cur,prev);

		modified = false;


		//adebug2d(a[prev],n+1,m+1);


		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
			{
				int mx = a[prev][i][j];
				for(int k = 0; k < 4;++k){
					int ni = i+di[k];
					int nj = j+dj[k];
					if(mx < a[prev][ni][nj])
					{
						mx = a[prev][ni][nj];
						modified = true;
					}

				}
				a[cur][i][j] = mx;
			}
	}

	for(;cq < q; ++cq){
		ans[queries[cq].n] = a[cur][queries[cq].i][queries[cq].j];
	}
	for(int i = 0; i < q; ++i)
		printf("%d\n",ans[i]);

	return 0;
}