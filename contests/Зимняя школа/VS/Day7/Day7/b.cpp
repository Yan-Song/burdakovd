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

const int maxN = 310000;

char a1[maxN],a2[maxN];
char res[maxN];

int main(){
//freopen("in.txt","r",stdin);
freopen("b.in","r",stdin);
freopen("b.out","w",stdout);
	scanf("%s",a1);
	scanf("%s",a2);

	int n = strlen(a1);
	int over = 1;
	res[n] = 0;

	for(int i = n-1; i >=0;--i){
		if(isdigit(a1[i])){
			int a = a1[i] - '0';
			int b = a2[i] - '0';
			int c = a+b+over;
			over = c/10;
			c%=10;
			res[i] = c+'0';
		}else{
			int a = a1[i] - 'a'+0;
			int b = a2[i] - 'a'+0;
			int c = a+b+over;
			over = c/26;
			c%=26;
			res[i] = c+'a';

		}

	}
	printf("%s",res);
	

	return 0;
}