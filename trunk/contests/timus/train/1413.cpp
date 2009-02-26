#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define foreach(i,x) for(int i=0; i<x.size(); i++)
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()

using namespace std;

typedef long long i64;
typedef vector<int> VI;

struct Vector
{
    int x,y,xq2,yq2;
    Vector(): x(0), y(0), xq2(0), yq2(0) {};
    Vector(int xx, int yy, int xq, int yq): x(xx), y(yy), xq2(xq), yq2(yq) {};
    Vector operator+=(const Vector& v)
    {
        x+=v.x;
        y+=v.y;
        xq2+=v.xq2;
        yq2+=v.yq2;
        return *this;
    }
    void print() const
    {
        double xx=double(x)+sqrt(double(0.5))*xq2;
        double yy=double(y)+sqrt(double(0.5))*yq2;
        printf("%.10lf %.10lf\n", xx, yy);
    }
};

Vector solve(const string& code)
{
    Vector pos;
    Vector mv[10] = { Vector(),
            Vector(0,0,-1,-1), Vector(0,-1,0,0), Vector(0,0,1,-1),
            Vector(-1,0,0,0), Vector(0,0,0,0), Vector(1,0,0,0),
            Vector(0,0,-1,1), Vector(0,1,0,0), Vector(0,0,1,1)
            };
    foreach(i, code)
    {
        pos += mv[code[i]-'0'];
        if(code[i]=='0') return pos;
    }
    return pos;
}

int main()
{
    /*
    обратить внимание, что на string code; cin>>code - получал стабильный TLE
    */
    char cs[1200000];
    scanf("%s", cs);
    string code=string(cs);
    solve(code).print();
    return 0;
}
