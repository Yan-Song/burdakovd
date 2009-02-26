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
#define eps 1e-6

#define KRUG 1
#define KVADRAT 2
#define TREUG 3

using namespace std;

typedef long long i64;
typedef vector<int> VI;

struct figure
{
    int typ;
    int size;
    figure() {}
    figure(int _typ, int sz): typ(_typ), size(sz) {}
};

istream& operator>>(istream& in, figure& f)
{
    in>>f.typ>>f.size;
    return in;
}

bool VLEZET(const figure& K, const figure& f)
{
//     if(K.typ==KRUG&&f.typ==KRUG) return K.size>=f.size;
//     if(K.typ==KRUG&&f.typ==KVADRAT) return 2*K.size>=f.size;
//     if(K.typ==KRUG&&f.typ==TREUG) return 2*K.size>=f.size*sqrt(double(3))/2;
// 
//     if(K.typ==KVADRAT&&f.typ==KRUG) return K.size*sqrt(double(2))>=2*f.size;
//     if(K.typ==KRUG&&f.typ==KVADRAT) return K.size*sqrt(double(2))>=f.size;
//     if(K.typ==KRUG&&f.typ==TREUG) return 2*K.size>=f.size*sqrt(double(3))/2;
    double sz1, sz2;
    if(K.typ==KRUG) sz1=2*K.size;
    if(K.typ==KVADRAT) sz1=sqrt(double(2))*K.size;
    if(K.typ==TREUG) sz1=K.size;

    if(f.typ==KRUG) sz2=2*f.size;
    if(f.typ==KVADRAT) sz2=f.size;
    if(f.typ==TREUG) sz2=sqrt(double(3))/2*f.size;

    //cout<<sz1<<" "<<sz2<<endl;
    return sz1+eps>sz2;
    
}

int main()
{
    figure K,f;
    cin>>K;
    int n,ans=0;
    cin>>n;
    fo(i,0,n)
    {
        cin>>f;
        if(VLEZET(K,f)) ++ans;
    }
    cout<<ans<<endl;
    return 0;
}
