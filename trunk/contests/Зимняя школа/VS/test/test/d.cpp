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

VVI ans(4);
priority_queue<pii, vector<pii>, greater<pii> > even,odd;
VI ones;

int max_qnt = -1;
void ans_push(int a,int b,int c,int d)
{
	ans[0].push_back(a);
	ans[1].push_back(b);
	ans[2].push_back(c);
	ans[3].push_back(d);
}

pii minimum(){
	pii ret(-1,-1);
	if(even.empty())
	{
		ret= odd.top();
		odd.pop();
	}
	else
		if(odd.empty())
		{
			ret = even.top();
			even.pop();
		}else
		{
			if(odd.top().first < even.top().first)
			{
				ret = odd.top();
				odd.pop();
			}
			else
			{
				ret = even.top();
				even.pop();
			}
		}

	return ret;
}

void Vpii_from_Q(vector<pii>& b,priority_queue<pii, vector<pii>, greater<pii> > & Q)
{
	while(!Q.empty())
	{
		b.push_back(Q.top());
		Q.pop();
	}
}

pii minimum_odd()
{
	pii ret(-1,-1);
	if(!ones.empty()){
		ret = pii(1,ones.back());
		ones.pop_back();
	}
	else
		if(!odd.empty())
		{
			ret = odd.top();
			odd.pop();
		}
	return ret;
}


void push(int cnt,int val)
{
	if(cnt == 0) return;
	max_qnt = max(max_qnt,cnt);
	if(cnt == 1){
		ones.push_back(val);
		return;
	}
	if(cnt&1)
		odd.push(pii(cnt,val));
	else
		even.push(pii(cnt,val));
}

int main(){
//freopen("in.txt","r",stdin);
freopen("d.in","r",stdin);
freopen("d.out","w",stdout);
	int n;
	cin>>n;



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
		push(it->second,it->first);
	}
/*
	if(odd.size() == 1 && even.size() == 1){
		pii p = even.top();
		int L = p.first/2;
		cout<<L;
		for(int i = 0; i < L; ++i){
			printf("\n%d %d %d %d",p.second,p.second,odd[0].second,odd[0].second);
		}
		return 0;
	}
*/
	

	while(!ones.empty()||!odd.empty()||!even.empty()){
		if(odd.empty() && even.empty())
			fail();

		if(ones.empty() && odd.empty()){
			vector<pii> b;
			Vpii_from_Q(b,even);
			int mx = b.back().second;
			for(int i = 0; i < b.size() -1 ; ++i){
				for(int j = 0 ; j< b[i].second/2; ++j)
					ans_push(b[i].second,b[i].second,mx,mx);
			}
			break;
		}

		if(odd.size() == 1 && ones.empty() && odd.top().first == max_qnt){
			if(!even.empty()){
				vector<pii> b;
				int max_elem = odd.top().second;
				Vpii_from_Q(b,even);
				int mx = b.back().first;
				for(int i = 0; i < b.size(); ++i){
					for(int j = 0 ; j< b[i].second/2; ++j)
						ans_push(b[i].second,b[i].second,max_elem,max_elem);
				}
			}
			break;
		}

		int a,b,c,d;

		pii min_p = minimum();
		pii min_odd = minimum_odd();
		
		a = b = min_p.second;
		c = min_odd.second;





		push(min_p.first - 2,min_p.second);
		push(min_odd.first + 1,min_odd.second);

		min_odd = minimum_odd();
		d = min_odd.second;
		if(min_odd.first == -1)
		{
			vector<pii> b;
			Vpii_from_Q(b,even);
			if(!b.empty()){
				for(int i = 0;i<b.size()-1;++i)
					push(b[i].first,b[i].second);
				push(b.back().first + 1,b.back().second);
				d = b.back().second;
			}
			
		}

		
	
		push(min_odd.first+1,min_odd.second);

		ans_push(a,b,c,d);
		
	}

	int L = ans[0].size();
	cout<<L;
	for(int i = 0; i <L; ++i)
		printf("\n%d %d %d %d",ans[0][i],ans[1][i],ans[2][i],ans[3][i]);
	return 0;

}
