#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;



int main(){
//freopen("in.txt","r",stdin);
freopen("c1.in","r",stdin);
freopen("c1.out","w",stdout);
	vector<vector<int> > a(8);
	int n;
	cin>>n;
	for(int i = 0; i < n; ++i){
		int ai;
		scanf("%d",&ai);
		a[ai%8].push_back(ai);
	}

	vector<int> ans;

	int cur = 0;

	for(;;){
		if(cur!=0 && !a[0].empty()){
			for(int i = 0; i  < a[0].size();++i)
				ans.push_back(a[0][i]);
			a[0].clear();
		}
		int mi = -1;

		for(int i = 1 ; i < 8; ++i)
			if((cur+i)%8 != 0 && !a[i].empty() && (mi == -1 || a[i].size() > a[mi].size()))
				mi = i;

		if(mi == -1) 
		{
			for(int i = 0; i < 8; ++i)
				if(!a[i].empty())
					ans.push_back(a[i][0]);
			break;
		}
		ans.push_back(a[mi].back());
		a[mi].pop_back();
		cur = (cur+mi) %8 ;
	}

	cout<<ans.size()<<endl;
	for(int i = 0; i <ans.size(); ++i){
		if(i)
			printf(" ");
		printf("%d",ans[i]);
	}
	return 0;
}