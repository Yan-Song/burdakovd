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

const int inf = 1<<30;

struct StackMin{
	stack<int> data;
	stack<int> mins;

	void pop(){
		data.pop();
		mins.pop();
	}

	int minimum(){
		if(empty()) return inf;
		return mins.top();
	}
	void push(int x){
		data.push(x);
		if(mins.empty()){
			mins.push(x);
		}
		else
			mins.push(min(mins.top(),x));
	}
	
	int top(){
		return data.top();
	}
	bool empty() { return data.empty(); }
};

struct Qmin{
	StackMin in,out;

	inline int minimum(){
		if(empty()) return 0;
		return min(in.minimum(),out.minimum());
	}

	void pop(){
		if(out.empty()){
			while(!in.empty())
			{
				out.push(in.top());
				in.pop();
			}
		}
		if(!out.empty())
			out.pop();
	}


	void push(int x){
		in.push(x);
	}

	bool empty(){
		return in.empty() && out.empty();
	}
};

const int modulo = 1000000;

int main(){
//freopen("in.txt","r",stdin);
freopen("m2.in","r",stdin);
freopen("m2.out","w",stdout);
	int n,a,b,c;
	i64 x;
	scanf("%d %d %d %d",&n,&a,&b,&c);
	cin>>x;

	i64 ans = 0;

	Qmin Q;

	for(int i = 0; i < n; ++i){
		x = (a*x*x + b*x + c)/100 % modulo;

		if(x % 5 < 2)
			Q.pop();
		else
			Q.push(x);

		ans += Q.minimum();

	}

	cout<<ans<<endl;


	return 0;
}
