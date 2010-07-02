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


//#pragma comment(linker,"/stack:256000000")

inline i64 sqr(i64 x) { return x*x; }

const int maxN = 210000;

i64 dp[maxN];
i64 a[maxN];

int main(){
//freopen("in.txt","r",stdin);
freopen("i.in","r",stdin);
freopen("i.out","w",stdout);
	int n = 100000;
	//scanf("%d",&n);
	cin>>n;
	dp[0] = 0;
	for(int i =0 ;i < n; ++i)
	{
		//scanf("%lld",&a[i]);
		cin>>a[i];
//		if(i&1) a[i] = 4000+i;
//		else
//			a[i] = -4000-i;
	}

	for(int i = 1; i < n; ++i){
		dp[i] = dp[i-1] + sqr(a[i]-a[i-1]);
		if(i-2>=0){
			i64 d = dp[i-2] + 3*sqr(a[i]-a[i-2]);
			if(dp[i] >= d)
				dp[i] = d;
			
			d = dp[i-1] + sqr(a[i-1]-a[i-2]) + 3 * sqr(a[i-2]-a[i]);
			if(dp[i]>=d)
				dp[i] = d;
		}
	}
	//printf("%lld",dp[n-1]);
	cout<<dp[n-1]<<endl;;

	return 0;
}