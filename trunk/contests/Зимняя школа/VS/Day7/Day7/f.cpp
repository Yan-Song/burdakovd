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


const i64 modulo = 1000009;

const int maxN = 500;
i64 f[maxN]; 

i64 fact(i64 n){
	if(n==0) return 1;
	return (n*fact(n-1))%modulo;
}

int main(){
//freopen("in.txt","r",stdin);
freopen("f.in","r",stdin);
freopen("f.out","w",stdout);
	int N;
	cin>>N;

	if(N%2 == 0){
		cout<<"0";
		return 0;
	}
	f[1] = 1;

	for(int n = 1; n <= N; ++n){
		i64 sum = 0;
		for(int k = 1; k < 2*n; k+=2){
			sum+=f[k]*f[2*n-k];
			sum%=modulo;
		}
		sum*=4;
		f[2*n+1] = sum%modulo;
	}

	int n = N/2;
	i64 ans = f[N]*fact(n+1);
	ans%=modulo;


	cout<<ans;

	return 0;
}