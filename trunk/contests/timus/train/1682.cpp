#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define forsz(i,start,container) fo(i,start,container.size())
#define foreach(i,container) forsz(i,0,container)
#define showv(v) foreach(i,v) cout<<(i?" ":"")<<v[i]; cout<<endl
#define ALL(container) container.begin(),container.end()

using namespace std;

typedef long long i64;

struct SetForest
{
    vector<int> rank, p;

    void Append()
    {
        rank.push_back(0);
        p.push_back(p.size());
    }

    int FindSet(int x)
    {
        return p[x]==x ? x : p[x]=FindSet(p[x]);
    }

    void Union(int x, int y)
    {
        //cout<<"Объединяем "<<x<<" и "<<y<<endl;
        int xs=FindSet(x), ys=FindSet(y);
        if(rank[xs]<rank[ys])
            p[xs]=ys;
        else
        {
            p[ys]=xs;
            if(rank[xs]==rank[ys])
                ++rank[xs];
        }
    }
};

int solve(i64 k)
{
    vector< vector<i64> > mods(k), mods2(k);
    SetForest f;
    f.Append(); // 0

    for(i64 n=1; ; n++)
    {
        f.Append(); // n
        i64 mod=n%k, mod2=n%k*n%k;
        
        i64 required_mod = (k-mod2)%k;
        i64 required_mod2 = (k-mod)%k;
        
        vector<int> near;
        foreach(i,mods[required_mod])
            near.push_back(mods[required_mod][i]);
        foreach(i,mods2[required_mod2])
            near.push_back(mods2[required_mod2][i]);

        sort(ALL(near));
        near.resize(unique(ALL(near))-near.begin());

        foreach(i,near)
            if(f.FindSet(n)==f.FindSet(near[i]))
                return n;
            else
                f.Union(n,near[i]);
        
        mods[mod].push_back(n);
        mods2[mod2].push_back(n);
    }
    throw "o_O";
}

int main()
{
    i64 k;
    cin>>k;
    cout<<solve(k)<<endl;
    return 0;
}
