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
#include <cassert>
 
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
typedef vector<vi> vvi;
typedef vector<i64> v64;
typedef vector<i64> vv64;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
 
const double pi=2*acos(0.0);
const int inf=1<<25;

bool good(const vi& data)
{
    foreach(i, data)
        if(data[i] > i + 1)
            return false;
    return true;
}

int solve(const vi& data)
{
    set<vi> visited;

    queue< pair<vi, int> > q;

    q.push(pair<vi,int>(data, 0));

    visited.insert(data);
    
    while(!q.empty())
    {
        vi cur = q.front().first;
        int cnt = q.front().second;
        int n = cur.size();
        q.pop();
      
        if(good(cur))
            return cnt;

        for(int i=1; i<n; ++i)
        {
            if(cur[i-1]<cur[i])
                continue;

            swap(cur[i-1], cur[i]);

            if(visited.count(cur)==0)
            {
                visited.insert(cur);
                q.push(pair<vi,int>(cur, cnt+1));
            }

            swap(cur[i-1], cur[i]);
        }
    }

    throw "o_O";
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int t;
    cin>>t;
    for(int cas=1; cas<=t; ++cas)
    {
        int n;
        cin>>n;
        vi data(n, 0);
        for(int i=0; i<n; ++i)
        {
            string _;
            cin>>_;
            foreach(j, _)
                if(_[j] == '1')
                    data[i] = j + 1;
        }
        cout<<"Case #"<<cas<<": "<<solve(data)<<endl;
        cerr<<"Case #"<<cas<<": "<<solve(data)<<endl;
    }
    return 0;
}
