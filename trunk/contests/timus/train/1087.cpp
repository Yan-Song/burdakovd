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
    int n,m;
    cin>>n>>m;
    vector<int> k(m);
    foreach(j,k)
        cin>>k[j];
    vector<bool> dp(n);
    dp[0]=true; // выигрывает первый игрок,
    // так как второй только что взял последние камни
    fo(i,1,n+1)
    {
        dp[i]=false;
        foreach(j,k)
            if(i-k[j]>=0&&!dp[i-k[j]])
            {
                dp[i]=true;
                break;
            }
    }
    cout<<(dp[n]?1:2)<<endl;
    return 0;
}
