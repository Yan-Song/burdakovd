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

int main()
{
    int n, q[61000];
    cin>>n;
    q[0] = 0;
    for(int i=1; i<=n; i++)
    {
        int m=1000000;
        for(int j=1; j*j<=i; j++)
            if(m>q[i-j*j])
                m = q[i-j*j];
        q[i] = m+1;
    }
    cout<<q[n]<<endl;
    return 0;
}
