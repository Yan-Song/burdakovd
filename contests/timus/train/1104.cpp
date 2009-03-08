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

bool check(vector<int> num, int base)
{
    int _=0;
    foreach(i, num)
        if(num[i]<base)
            _ = (_*base + num[i]) % (base-1);
        else
            return false;
    return _==0;
}

int main()
{
    char q[2000000];
    scanf("%s", q);
    
    vector<int> num(strlen(q));
    foreach(i, num)
        num[i] = q[i]<'A' ? q[i]-'0' : q[i]-'A'+10;
    
    fo(i,2,37)
        if(check(num, i))
        {
            cout<<i<<endl;
            return 0;
        }
    cout<<"No solution."<<endl;
    return 0;
}
