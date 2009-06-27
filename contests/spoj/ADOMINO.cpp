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

bool possible(v64& p, i64 d, i64 dist)
{
    i64 prev=-1e9,pos=0;
    fo(i,0,d)
    {
        while(pos<p.size() && p[pos]-prev<dist) ++pos;
        if(pos==p.size()) return false;
        prev = p[pos];
    }
    return true;
}

int main()
{
    int tc;
    scanf("%d\n", &tc);
    fo(t,0,tc)
    {
        i64 n,d;
        scanf("%lld %lld\n", &n, &d);
        v64 p(n);
        foreach(j,p)
            scanf("%lld\n", &p[j]);
        sort(ALL(p));
        // binary search
        i64 left=0, right=1e9+1;
        while(left!=right-1) // left <= answer < right
        {
            i64 middle = (left + right) / 2;
            if(possible(p,d,middle))
                left = middle;
            else
                right = middle;
        }
        printf("%lld\n", left);
    }
    return 0;
}
