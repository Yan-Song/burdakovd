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
    int n,k;
    cin>>n>>k;
    vector<int> fibo(n+1);
    k--;
    fibo[0]=1;
    fibo[1]=2;
    fo(i,2,n+1)
        fibo[i]=fibo[i-1]+fibo[i-2];
    if(k>=fibo[n])
    {
        cout<<-1<<endl;
        return 0;
    }
    while(n>0)
    {
        if(k<fibo[n-1])
            cout<<0;
        else
        {
            k-=fibo[n-1];
            cout<<1;
        }
        --n;
    }
    cout<<endl;
    return 0;
}
