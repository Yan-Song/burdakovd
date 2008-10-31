#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n, kmin=2, kmax=10;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        string res;
        int k;
        cin>>k>>res;
        if(res[0]=='s') kmax=min(kmax, k);
        if(res[0]=='h') kmin=max(kmin, k+1);
    }
    if(kmin<=kmax) cout<<kmax<<endl;
    else cout<<"Inconsistent"<<endl;
    return 0;
}
