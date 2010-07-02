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
#include <cassert>


using namespace std;

const int seed = 107;
const int maxTests = 1000;
const int maxN = 210;

const int mod = 1600;

int x[maxN];
int y[maxN];
int n;



typedef vector<int> VI;

inline int sqr(int x) { return x*x; }


set<int> dists;
int sz = 0;

bool ok(int x0,int y0){
	set<int> a;
	for(int i = 0; i < sz; ++i)
	{
		int d = (sqr(x[i]-x0)+sqr(y[i]-y0));
		a.insert(d);
	}
	if(a.size() != sz)
		return false;

	for(set<int>::iterator it = a.begin(); it!=a.end(); ++it)
		if(dists.count(*it))
			return false;

	return true;
}


void out_array(int a[],int n)
{
	cout<<"{";
	for(int i = 0; i < n; ++i)
	{
		if(i)
			printf(", ");
		printf("%d",a[i]);
	}
	cout<<"};\n";
}

void ans()
{
	for(int i = 0; i < n; ++i)
	{
		if(i)
			printf("\n");
		printf("%d %d",x[i],y[i]);
	}
	exit(0);
}

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);

	cin>>n;

	srand(17);
	//dists.insert(0);

	int x0 = 0;
	int y0 = 0;

	int spirals = 0;
	int l = 0;
	int L = 1;
	int d = 0;

	while(abs(x0)<=800 && abs(y0) <=800)
	{
		if(ok(x0,y0))
		{
			x[sz] = x0;
			y[sz] = y0;
			for(int i = 0 ; i<sz;++i)
			{
				int dst = sqr(x[sz]-x[i])+sqr(y[sz]-y[i]);
	//			assert(dists.count(dst)==0);
	//			cout<<dst<<endl;
				dists.insert(dst);
			}
			++sz;
		}
		//printf("%d %d\n",x0,y0);
		if(sz == n) 
		{
			cout<<dists.size()<<endl;
			out_array(x,sz);
			out_array(y,sz);
			return 0;
			//ans();
		}

		x0+=dx[d];
		y0+=dy[d];

		++l;

		if(l == L){
			++spirals;
			if(spirals % 2 == 0)
				++L;
			l = 0;
			d = (d+1) % 4;
		}


	
	}
	throw 7;
	return 0;
}