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

const int maxN = 110;

double p[110][2]; 
double u[110][2]; 
double d[110][2]; 

double A,B;

int main(){
//freopen("in.txt","r",stdin);
freopen("h.in","r",stdin);
freopen("h.out","w",stdout);
	int N;

	scanf("%d %lf %lf",&N,&A,&B);
	p[1][0] = p[1][1] = 0;
	
	for(int n = 2; n <= N; ++n){
		for(int place = 0; place<2;++place){
			double a = A, b = B;
			if(place == 1) swap(a,b);
			double add;
			if(p[n-1][place^1] > 0)
				add = 1.0/(n-1)*a + (n-2.0)/(n-1)*p[n-2][place];
			else 
				add = a;

			double d = -1.0/n + (n-1.0)/n*add;
			p[n][place] = max(0.0,d);
		}
	}

	for(int n = 1; n <= N; ++n)
		for(int place = 0; place < 2; ++place)
	{
		double D;
		if(p[n][place]>0)
			D = (n-1.0)/n*(1-d[n-1][place^1]);

		d[n][place] = (p[n][place]>0)?D:0;
	}

	for(int n = 1; n <= N;++n)
		for(int place = 0; place < 2; ++place){
			if(p[n][place] > 0){
				u[n][place] = 1.0/n;

				if(p[n-1][place^1] > 0){
					u[n][place] += (n-2.0)/n * u[n-2][place];
				}
			}
			else
				u[n][place] = 0;
				
		}

	printf("%.8lf %.8lf\n", u[N][0], d[N][0]);
	printf("%.8lf %.8lf" , p[N][0] > 0 ? (N-1.0)/N * u[N-1][1] : 0  , 1.0 - d[N][0]);

	return 0;
}