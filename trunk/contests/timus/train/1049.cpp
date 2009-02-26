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
#define fori(i,begin,end) for(int i=begin; i<end; i++)
#define foreach(i,x) for(int i=0; i<x.size(); i++)
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl

using namespace std;

typedef long long i64;
typedef vector<int> VI;

vector<int> era(int n)
{
    vector<bool> q(n+2,true);
    fori(i,2,q.size())
       if(q[i])
            for(int j=i+i;j<q.size();j+=i)
                q[j]=false;
    vector<int> ans;
    fori(i,2,q.size())
        if(q[i])
            ans.push_back(i);
    return ans;
}

int main()
{
    
    vector<int> primes=era(10000);
    //showv(primes);
    VI dividors(primes.size(),0);
    fori(i, 0, 10)
    {
        int ai;
        cin>>ai;
        foreach(i, primes)
            while(!(ai%primes[i]))
            {
                ai/=primes[i];
                dividors[i]++;
            }
    }
    //showv(dividors);
    int ans=1;
    foreach(i, dividors)
        ans = ans*(dividors[i]+1)%10;
    cout<<ans<<endl;
    return 0;
}
