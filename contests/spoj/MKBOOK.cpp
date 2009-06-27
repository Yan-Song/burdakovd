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
    int a,b;
    for(int _case=1; ; ++_case)
    {
        scanf("%d %d\n", &a, &b);
        if(!a) break;
        vi v(10,0);
        for(int p=min(a,b); p<=max(a,b); p++)
        {
            int pp=p;
            while(pp>0)
            {
                ++v[pp%10];
                pp /= 10;
            }
        }
        printf("Case %d:", _case);
        foreach(j,v)
            printf(" %d:%d", j, v[j]);
        printf("\n");
    }
    return 0;
}
