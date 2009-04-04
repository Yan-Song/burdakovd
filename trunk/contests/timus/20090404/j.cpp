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

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define foreach(i,x) for(int i=0; i<x.size(); i++)
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()

using namespace std;

typedef long long i64;
typedef vector<int> VI;

struct PenguinAvia
{
    i64 n,d,a;
    vector<string> x;
    vector<bool> were,rwere;
    vector<pair<int,int> > del;
    vector<int> add;
    vector<int> cur;

    bool _reach(int u, int v)
    {
        if(u==v) return true;
        rwere[u]=true;
        foreach(i,x[u])
            if(x[u][i]=='1'&&!rwere[i]&&_reach(i,v)) return true;
        return false;
    }
    
    bool reachable(int u, int v)
    {
        rwere.resize(100);
        foreach(i,rwere) rwere[i]=false;
        return _reach(u,v);
    }
    
    int dfs(int s, vector<bool>& were)
    {
        were[s]=true;
        cur.push_back(s);

        int ans=0;
        foreach(i,x[s])
            if(x[s][i]=='1'&&!were[i])
                ans+=dfs(i, were);
        return ans;
    }
    
    void solve(int s)
    {
        cur.clear();
        dfs(s, were);
        add.push_back(s);
        foreach(i,cur)
            foreach(j,cur)
                if(x[cur[i]][cur[j]]=='1')
                {
                    int u=cur[i], v=cur[j];
                    x[u][v]=x[v][u]='0';
                    if(reachable(u,v))
                        del.push_back(pair<int,int>(u,v));
                    else
                        x[u][v]=x[v][u]='1';
                }
    }
    
    void main()
    {
        cin>>n>>d>>a;
        x.resize(n);
        were.resize(n);

        foreach(i,x)
        {
            cin>>x[i];
            were[i]=false;
        }
        
        fo(i,0,n)
            if(!were[i])
                solve(i);

        vector<string> ans(n,string(n,'0'));
        foreach(i,del)
        {
            ans[del[i].first][del[i].second] = 'd';
            ans[del[i].second][del[i].first] = 'd';
        }
        fo(i,1,add.size())
        {
            ans[add[0]][add[i]] = 'a';
            ans[add[i]][add[0]] = 'a';
        }
        cout<<(d*del.size()+a*(add.size()-1))<<endl;
        foreach(i,ans)
            cout<<ans[i]<<endl;
    }
};

int main()
{
    PenguinAvia s;
    s.main();
    return 0;
}
