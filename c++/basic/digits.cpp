#include <iostream>
using namespace std;

int main ()
{
    char c;
    bool first=true;
    while(cin>>c)
    {
        if(first)
            first=false;
        else
            cout<<' ';
        cout<<c;
    }
    return 0;
}
