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

struct NPM
{
    vector<pair<int,int> > p;  // returns root, and current_salary-root_salary
    vector<pair<int,int> > mm; // min && max in group

    NPM(int n)
    {
        p.resize(n);
        mm.resize(n);
        foreach(i,p)
        {
            p[i].first=i;
            p[i].second=0;
            mm[i].first=0;
            mm[i].second=0;
        }
    }
    
    pair<int,int> find(int k)
    {
        if(k==p[k].first) return pair<int,int>(k,0);
        else
        {
            pair<int,int> _=find(p[k].first);
            _.second += p[k].second;
            return p[k]=_;
        }
    }
    
    void un(int x, int y, int delta)
    {
        
        pair<int,int> u=find(x), v=find(y);
        int g=v.first, oldg=u.first;
        if(oldg==find(0).first)
        {
            un(y,x,-delta);
            return;
        }
        p[oldg].first=g; // optimize
        p[oldg].second=delta-u.second+v.second;
        //if(
        mm[g].first = min(mm[g].first,mm[oldg].first+p[oldg].second); // min
        mm[g].second = max(mm[g].second,mm[oldg].second+p[oldg].second); // max
    }
};

int main()
{
    int n,m;
    cin>>n>>m;
    vector<int> z(n,0);
    
    //return 0;
    NPM q(n);
    fo(i,0,m)
    {
        int x,y,d;
        cin>>x>>y>>d;
        //cerr<<x<<" "<<y<<" "<<d<<endl;
        
        cerr.flush();
        pair<int,int> px=q.find(x),py=q.find(y);
        if(px.first==py.first)
            if(d != px.second-py.second)
            {
                cout<<"Impossible after "<<(i+1)<< " statements"<<endl;
                return 0;
            }
            else ;
        else
        {
            q.un(x,y,d);
//             fo(i,0,n)
//             {
//                 q.find(i);
//                 cout<<q.p[i].first<<" "<<q.p[i].second<<endl;
//             }
            //cout<<" ffffff"<<endl;
            int g=q.find(x).first;
            pair<int,int> mmm=q.mm[g];
            int dm=mmm.second-mmm.first;
            if(
                dm>1000000000
                ||
                (g==q.find(0).first
                    &&
                    (mmm.first<0||mmm.second>1000000000)
                )
              )
            {
                cout<<"Impossible after "<<(i+1)<< " statements"<<endl;
                return 0;
            }
        }
    }

//     fo(i,0,n)
//     {
//         q.find(i);
//         cout<<q.p[i].first<<" "<<q.p[i].second<<endl;
//     }
    
    cout<<"Possible"<<endl;
    fo(i,0,n)
    {
        //cerr<<i<<endl;
        int sal=q.find(i).second-q.mm[q.find(i).first].first;
        //int sal=q.find(i).second;
        cout<<sal<<endl;
    }
    
    return 0;
}
