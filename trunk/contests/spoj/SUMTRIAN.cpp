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
typedef vector<vi> vvi;

const double pi=2*acos(0.0);
const int inf=1e9;

int main()
{
    int tc;
    scanf("%d\n",&tc);
    fo(t,0,tc)
    {
        int n;
        scanf("%d\n",&n);
        vvi t(n);
        foreach(j,t)
        {
            t[j].resize(j+1);
            foreach(k,t[j])
                scanf("%d",&t[j][k]);
            scanf("\n");
        }
        for(int i=t.size()-2; i>=0; i--)
            for(int j=i; j>=0; j--)
                t[i][j] += max(t[i+1][j], t[i+1][j+1]);
        cout<<t[0][0]<<endl;
    }
    return 0;
}
