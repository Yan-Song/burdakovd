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

string s;

const int maxN = 10000;

int byte_ones[maxN];
int ones[20];


int toDigit(char c){
	if(isdigit(c))
		return c-'0';
	return c-'A'+10;
}

int count_ones(int i){
	int ans = 0;
	for(;i;++ans,i=i&(i-1));
	return ans;
}

int ps[maxN];
int counts[30000];

int main(){
//freopen("in.txt","r",stdin);
freopen("k.in","r",stdin);
freopen("k.out","w",stdout);
	memset(counts,0,sizeof(counts));
	cin>>s;
	int n = s.size()/2;

	for(int i = 0; i < 16;++i)
		ones[i] = count_ones(i);
	
	for(int i = 0; i < n; ++i)
		byte_ones[i+1] = ones[toDigit(s[2*i])] + ones[toDigit(s[2*i+1])];
	
	ps[0] = 0;
	for(int i = 1; i <= n; ++i)
		ps[i] = ps[i-1]+byte_ones[i];


	for(int A = 1; A<=n; ++A)
		for(int B = A; B<=n;++B){
			if((B-A+1)*4 == ps[B] - ps[A-1])
				++counts[ps[B]-ps[A-1]];
		}

	
	int mx = *max_element(counts,counts+maxN);

	for(int i = maxN-1; i >= 0; i--)
		if(counts[i] == mx){
			printf("%d",i);
			return 0;
		}

	throw 9;


	return 0;
}