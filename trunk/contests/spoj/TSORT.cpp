#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <complex>

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define fosz(i,s,x) for(int i=s; i<x.size(); i++)
#define foreach(i,x) fosz(i,0,x)
#define debug(x) cerr<<(#x)<<" = "<<(x)<<endl
#define adebug(x,n) fo(i,0,n) cerr<<(#x)<<"["<<i<<"] = "<<x[i]<<endl
#define vdebug(x) foreach(i,x) cerr<<(#x)<<"["<<i<<"] = "<<x[i]<<endl
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()

using namespace std;

typedef long long i64;
typedef unsigned long long u64;
typedef vector<int> vi;
typedef vector<i64> v64;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef complex<double> cd;
typedef vector<cd> vcd;

const double pi=2*acos(0.0);
const int inf=1000000;

int main()
{
    int n;
    scanf("%d\n", &n);

    // first soltion: 2.39s
    /*
    vi v(n);
    foreach(i,v)
        scanf("%d\n", &(v[i]));
    sort(ALL(v));
    foreach(i,v)
        printf("%d\n", v[i]);
    */

    // second solution: 2.20s
    vi q(1<<20, 0);
    fo(i,0,n)
    {
        int _;
        scanf("%d\n", &_);
        ++q[_];
    }
    foreach(i,q)
        fo(j,0,q[i])
            printf("%d\n", i);

    return 0;
}
