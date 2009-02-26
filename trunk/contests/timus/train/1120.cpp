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
    int n;
    cin>>n;
    for(int p=1000000; p>0; p--)
        if(2*n%p==0)
        {
            int a = 2*n/p+1-p;
            if(a%2>0) continue;
            if(a<=0) continue;
            a /= 2;
            cout<<a<<" "<<p<<endl;
            return 0;
        }
    return 1;
}
