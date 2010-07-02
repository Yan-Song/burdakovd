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

//#include <ctime>

using namespace std;

typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef pair<int,int> pii;
typedef long long i64;

const int inf = 1<<26;
const double eps = 1e-9;

#define sqr(x) ((x)*(x))
#pragma comment(linker,"/stack:64000000")


int lineX;

struct Triple{
	int x, y;
	bool begin;
	int segment_number;
	Triple() {}
	Triple(int x1,int y1,bool beg,int seg):x(x1),y(y1),begin(beg),segment_number(seg){}
};

struct Vector{
	int x,y;

	double length() { return sqrt(sqr(x)+sqr(y)+0.0); }
	int length2() { return sqr(x) + sqr(y); }

	Vector() { x = 0; y = 0; }
	Vector(int xx,int yy) { x=xx; y = yy;}

	Vector operator+(Vector& B){
		return Vector(x+B.x,y+B.y);
	}

	Vector operator-(Vector& B){
		return Vector(x-B.x,y-B.y);
	}

	int operator%(Vector& B){
		return x*B.x + y*B.y;
	}
	int operator^(Vector& B){
		return  x*B.y - y*B.x;
	}

	bool operator<(const Vector& B) const{
		return x<B.x || x==B.x && y<B.y;
	}

	bool operator!=(const Vector& B) const{
		return x!=B.x || y!=B.y;
	}

	
};
typedef Vector Point;


struct Segment{
	Point a,b;
	Segment(){}
	Segment(Point aa,Point bb):a(aa),b(bb) {}
	bool operator<(const Segment& B) const {
		return a.x < B.b.x;
	}
};


vector<Segment> segs;
vector<Triple> triples;


bool inside(Vector& O,Vector& A,Vector& B){
	return  O.x <= max(A.x,B.x) && O.x >= min(A.x,B.x) && O.y <= max(A.y,B.y) && O.y >= min(A.y,B.y);
}

inline int sgn(int x){
	if(x==0) return 0;
	return x>0?1:-1;
}

bool intersects(int i,int j){
	Vector& A = segs[i].a;
	Vector& B = segs[i].b;
	Vector& C = segs[j].a;
	Vector& D = segs[j].b;


	Vector AB = B-A;
	Vector AC = C-A;
	Vector AD = D-A;
	Vector BD = D-B;
	Vector CD = D-C;
	int d1 = AC^AB;
	int d2 = AD^AB;
	int d3 = AD^CD;
	int d4 = BD^CD;
	if(d1 == 0 && inside(C,A,B) || d2 == 0&& inside(D,A,B) || d3 == 0 && inside(A,C,D) || d4 == 0 && inside(B,C,D)){
		return true;
	}
	return sgn(d1)*sgn(d2) < 0 && sgn(d3) * sgn(d4) < 0;
}

void showsegs()
{
	cout << "	segs:"<<std::endl;
	for(int i = 0; i < segs.size(); ++i)
		printf("%d %d %d %d\n", segs[i].a.x, segs[i].a.y, segs[i].b.x, segs[i].b.y);
}

void check()
{
	return;
	bool fail = false;
	for(int i = 0; i < segs.size(); ++i)
		for(int j = 0; j < i; ++j)
			if(intersects(i, j))
			{
				std::cerr << "FAIL!!! " << i << ", " << j <<" intersects" << std::endl;
				fail = true;
			}

	if(fail)
		showsegs();
}

void check(const int i, const int j)
{
	return;
	bool fail = false;
	if(!intersects(i, j))
	{
		std::cerr << "FAIL!!! " << i << ", " << j <<" not intersects" << std::endl;
		fail = true;
	}

	if(fail)showsegs();
}

void YES(int i,int j){
	printf("YES\n%d %d",i+1,j+1);
	check(i, j);
	exit(0);
}

void NO(){
	printf("NO");
	check();
	exit(0);
}


bool cmpX(const Triple& T1,const Triple& T2){
	return T1.x<T2.x || T1.x == T2.x && T1.y < T2.y || T1.x == T2.x && T1.y == T2.y && T1.begin > T2.begin ||
		T1.x == T2.x && T1.y == T2.y && T1.begin == T2.begin && T1.segment_number < T2.segment_number;
}






int currentX;

struct setCmp{
bool operator()(const Triple& T1,const Triple& T2) const{
	const Segment& AB = segs[T1.segment_number];
	const Segment& CD = segs[T2.segment_number];
	
	const Point& A = AB.a;
	const Point& B = AB.b;

	const Point& C = CD.a;
	const Point& D = CD.b;

	const i64 x = currentX;

//	double y1 = A.y + (x-A.x)*(B.y-A.y)*(0.0+D.x-C.x);
//	double y2 = C.y + (x-C.x)*(D.y-C.y)*(0.0+B.x-A.x);

//	return y1<y2;

	return ((x - A.x)*(B.y-A.y)+A.y*(B.x-A.x))*(D.x-C.x)  < ((x - C.x)*(D.y-C.y)+C.y*(D.x-C.x))*(B.x-A.x);
}
};


const int maxN = 125000;
const int maxXY = 10000;

int main(){
//freopen("in.txt","r",stdin);
freopen("c1.in","r",stdin);
freopen("c1.out","w",stdout);
	//srand(time(0));

	int n = rand() % maxN;
	scanf("%d",&n);
	segs.resize(n);
	triples.resize(2*n);
	int x1,y1,x2,y2;
	for(int i = 0; i < n; ++i){
		//x1 = rand() % (2*maxXY) - maxXY;
		//y1 = rand() % (2*maxXY) - maxXY;
		//x2 = rand() % (2*maxXY) - maxXY;
		//y2 = rand() % (2*maxXY) - maxXY;
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		if(x1 > x2) { swap(x1,x2); swap(y1,y2); }
		if(x1 ==  x2 && y1>y2) { swap(y1,y2); }
		segs[i] = Segment(Point(x1,y1),Point(x2,y2));
		triples[2*i] = Triple(x1,y1,true,i);
		triples[2*i+1] = Triple(x2,y2,false,i);
	}
	
	set<Triple,setCmp> st;
	set<Triple,setCmp>::iterator it;
	set<Triple,setCmp>::iterator it1;
	sort(triples.begin(),triples.end(),cmpX);

	for(int i = 0; i < triples.size(); ++i){
		currentX = triples[i].x;
		if(triples[i].begin == true){

			it = st.lower_bound(triples[i]);
			it1 = it;

			if(it!=st.begin()) 
				it1--;

			vector<Triple> neigb;
			if(it!=st.end())
				neigb.push_back(*it);
			if(it1!=st.end() && it1!=it)
				neigb.push_back(*it1);

			for(int j = 0; j < neigb.size(); ++j)
				if(intersects(neigb[j].segment_number,triples[i].segment_number))
					YES(neigb[j].segment_number,triples[i].segment_number);

			st.insert(triples[i]);				
		}else{

			st.erase(Triple(triples[i].x,triples[i].y,true,triples[i].segment_number));

			it = st.lower_bound(triples[i]);
			it1 = it;

			if(it!=st.begin()) 
				it1--;

			vector<Triple> neigb;
			if(it!=st.end())
				neigb.push_back(*it);
			if(it1!=st.end() && it1!=it)
				neigb.push_back(*it1);

			for(int j = 0; j < neigb.size(); ++j)
				if(intersects(neigb[j].segment_number,triples[i].segment_number))
					YES(neigb[j].segment_number,triples[i].segment_number);

			if(neigb.size() == 2 && intersects(neigb[0].segment_number,neigb[1].segment_number))
				YES(neigb[0].segment_number,neigb[1].segment_number);

		}

	}

	NO();
	

	return 0;
}