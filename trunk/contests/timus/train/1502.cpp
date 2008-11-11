#include <iostream>
#include <string>

using namespace std;

int main()
{
    long long n,s=0;
    cin>>n;
    for(long long k=0; k<=n; k++)
        s += (k+n)*(n-k+1)/2 + k*(n-k+1);
    cout<<s<<endl;
    return 0;
}
