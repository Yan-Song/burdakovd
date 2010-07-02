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

const int maxN = 1000000;

int n;

int a[20];

/*
bool lose(){
	int cnt = count(a,a+n,1);
	if(cnt == n){
		if( n % 2 == 1)
			return true;
		else
			return false;
	}
	int res = 0;
	for(int i = 0; i < n; ++i)
		res^=(a[i]);


	return (res^(cnt%2)) == 0;
}*/

bool lose(){
	int cnt = count(a,a+n,1);
	if(cnt == n)
		return n%2;

	map<int,int> b;
	for(int i = 0; i < n; ++i){
		int t = b[a[i]];
		b[a[i]] = t+1;
	}

	for(map<int,int>::iterator it = b.begin(); it != b.end(); ++it)
		if(it->second % 2)
			return false;
	return true;
}

int main(){
//freopen("in.txt","r",stdin);
freopen("c.in","r",stdin);
freopen("c.out","w",stdout);
/*	for(int i = 2; i < maxN;++i)
		for(int j = 2; j <= i/2+1; ++j){
			int a = i;
			int b = j;
			int c = a-b;
			if(c<2) continue;
			if((a-1)==((b-1)^(c-1)))
				printf("%d = %d + %d\n",a,b,c);

		}

*/
	scanf("%d",&n);
	for(int i = 0; i < n; ++i)
		scanf("%d",&a[i]);

	if(lose())
		printf("Second");
	else
		printf("First");

	return 0;

}