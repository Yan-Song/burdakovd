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

const int inf = 1<<26;
const double eps = 1e-9;

struct Vector{
	int x,y;

	int length() { return sqrt(sqr(x)+sqr(y)+0.0); }
	int length2() { return sqr(x) + sqr(y); }

	Vector() { x = 0; y = 0; }
	Vector(int xx,int yy) { x=xx; y = yy;}

	Vector operator+(Vector& B){
		return Vector(x+B.x,y+B.y);
	}

	Vector operator-(Vector& B){
		return Vector(x-B.x,y-B.y);
	}



};

int main(){
//freopen("in.txt","r",stdin);
//freopen("in.txt","r",stdin);
//freopen("out.txt","w",stdout);
	return 0;
}