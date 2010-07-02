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

const int inf = 1<<30;
const double eps = 1e-9;

#define sqr(x) ((x)*(x))
#pragma comment(linker,"/stack:128000000")

vector<pii> points;
VVI V;
const int maxN = 8000;

struct Edge{
	int u,v;
	Edge() {}
	Edge(int uu,int vv) { u = uu; v = vv; }
	bool operator<(const Edge& E) const{
		return u<E.u || u == E.u && v < E.v;
	}
};

int dist(int i,int j){
	return sqr(points[i].first - points[j].first) + sqr(points[i].second - points[j].second);
}


int p[maxN];

void init_sets(){
	for(int i = 0; i < maxN; ++i)
		p[i] = i;
}

int find_set(int u){
	return u==p[u]? u : (p[u] = find_set(p[u]));
}

bool same_sets(int u,int v){
	return find_set(u) == find_set(v);
}

void set_union(int u,int v){
	p[find_set(u)] = find_set(v);
}


void MST(vector<pii>& points,VVI& V,int n){
	priority_queue<pair<int,Edge >, vector<pair<int,Edge > > ,greater<pair<int,Edge > > > Q;

	init_sets();

	for(int i = 0; i < n; ++i){
		int min_dist = inf;
		int v;
		for(int j = i+1; j < n; ++j){
			int cur = dist(i,j);
			if(min_dist > cur){
				min_dist = cur;
				v = j;
			}
		}
		
		if(min_dist < inf)
			Q.push(make_pair(min_dist,Edge(i,v)));
	}

	int size = 0;

	while(!Q.empty() && size < n){
		pair<int , Edge> cur = Q.top(); Q.pop();
		int u = cur.second.u;
		int v = cur.second.v;

		if(!same_sets(u,v))
		{
			set_union(u,v);
			++size;
			V[u].push_back(v);
			V[v].push_back(u);
		}

		int min_dist = inf;
		int k;
		for(int v = u + 1; v < n; ++v)
			if(dist(u,v) < min_dist && !same_sets(u,v)) {
				min_dist = dist(u,v);
				k = v;
			}
		if(min_dist < inf){
			Q.push(make_pair(min_dist,Edge(u,k)));
		}
		

	}

}

int colors[8000];

void dfs(int u,int col = 0){
	if(colors[u] != -1) return;
	colors[u] = col;

	for(int i = 0; i < V[u].size(); ++i){
		int v = V[u][i];
		dfs(v,col^1);
	}
}


int main(){
//freopen("in.txt","r",stdin);
freopen("g1.in","r",stdin);
freopen("g1.out","w",stdout);
	int n;
	scanf("%d",&n);
	points.resize(n);
	V.resize(n);

	

	for(int i = 0; i < n; ++i){
		scanf("%d %d",&points[i].first,&points[i].second);
	}

	MST(points,V,n);

	memset(colors,-1,sizeof(colors));


	dfs(0);


	int ans = inf;

	for(int i = 0; i < n; ++i)
		for(int j = i+1; j < n; ++j){
			if(colors[i] == colors[j])
				ans = min(ans,dist(i,j));
		}

	printf("%.6lf\n",sqrt(0.0+ans)/2);
	for(int i = 0; i < n; ++i)
		printf("%d ",colors[i]+1);

	return 0;
}