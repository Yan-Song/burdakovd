#include <iostream>

using namespace std;

int main()
{
    int n, x, maxl=-1000000, minr=1000000, _;
    cin>>n>>x;
    for(int i=0; i<n; i++)
    {
        cin>>_;
        if(_>0) minr = min(minr, _);
        if(_<0) maxl = max(maxl, _);
    }
    if((x>minr)||(x<maxl))
    {
        cout<<"Impossible"<<endl;
        return 0;
    }
    if(x>0)
        cout<<x<<" "<<x-2*maxl<<endl;
    else
        cout<<2*minr-x<<" "<<-x<<endl;
    return 0;
}
