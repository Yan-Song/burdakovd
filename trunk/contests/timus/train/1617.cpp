#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int d[800];
    for(int i=0; i<800; i++)
        d[i] = 0;
    for(int i=0; i<n; i++)
    {
        int _;
        cin>>_;
        d[_]++;
    }
    int res=0;
    for(int i=0; i<800; i++)
        res += (d[i]/4);
    cout<<res<<endl;
    return 0;
}
