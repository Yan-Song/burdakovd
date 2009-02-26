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


int main()
{
    double v,a,k,pi=3.1415926535;
    /* физика + формула суммы геометрической прогрессии */
    cin>>v>>a>>k;
    double s=v*v*sin(2*a*pi/180.0)/10.0/(1-1/k);
    printf("%.2lf", s);
    return 0;
}
