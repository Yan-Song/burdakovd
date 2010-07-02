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

typedef pair<string,char> psc;

int l = 0;
string s;
string ans;

string pack(string s){
	return "("+s+")";
}

bool contains(string s,char c){
	return s.find(c) != string::npos;
}

pair<string,char> print(){
	if(l>s.size()) return make_pair("",1);
	int k = l;
	++l;
	if(isalpha(s[k])){
		return make_pair(string(1,s[k]),1);
	}

	psc a1 = print();
	psc a2 = print();

	string op1 = a1.first;
	string op2 = a2.first;

	string what1;
	string what2;

	switch(s[k]){
		case '-':
			what1 = "";
			what2 = "+-";
			break;
			
		case '*':
			what1 = "+-/";
			what2 = "+-";
			break;
		case '/':
			what1 = "+-";
			what2 = "+-*/";
			break;
	}
	if(contains(what1,a1.second))
		op1 = pack(op1);
	if(contains(what2,a2.second))
		op2 = pack(op2);
	
	return make_pair(op1+s[k]+op2,s[k]);
	
}

int main(){
//freopen("in.txt","r",stdin);
freopen("g.in","r",stdin);
freopen("g.out","w",stdout);
	cin>>s;
	cout<<print().first;
	return 0;
}