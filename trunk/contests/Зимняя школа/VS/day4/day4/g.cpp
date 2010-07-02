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
#define mset(A,x) memset(A,x,sizeof(A))
int n,m;
const int maxN = 25;

char a[maxN][maxN];

const char empty = '#';


int di[] = {1,-1,0,0};
int dj[] = {0,0,1,-1};


char colors[8] = "RBGWVYO";
const int Ncolors = 7;

int dfs(int i, int j,char cur,char b[maxN][maxN],bool leave_empty = false){
	if(i<0 || j <0 || i>=n || j >= m || b[i][j] != cur || b[i][j] == empty) return 0;
	b[i][j] = empty;
	int ret = 1;

	for(int k = 0; k  < 4; ++k)
		ret+=dfs(i+di[k],j+dj[k],cur,b,leave_empty);

	if(!leave_empty)
		b[i][j] = cur;
	return ret;
}

void shift(char b[maxN][maxN]){
	char left[maxN];
	for(int j = 0; j < m; ++j){
		int sz = 0;
		for(int i = n-1; i >=0; --i)
		{
			if(b[i][j]!=empty)
				left[sz++] = b[i][j];
			b[i][j] = empty;
		}

		for(int i = n-1, k = 0; k<sz; i--,k++)
			b[i][j] = left[k];
	}
}

bool emp[maxN][maxN];
int simulate(char b[maxN][maxN]){
	bool destroyed = false;
	
	mset(emp,false);
	for(int k = 0; k < Ncolors;++k){
		char col = colors[k];
		int cur_count;

		for(int i = 0; i < n; ++i)
		{
			cur_count = 0;
			for(int j = 0; j <= m; ++j)
				if(b[i][j] == col)
					cur_count++;
				else
				{
					
					if(cur_count>=3){
						for(int t = j - cur_count; t<j;++t)
							emp[i][t] = true;
						destroyed = true;
					}

					cur_count = 0;
				}
		}
		

		for(int j = 0; j <m;++j)
		{
			cur_count = 0;
			for(int i = 0; i <=n ; ++i)
				if(b[i][j] == col)
					cur_count++;
				else{
					if(cur_count >= 3){
						for(int t = i-cur_count; t <i ;++t)
							emp[t][j] = true;
						destroyed = true;
					}
					cur_count = 0;

				}
		}
				
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			if(emp[i][j])
				b[i][j] = empty;
	
	if(destroyed){
		shift(b);
		return simulate(b);
	}

	int ret = 0;
	for(int i = 0; i < n ; ++i)
		for(int j = 0; j < m; ++j)
			if(b[i][j]!=empty)
				++ret;

	return ret;
}


int solve(){
	int ret = n * m;
	char b[maxN][maxN];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			for(int k = 0; k < 4; ++k){
				int ni = i + di[k];
				int nj = j + dj[k];
				if(ni<0||nj<0 || ni >= n || nj >= m) continue;
				memcpy(b,a,sizeof(a));
				swap(b[i][j],b[ni][nj]);
				ret = min(ret,simulate(b));
			}

	return ret;
}


int main(){
//freopen("in.txt","r",stdin);
freopen("g.in","r",stdin);
freopen("g.out","w",stdout);
	memset(a,'#',sizeof(a));
	scanf("%d %d",&n,&m);
	for(int i = 0; i < n; ++i)
		scanf("%s",a[i]);
	
	printf("%d",solve());

	return 0;
}