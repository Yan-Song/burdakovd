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


const int maxN = 300;
int p[maxN][maxN];
double memo[maxN][maxN];

string ops;
VI digits;

double f(int l,int r){
	if(p[l][r]!=-1)
		return memo[l][r];
	double& ret = memo[l][r];
	p[l][r] = r;
	if(l==r)
		return digits[l];

	for(int k = l;k<r; ++k){
		switch(op[k]){
			case '+':
				break;
			case '-':
				break;
			case '*':
				break;
		}
	}
}

int main(){
//freopen("in.txt","r",stdin);
//freopen("in.txt","r",stdin);
//freopen("out.txt","w",stdout);
	string s;
	cin>>s;

	memset(p,-1,sizeof(p));
	for(int i = 0; i < s.size();++i){
		if(i%1 == 0)
			digits.push_back(s[i]-'0'):
		else
			ops+=s[i];
	}

	int l = 0;
	int r = digits.size();
	f(l,r);

	string ans = prnt(l,r);
	cout<<ans<<endl;
	

	return 0;
}