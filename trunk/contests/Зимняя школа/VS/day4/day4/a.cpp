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
const double eps = 1e-6;

#define sqr(x) ((x)*(x))


//#pragma comment(linker,"/stack:64000000")

const int maxN = 120;


int x[maxN],y[maxN],w[maxN];
int N=100,K=100,R=0;

struct Vector{
	double x,y;

	double length() { return sqrt(sqr(x)+sqr(y)+0.0); }
	double length2() { return sqr(x) + sqr(y); }

	Vector() { x = 0; y = 0; }
	Vector(double xx,double yy) { x=xx; y = yy;}

	Vector operator+(const Vector& B) const{
		return Vector(x+B.x,y+B.y);
	}

	Vector operator-(const Vector& B) const{
		return Vector(x-B.x,y-B.y);
	}
	Vector operator*(double a) const{
		return Vector(a*x,a*y);
	}

	void normalize(){
		double abso = length();
		x/= abso;
		y/= abso;
	}

	double operator%(const Vector& B) const{
		return x*B.x + y*B.y;
	}
	double operator^(const Vector& B) const{
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

inline bool can(double r,int i){
	int ret = 0;

	for(int j = 0; j < N; ++j){
		if(sqr(x[i]-x[j])+sqr(y[i]-y[j])<=r*r+eps)
			ret+=w[j];
		if(ret>=K) return true;
	}
	return false;
}

inline bool can(double& r,double& Ox,double& Oy){
	int ret = 0;

	double r2 = r*r + eps;
	for(int j = 0; j < N; ++j){
		if(sqr(Ox-x[j]) + sqr(Oy-y[j])<=r2)
			ret+=w[j];
		if(ret>=K) return true;
	}
	return false;
}

inline bool can(double r,int i,int j){
	if(x[i]==x[j] && y[i] == y[j])
		return false;
/*
	Vector A(x[i],y[i]);
	Vector B(x[j],y[j]);

	Vector AB = B-A;
	Vector O = A + (AB*0.5);
	Vector norm(AB.y,-AB.x);
	norm.normalize();

	double len = sqrt(r*r - AB.length2()/4);
	Vector O1 = O + (norm*len);
	Vector O2 = O - (norm*len);
*/
	int ABx = x[j] - x[i];
	int ABy = y[j] - y[i];
	double Ox = (x[i] + x[j])*0.5;
	double Oy = (y[i] + y[j])*0.5;
	int NormX = ABy;
	int NormY = -ABx;
	
	int ABlen2 = sqr(ABx) + sqr(ABy);
	double len =sqrt(ABlen2 +0.0);

	//if(ABlen2 > 4*r*r - eps) return false;

	double len1 = sqrt(r*r - ABlen2*0.25) /len;
	double O1x = Ox + NormX *len1;
	double O1y = Oy + NormY *len1;

	double O2x = Ox - NormX *len1;
	double O2y = Oy - NormY *len1;
	

	return can(r,O1x,O1y) || can(r,O2x,O2y);
}



bool can(double r){
	for(int i = 0; i < N; ++i){
		if(can(r,i))
			return true;
		for(int j = i+1; j < N;++j)
			if(can(r,i,j))
				return true;
	}
	return false;
}

int main(){
//freopen("in.txt","r",stdin);
freopen("a4.in","r",stdin);
freopen("a4.out","w",stdout);
	scanf("%d %d %d",&N,&R,&K);
	int wsum = 0;
	for(int i = 0; i < N; ++i)
	{
		scanf("%d %d %d",&x[i],&y[i],&w[i]);
		//x[i] = i;
		//y[i] = i;
		//w[i] = 1;
		wsum+=w[i];
	}

	if(wsum < K){
		printf("-1");
		return 0;
	}

	double left = 0, right = 1500;
	srand(17);

	while(fabs(left-right)>=eps){
		double r = left + (right-left)*((rand()%1000)*0.001);
		if(can(r))
			right = r;
		else
			left = r;
	}

	printf("%.6lf",(left+right)/2.0+R);



	return 0;
}