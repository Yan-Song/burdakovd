#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>
using namespace std;

typedef vector<vector<int> > VVI;
typedef vector<int> VI;
typedef pair<int,int> pii;

void fail()
{
	cout<<-1;
	exit(0);
}

int main(){
//freopen("in.txt","r",stdin);
//freopen("in.txt","r",stdin);
//freopen("out.txt","w",stdout);
	int n;
	cin>>n;

	priority_queue<pii, vector<pii>, greater<pii> > even;
	vector<pii> odd;

	int ai;
	map<int,int> mp;
	for(int i = 0; i < n; ++i){
		scanf("%d",&ai);
		if(mp.find(ai) == mp.end())
			mp[ai] = 1;
		else
		{
			int t = mp[ai];
			mp[ai] = t+1;
		}
	}

	for(map<int,int>::iterator it = mp.begin();it!=mp.end();++it){
		pii padd(it->second,it->first);
		if((it->second)&1)
			odd.push_back(padd);
		else
			even.push(padd);
	}

	if(odd.size() == 1 && even.size() == 1){
		pii p = even.top();
		int L = p.first/2;
		cout<<L;
		for(int i = 0; i < L; ++i){
			printf("\n%d %d %d %d",p.second,p.second,odd[0].second,odd[0].second);
		}
		return 0;
	}

	VVI ans(4);

	sort(odd.begin(),odd.end(),greater<pii>);

	while(odd.size()>0 && !even.empty()){
		if(odd.size() == 1){
			if(odd[0].first == 1){
								
			}
			else{
			}
			continue;
		}
		int k = odd.size()-1;
		int a = odd[k].second;
		int d = odd[k-1].second;
		int c = even.top().second;
		even.pop();
		int qnt = even.top().first;
		ans[0].push_back(c);
		ans[1].push_back(c);
		ans[2].push_back(a);
		ans[3].push_back(d);

		qnt-=2;
		if(qnt!=0)
			even.push(pii(qnt,c));
		even.push(pii(odd[k].first-1,odd[k].second));
		even.push(pii(odd[k-1].first-1,odd[k-1].second));

		odd.pop_back();
		odd.pop_back();
	
	}

		int L = ans.size();
		
		vector<pii> b;
		while(!even.empty()){
			b.push_back(even.top());
			even.pop();
		}

		if(b.empty()){
			cout<<L;
			for(int i = 0; i <ans[0].size(); ++i)
				printf("\n%d %d %d %d",ans[0][i],ans[1][i],ans[2][i],ans[3][i]);
			return 0;
		}

		int mx = b.back().second;
		for(int i = 0 ; i < b.size()-1;++i)
			L+=b[i].first/2;

		cout<<L;
		for(int i = 0; i <ans[0].size(); ++i)
			printf("\n%d %d %d %d",ans[0][i],ans[1][i],ans[2][i],ans[3][i]);


		for(int i = 0; i < b.size()-1;++i)
			for(int j = 0; j < b[i].first/2; ++j)
				printf("\n%d %d %d %d",b[i].second,b[i].second,mx,mx);
		

	return 0;
}