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

string pal(string old)
{
    string ans=old;
    for(int i=ans.size()/2; i<ans.size(); i++)
        ans[i] = ans[ans.size()-1-i];
    return ans;
}

int main()
{
    string s,old;
    cin>>old;
    s=pal(old);
    if(s<old)
    {
        /* заметим что увеличивать разрядность никогда не придётся,
        т.к 999...999 - палиндром,

        из того же следует что сейчас в левой половине строки сейчас найдётся
        цифра меньшая 9 */
        int p=old.size()/2;
        if(old.size()%2==0) --p;
        
        while(old[p]=='9')
        {
            old[p]='0';
            --p;
        }
        old[p]++;
        s=pal(old);
    }
    cout<<s<<endl;
    return 0;
}
