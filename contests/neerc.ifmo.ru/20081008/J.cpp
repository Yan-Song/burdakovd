#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

int main()
{
    freopen ("logo.out", "w", stdout);
    freopen ("logo.in", "r", stdin);
    int tc;
    cin>>tc;
    for(int tcc=0; tcc<tc; tcc++)
    {
        int n;
        cin>>n;
        double x=0, y=0, a=0;
        for(int i=0; i<n; i++)
        {
            string s;
            double p;
            cin>>s>>p;
            if(s[1]=='t') //turning
            {
                if(s[0]=='r') //right
                    p=-p;
                // will turn to p degrees;
                a += p/180*3.1415926535897934;
            }
            else // moving
            {
                if(s[0]=='b') // backward
                    p=-p;
                x += p*cos(a);
                y += p*sin(a);
            }
            //cout<<"step #"<<i+1<<", x="<<x<<", y="<<y<<", a="<<a/2/3.14*360<<endl;
        }
        cout<<(int)round(sqrt(x*x+y*y))<<endl;
    }
    return 0;
}
