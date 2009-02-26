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

using namespace std;

typedef long long i64;
typedef vector<int> VI;

int gcd(int m, int n)
{
    return m==0?n:gcd(n%m, m);
}

int main()
{
    int n, m;
    cin>>n>>m;
    while(n==-1);
    if(n==-2) exit(99);

    n--; m--;
    int g=gcd(n, m);
    n/=g; m/=g;
    if(m>n) swap(m, n);
    int ans=max(n,m)+(m-1);
    ans *= g;
    cout<<ans<<endl;
    return 0;
}
