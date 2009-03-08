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

int main()
{
    int y,n,q;
    cin>>y>>n>>q;
    string trash;
    getline(cin, trash);
    set<string> us;
    fo(i,0,n)
    {
        string team,u;
        getline(cin, team);
        if(team.find('#')==string::npos)
            u=team;
        else
            u=team.substr(0,team.find('#')-1);
        if(!us.count(u))
        {
            if(q==0) // мест не осталось
            {
                cout<<team<<endl;
                return 0;
            }
            --q;
            us.insert(u);
            //cout<<":) "<<team<<endl;
        }
    }
    throw "хрень";
    return 0;
}
