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


string a;
string G;
char values[16][16] = 
{"0000",
 "0001",
 "0010",
 "0011",
 "0100",
 "0101",
 "0110",
 "0111",
 "1000",
 "1001",
 "1010",
 "1011",
 "1100",
 "1101",
 "1110",
 "1111"};




void hex2bin(string& hex,string& bin){
	bin = "";
	for(int i = 0; i < hex.size(); ++i){
		if(isdigit(hex[i])){
			bin += values[hex[i]-'0'];
		}
		else{
			bin+= values[hex[i]-'A'+10];
		}
	}
}

void bin2hex(string& bin,string& hex){
	hex = "";
	for(int i = 0; i < bin.size(); i+=4){
		int curval = 0;
		for(int k = i;k<i+4;++k){
			curval=curval*2 + (bin[k]-'0');
		}
		if(curval<10)
			hex+=curval+'0';
		else
			hex+=curval-10+'A';
	}
}

inline char myxor(char a,char b){
	return  a==b?'0':'1';
}

int main(){
//freopen("in.txt","r",stdin);
freopen("a.in","r",stdin);
freopen("a.out","w",stdout);



	cin>>a;

	hex2bin(a,G);

	string N(G.size(),' ');
	
	N[0] = G[0];
	for(int i = 1; i < N.size(); ++i){
		N[i] = myxor(G[i],N[i-1]);
	}

	bin2hex(N,a);

	
	int l = 0;
	while(l<a.size()-1 && a[l]=='0') ++l;

	cout<<a.substr(l);
	return 0;
}