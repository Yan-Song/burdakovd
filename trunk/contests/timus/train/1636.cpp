#include <iostream>
#include <string>

using namespace std;

int main()
{
    int t1, t2, _;
    cin>>t1>>t2;
    for(int i=0; i<10; i++)
    {
        cin>>_;
        t2 -= _*20;
    }
    if(t1<=t2)
        cout<<"No chance.\n";
    else
        cout<<"Dirty debug :(\n";
    return 0;
}
