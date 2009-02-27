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

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define foreach(i,x) for(int i=0; i<x.size(); i++)
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()
#define forit(it, data) for(typeof(data)::iterator it=data.begin(); it<data.end(); ++it)

using namespace std;

typedef long long i64;
typedef vector<int> VI;


int main()
{
    int n,N;
    cin>>n;
    N=(1<<n);
    map<string,int> prefs;
    fo(i,0,N)
    {
        string name, pref;
        cin>>name>>pref;
        ++prefs[pref];
    }
    int m=0;
    for(map<string,int>::iterator it=prefs.begin(); it!=prefs.end(); ++it)
        m=max(m,it->second);
    int q=1, ans=n;
    while(q<m)
    {
        --ans;
        q=q<<1;
    }
    cout<<ans<<endl;
    return 0;
}
