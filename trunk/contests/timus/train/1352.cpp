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
    int ans[38]={2,3,5,7,13,17,19,31,61,89,107,127,521,607,1279,2203,2281,3217,4253,
            4423,9689,9941,11213,19937,21701,23209,44497,86243,110503,132049,
            216091,756839,859433,1257787,1398269,2976221,3021377,6972593};
    int t;
    cin>>t;
    fo(i,0,t)
    {
        int _;
        cin>>_;
        cout<<ans[_-1]<<endl;
    }
    return 0;
}
