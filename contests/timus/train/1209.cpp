#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    long n, k, d;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>k;
        k=(k-1)*2;
        d=long(floor(sqrt(double(k))));
        cout<<((d*(d+1)==k)?1:0)<<" ";
    }
    cout<<endl;
    return 0;
}
