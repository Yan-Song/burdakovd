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
typedef long long i64;

#define eps 0.000000001

using namespace std;

int main()
{
    i64 n=1;
    double p,q;
    cin>>p>>q;
    //p/=100;
    //q/=100;

    int P=floor(p*100+0.5);
    int Q=floor(q*100+0.5);
    
    while(true)
    {
        ++n;
        for(i64 j=0; j<n; j++)
            if((j*10000>P*n)&&(j*10000<Q*n))
            {
                cout<<n<<endl;
                return 0;
            }
        //cout<<"("<<n<<") ("<<p*n<<", "<<q*n<<")"<<endl;
    }
    cout<<n<<endl;
    return 0;
}
