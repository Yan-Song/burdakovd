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
    i64 n;
    cin>>n;
    i64 d=2, m=1, k=1;
    while(n>1)
    {
        int c=0;
        while(n%d==0)
        {
            ++c;
            n/=d;
        }
        int mc,nc;
        if(c%2)
        {
            mc=(c+3)/2;
            nc=1;
        }
        else
        {
            mc=c/2;
            nc=0;
        }
        fo(i,0,mc) m*=d;
        fo(i,0,nc) k*=d;
        ++d;
    }
    cout<<m<<endl<<k<<endl;
    return 0;
}
