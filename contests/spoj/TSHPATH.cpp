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
typedef vector<vector<pii> > lists;

const double pi=2*acos(0.0);
const int inf=1000000;

/*
dijkstra, без оптимизации "if(u==finish) break;" - 5.82s
с оптимизацией - 3.78s

set_dijkstra без оптимизации - 10.58
с оптимизацией - 10.74
*/

int set_dijkstra(const lists& G, int start, int finish) // set_dijsktra
{
    // в множестве Q каждая вершина встречается только один раз
    // но тратится некоторое время на удаление
    set<pii> Q;
    vi D(G.size(), inf);
    D[start] = 0;
    Q.insert(pii(0,start));
    while(!Q.empty())
    {
        pii top = *(Q.begin());
        Q.erase(Q.begin());
        int d = top.first, u = top.second;
        if(u==finish) break;
        foreach(j,G[u])
        {
            int v=G[u][j].first, cost=G[u][j].second;
            if(d+cost<D[v])
            {
                if(D[v]!=inf) Q.erase(pii(D[v],v));
                D[v] = d + cost;
                Q.insert(pii(D[v],v));
            }
        }
    }
    return D[finish];
}

int dijkstra(const lists& G, int start, int finish) // priority_queue
{
    // в очереди Q каждая вершина может встречаться несколько раз, но все повторения игнорируются
    priority_queue<pii,vector<pii>,greater<pii> > Q;
    vi D(G.size(), inf);
    D[start] = 0;
    Q.push(pii(0,start));
    while(!Q.empty())
    {
        pii top = Q.top();
        Q.pop();
        int d=top.first, u=top.second;
        if(u==finish) break; // оптимизация если нужно только D[finish]
        if (d>D[u]) continue; // игнорируем повторения
        foreach(j,G[u])
        {
            int v=G[u][j].first, cost=G[u][j].second;
            if(d+cost<D[v])
            {
                D[v] = d + cost;
                Q.push(pii(D[v],v));
            }
        }
    }
    return D[finish];
}

int main()
{
    int tc;
    cin>>tc;
    fo(ti,0,tc)
    {
        map<string,int> cities;
        int n;
        scanf("%d\n",&n);
        //debug(n);
        lists G(n);
        fo(i,0,n)
        {
            char cname[1000];
            scanf("%s\n", cname);
            string name(cname);
            //debug(name);
            cities[name] = i;
            int p;
            scanf("%d\n",&p);
            //debug(p);
            G[i].resize(p);
            foreach(j,G[i])
            {
                int nr,cost;
                scanf("%d %d\n",&nr,&cost);
                G[i][j] = pii(nr-1,cost);
            }
        }
        int r;
        scanf("%d\n",&r);
        fo(i,0,r)
        {
            char cname1[1000], cname2[1000];
            scanf("%s %s\n", cname1, cname2);
            int start = cities[string(cname1)];
            int finish = cities[string(cname2)];
            printf("%d\n", dijkstra(G, start, finish));
        }
    }
    return 0;
}
