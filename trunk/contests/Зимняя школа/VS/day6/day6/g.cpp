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

inline i64 sqr(i64 b) { return b*b;}
#pragma comment(linker,"/stack:64000000")

#define adebug2d(a,n,m) for(int i = 0; i < n; ++i,cout<<endl) for(int j = 0; j < m; ++j) cout<<a[i][j]<<" ";

const int maxN = 310;
bool was[1<<8][maxN][maxN];
int sum[500];
int treasure_weights[10];
int isTreasure[maxN][maxN];
int Ntreasures = 0;

int can_hold[maxN][maxN];

struct State{
	int i,j,mask;
	State(int mask,int i,int j){ this->mask = mask; this->i = i; this->j = j; }
};


int N,M,w0;

inline bool isCapital(char c){
	return c>='A' && c<='Z';
}

int di[] = {1,-1,0,0};
int dj[] = {0,0,1,-1};

char str[10];

int dp[maxN][maxN];

int w[20][20];

/*
int count_path(int u){
	int i = tr_c[u].first;
	int j = tr_c[u].second;
	
	

}
*/

int main(){
//freopen("in.txt","r",stdin);
freopen("g.in","r",stdin);
//freopen("g6.out","w",stdout);
/*
	printf("%d %d %d\n",300,300,100);
	for(int i = 0; i < 300;++i,cout<<endl)
		for(int j = 0; j < 300; ++j)
			if(i == 0 && j < 8)
				cout<<"Z ";
			else	
			cout<<1000<<" ";


	return 0;
*/
	memset(was,false,sizeof(was));
	memset(treasure_weights,0,sizeof(treasure_weights));
	memset(sum,0,sizeof(sum));
	memset(isTreasure,0,sizeof(isTreasure));

	for(int i = 0; i < maxN; ++i)
		for(int j = 0; j < maxN; ++j)
			can_hold[i][j] = inf;

	scanf("%d %d %d",&N,&M,&w0);

	for(int i = 1; i <= N; ++i)
		for(int j = 1; j <= M; ++j)
		{
			scanf("%s",&str);
			if(isCapital(str[0])){
				treasure_weights[Ntreasures] = str[0]- 'A' +1;
				can_hold[i][j] = inf;
				isTreasure[i][j] = 1<<Ntreasures;
				Ntreasures++;
			}
			else{
				sscanf(str,"%d",&can_hold[i][j]);
				can_hold[i][j] -= w0;
			}
		}

	
	for(int i = 0; i < (1<<Ntreasures); ++i){
		for(int j  = 0; j < Ntreasures; ++j)
			if(i&(1<<j))
				sum[i]+=treasure_weights[j];
	}

	//queue<State, vector<State>> Q;
	stack<State, vector<State> > Q;
//	Q.c.reserve(10000);

	for(int j = 0; j <= M+1; ++j)
	{
		was[0][0][j] = was[0][N+1][j] = true;
		Q.push(State(0,0,j));
		Q.push(State(0,N+1,j));
	}
	for(int i = 0; i <= N+1; ++i)
	{
		was[0][i][0] = was[0][i][M+1] = true;
		Q.push(State(0,i,0));
		Q.push(State(0,i,M+1));
	}
	

	


	int maxSize = 0;

	while(!Q.empty()){
		//State cur = Q.front();
		maxSize = max(maxSize,(int)Q.size());
		State cur = Q.top();
		Q.pop();

		int weight = sum[cur.mask];

		for(int k = 0; k < 4; ++k){
			int ni = cur.i + di[k];
			int nj = cur.j + dj[k];
			if(ni<0||nj<0 || ni > N+1 || nj > M+1 || can_hold[ni][nj] < weight)
				continue;
			int newMask = cur.mask | isTreasure[ni][nj];
			if(was[newMask][ni][nj])
				continue;
			was[newMask][ni][nj] = true;
			Q.push(State(newMask,ni,nj));
		}		
		
	}

	cout<<maxSize<<endl;

	int ans = 0;

	for(int mask = 0; mask < (1<<Ntreasures) ; ++mask){
		for(int j = 0; j <= M+1; ++j)
			if(was[mask][0][j] || was[mask][N+1][j])
				ans = max(ans,sum[mask]);
		for(int i = 0; i <= N+1; ++i)
			if(was[mask][i][0] || was[mask][i][M+1])
				ans = max(ans,sum[mask]);
	}

	printf("%d",ans);	

	return 0;
}