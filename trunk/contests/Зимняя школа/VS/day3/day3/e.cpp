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

struct Point{
	int x,y;
	Point(int xx,int yy) { x = xx; y = yy; }
};
struct Segment{
	Point a,b;
	Segment(Point aa,Point bb):a(aa),b(bb) {}
	bool operator<(const Segment& B) const {
		return a.x < B.b.x;
	}
};

int main(){
//freopen("in.txt","r",stdin);
freopen("e.in","r",stdin);
freopen("e.out","w",stdout);
	int n;
	scanf("%d",&n);
	int x1,x2,y1,y2;
	vector<Segment> segs;
	for(int i = 0; i < n ; ++i)
	{
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		if(y1>y2) swap(y1,y2);
		segs.push_back(Segment(Point(x1,y1),Point(x1,y2)));
		segs.push_back(Segment(Point(x2,y1),Point(x2,y2)));
	}
	sort(segs.begin(),segs.end());
	
	map<int,bool> mp;
	int ans = 0;
	for(int i = 0; i < segs.size();++i)
	{
		int y = segs[i].a.y;

		if(mp.find(y) != mp.end()){
			mp.erase(segs[i].b.y);
			if(segs[i].a.y != segs[i].b.y){
				mp.erase(segs[i].a.y);
			}
		}
		else
		{

			map<int,bool>::iterator it = mp.lower_bound(y);
			if(it==mp.end() || it->second == true)
			{
				++ans;
				
				
				if(segs[i].a.y != segs[i].b.y)
					mp[segs[i].b.y] = false;
			
				mp[segs[i].a.y] = true;

			}
		}
	}
	printf("%d\n",ans);

	return 0;
}