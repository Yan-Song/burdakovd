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

const int maxN = 21;
const int maxMask = 1<<21;

int dp[maxMask];


int odd_move; // if 1 then max

const int MIN = 0;
const int MAX = 1;

VVI V;
VVI W;

int n,m;
/*
int f(int mask){

int goal;
int ret;
if(!odd(mask)) // будет пытаться ходить 1й игрок
goal = odd_move;
else
goal = odd_move^1;

if(goal == MIN)
ret = inf;
else
ret = 0;

if(goal == MAX){
for(int v = 1; v < n; ++v)
if(mask & (1<<v)){
int new_mask = mask^(1<<v);

}
}
else{

}
return 0;

}
*/
int E[maxN][maxN];

int main(){
	//freopen("in.txt","r",stdin);
	freopen("e.in","r",stdin);
	freopen("e.out","w",stdout);
	//mset(memo,-1);
	string first;

	cin>>n>>m>>first;

	if(first == "ANDREW") // min
		odd_move = MIN;
	else
		odd_move = MAX;

	memset(E,0,sizeof(E));


	V.resize(n);
	W.resize(n);

	for(int i = 0; i < m; ++i)
	{
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		u--;
		v--;
		V[u].push_back(v);
		W[u].push_back(w);
		V[v].push_back(u);
		W[v].push_back(w);
		E[u][v] = E[v][u] = w;
	}

	//int goal;
	//if(!odd(mask)) // будет пытаться ходить 1й игрок
	//	goal = odd_move;
	//else
	//	goal = odd_move^1;

	dp[0] = 0;

	VI in_tree;
	VI out_of_tree;
	for(int i = 1; i<n;++i){
		string mask =  string(n-i,'0')+string(i,'1');
		do{
			in_tree.clear();
			out_of_tree.clear();

			int int_mask = 0;
			for(int i = 0; i < n; ++i)
				if(mask[i] == '0')
				{
					in_tree.push_back(i);
					
				}
				else
				{
					out_of_tree.push_back(i);
					int_mask |= (1<<i);
				}

			int m;
			if((n-i)&1){
				// ходит первый
				m = ((odd_move == MIN)?-1:1);
			}
			else
				m = ((odd_move == MIN)?1:-1);

			int best = -m*inf;




			for(int i = 0; i<in_tree.size();++i)
				for(int j = 0; j < out_of_tree.size();++j){
					int u = in_tree[i];
					int v = out_of_tree[j];
					if(E[v][u] == 0) continue;
					int cur = E[v][u] + dp[int_mask ^ (1<<v)];

					if(m<0)
						best = min(best,cur);
					else
						best = max(best,cur);

				}
				dp[int_mask] = best;
		}
		while(next_permutation(mask.begin(),mask.end()));
	}

	printf("%d",dp[((1<<n)-1)-1]);


	return 0;
}