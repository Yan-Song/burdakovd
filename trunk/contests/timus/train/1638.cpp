#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
    int t, p, n1, n2, s, f;
    cin>>t>>p>>n1>>n2;
    s = n1*(t+2*p)-p;
    f = (n2-1)*(t+2*p)+p;
    cout<<abs(s-f)<<endl;
    return 0;
}
