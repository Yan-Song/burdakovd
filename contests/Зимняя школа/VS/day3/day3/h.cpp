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


struct Tree{
const static int maxN = 1<<18;
	int a[maxN+1];
	int size;
	int N;
	Tree(int n){
		//size = 1<<17;
		size = 1;
		while(size < n)  size <<= 1;
		for(int i = 0; i < maxN; ++i)
			a[i] = 0;

		N = n;
	}
	inline bool exists(int i) {
		return (a[i+size-1] == 1);//exists
	}
	int findPlace(int i){
		if(i<1 || i>N) return inf;
		int ret = rmq(1,i,N,1,size);
		if(ret!=inf)
			return ret;
		return rmq(1,1,i-1,1,size);
	}

	int rmq(int x,int i,int j,int l,int r){
		if(r<i || l > j) return inf;
		if(i<=l && r<=j){
			int len = r-l+1;
			if(a[x] == len) return inf;
			if(a[x] == 0) return l;
			if(l==r)
				return x;
		}
		int p = rmq(left(x),i,j,l,(l+r)/2);
		if(p!=inf) return p;
		return rmq(right(x),i,j,(l+r)/2 + 1,r);
	}

	void update(int x,int val){
		x+=size-1;
		a[x] = val;
		int p = parent(x);
		while(p>0){
			a[p] = a[x]+a[x^1];
			x = p;
			p = parent(p);
		}
	}

	inline int left(int x) { return x<<1; }
	inline int right(int x) { return (x<<1) + 1; }
	inline int parent(int x) { return x>>1; }

};

int main(){
//freopen("in.txt","r",stdin);
freopen("h.in","r",stdin);
freopen("h.out","w",stdout);
	int n,m;
	scanf("%d %d",&n,&m);
	Tree T(n);
	char com[5];
	for(int j = 0; j < m; ++j){
		int i;
		scanf("%s %d",com,&i);
		if(com[0] == '+'){
			int place = T.findPlace(i);
			if(place == inf)
				printf("-1\n");
			else{
				T.update(place,1);
				printf("%d\n",place);
			}
		}else{
			if(T.exists(i))
			{
				T.update(i,0);
				printf("0\n");
			}
			else
				printf("-2\n");
		}
	}
	return 0;
}