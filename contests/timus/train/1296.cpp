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
    /* найти часть последовательности с маккс суммой

    идея: пусть P[i]=p[1]+p[2]+...+p[i]

    далее Q[i]=min(P[0], P[1],...,P[i])

    Ans = max(P[i]-Q[i]), i=0..N

    всё это находится за линейное время и даже за один проход
    */
    i64 n,P=0,Q=0,ans=0,p;
    cin>>n;
    fo(i,0,n)
    {
        cin>>p;
        P+=p;
        Q=min(Q,P);
        ans=max(ans,P-Q);
    }
    cout<<ans<<endl;
    return 0;
}
