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

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define forsz(i,start,container) fo(i,start,container.size())
#define foreach(i,container) forsz(i,0,container)
#define showv() foreach(i,v) cout<<(i?" ":"")<<v[i]; cout<<endl
#define ALL(container) container.begin(),container.end()

using namespace std;

typedef long long i64;


int main()
{
    i64 n, m;
    cin>>n>>m;
    n*=3;
    fo(i,0,m)
    {
        int _;
        cin>>_;
        n-=_;
        if(n<0)
        {
            cout<<"Free after "<<(i+1)<<" times."<<endl;
            return 0;
        }
    }
    cout<<"Team.GOV!"<<endl;
    return 0;
}
