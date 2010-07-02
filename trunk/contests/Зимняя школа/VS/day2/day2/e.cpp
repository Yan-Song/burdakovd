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



const int modulo = 1000000000;

set<int> s;

inline void add(int i){
	s.insert(i);
}

inline int next(int i){
	set<int>::iterator it = s.lower_bound(i);
	if(it == s.end())
		return -1;
	else
		return *it;
}

int main(){
//freopen("in.txt","r",stdin);
freopen("e2.in","r",stdin);
freopen("e2.out","w",stdout);
	
	int n;
	scanf("%d",&n);
	char com[10];
	int a;
	int last = 0;
	for(int i = 0; i < n; ++i){
		scanf("%s %d",com,&a);
		if(com[0] == '+'){
			add(((a+last)%modulo+modulo)%modulo);
			last = 0;
		}
		else{
			last = next(a);
			printf("%d\n",last);
		}
	}
	return 0;
}