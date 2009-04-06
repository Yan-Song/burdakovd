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

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define forsz(i,start,x) fo(i,start,x.size())
#define foreach(i,x) forsz(i,0,x)
#define showv(v) foreach(i,v) cout<<(i?" ":"")<<v[i]; cout<<endl
#define ALL(v) v.begin(), v.end()
#define STOP -1

using namespace std;

typedef long long i64;
typedef vector<int> VI;

inline bool isdigit(char c)
{
    return c>='0'&&c<='9';
};

inline bool isspace(char c)
{
    return c==' ' || c=='\t' || c=='\n';
};

int main()
{
    enum state { W, F, S, L, E };
    state st=W;
    char c=getc(stdin);
    double s, k;
    //cout<<(int)c<<endl;
    do
    {
        switch(st)
        {
        case W:
            if(c=='.') {s=0; st=F; }
            else if(isdigit(c)) {s=0; st=F; }
            else if(isspace(c)) c=getc(stdin);
            else { st=L; }
            break;
        case F:
            if(c=='.') {k=0.1; c=getc(stdin); st=S; }
            else if(isdigit(c)) { s=s*10+c-'0'; c=getc(stdin); }
            else if(isspace(c)) { cout<<"s="<<s<<endl; st=W; }
            else st=L;
            break;
        case S:
            if(c=='.') st=L;
            else if(isdigit(c)) { s+=k*(c-'0'); k/=10; c=getc(stdin); }
            else if(isspace(c)) { cout<<"s="<<s<<endl; st=W; }
            else st=L;
            break;
        case L:
            if(isspace(c)) st=W;
            else if(c==STOP) st=E;
            else c=getc(stdin);
            break;
        }
    }
    while (st!=E);
    return 0;
}
