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

int gcd(int a, int b)
{
    while(true)
    {
        a = a % b;
        if( a == 0 )
            return b;
        b = b % a;
        if( b == 0 )
            return a;
    }
}

int lcm(int a, int b)
{
    return a*b / gcd(a,b);
}

int main()
{
    int n, ans=1;
    int p[1200];
    bool b[1200];
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>p[i];
        b[i] = true;
    }
    for(int i=1; i<=n; i++)
        if(b[i])
        {
            int j=i, cycle=0;
            while(b[j])
            {
                b[j] = false;
                cycle++;
                j = p[j];
            }
            ans = lcm(ans, cycle);
        }
    cout<<ans<<endl;
    return 0;
}
