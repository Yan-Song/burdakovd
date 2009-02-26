#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#pragma comment(linker, "/STACK:16777216")

using namespace std;

char plusminus(bool b)
{
    return b?'+':'-';
}

void an(int n)
{
    bool pm=false;
    for(int i=1; i<=n; i++)
    {
        cout<<"sin("<<i;
        if(i<n) cout<<plusminus(pm);
        pm=not pm;
    }
    for(int i=0; i<n; i++)
        cout<<")";
}

int main()
{
    int n;
    cin>>n;
    for(int i=1; i<n; i++)
        cout<<"(";
    for(int i=1; i<=n; i++)
    {
        if(i>1) cout<<")";
        an(i);
        cout<<"+"<<(n+1-i);
    }
    cout<<endl;
    return 0;
}
