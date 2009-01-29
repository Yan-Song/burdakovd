#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    int n,m,y;
    bool ex = false;
    cin>>n>>m>>y;
    for(int x=0; x<m; x++)
    {
        int p = 1; // не превысит x*m < 1e6
        // пользуюсь тем, что (a*b) mod m == (a*(b mod m)) mod m
        // x^n mod m == x*(x^(n-1) mod m) mod m
        for(int i=0; i<n; i++)
            p = x*p % m;
        if(p==y)
        {
            ex = true;
            cout<<x<<" ";
        }
    }
    if(!ex)
        cout<<"-1";
    cout<<endl;
    return 0;
}
