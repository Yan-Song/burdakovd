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

#define sqr(x) ((x)*(x))

typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef pair<int,int> pii;
typedef long long i64;
typedef pair<double,double> pdd;

const int inf = 1<<26;
const double eps = 1e-9;

pdd BAD(-inf,-inf);

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

const bool OPEN = false;
const bool CLOSE = true;


pair<Vector,Vector> overlap(Point A,Point B,Point C,Point D) // AB inside CD
{
	if(B<A) swap(A,B);
	if(D<C) swap(C,D);
	vector<pair<Vector,bool > > v;
	v.push_back(make_pair(A,OPEN));
	v.push_back(make_pair(B,CLOSE));
	v.push_back(make_pair(C,OPEN));
	v.push_back(make_pair(D,CLOSE));
	sort(v.begin(),v.end());
	int t = 1;
	if(v[1].second == OPEN)
		return make_pair(v[1].first,v[2].first);
	else
		return make_pair(Vector(-inf,-inf),Vector(-inf,-inf));
}


bool bad(pdd O){
	return O.first < -100000;
}

istream& operator>>(istream& in,Vector& A){
	in>>A.x>>A.y;
	return in;
}




pdd intersection(Point A,Point B,Point C,Point D){
	Vector AB = B-A;
	Vector CD = D-C;
	int a1 = AB.x;
	int b1 = -CD.x;
	int c1 = C.x - A.x;
	int a2 = AB.y;
	int b2 = -CD.y;
	int c2 = C.y - A.y;

	int det = a1*b2 - a2*b1;
	if(det == 0) 
		return BAD;
	int det1 = c1*b2 - c2*b1;
	int det2 = a1*c2 - a2*c1;

	if(det < 0){
		det = -det;
		det1 = -det1;
		det2 = -det2;
	}
	if(det1<0 || det1>det || det2<0 ||det2>det) return BAD;
	double x = A.x +AB.x*((det1+0.0)/det);
	double y = A.y + AB.y*((det1+0.0)/det);
	return pdd(x,y);
}

void print(Vector A)
{
	printf("%.10lf %.10lf\n",(double)A.x,(double)A.y);
}


int main(){
	//freopen("in.txt","r",stdin);
	freopen("i.in","r",stdin);
	freopen("i.out","w",stdout);
	Vector A,B,C,D;
	cin>>A>>B>>C>>D;

	Vector AB = B-A;
	Vector CD = D-C;
	Vector AC = C-A;
	Vector AD = D -A;
	if((AC^AD)==0){
		pair<Vector,Vector> O = overlap(A,B,C,D);
		if(O.first.x > -100000)
		{
			print(O.first);
			if(O.first != O.second)
				print(O.second);
			return 0;
		}
	}

	pdd O = intersection(A,B,C,D);
	if(bad(O))
		printf("Empty\n");
	else
		printf("%.10lf %.10lf\n",O.first,O.second);

	return 0;
}