#include <iostream>

using namespace std;

int main()
{
    int a, b, d;
    cin>>a>>b;
    d=b-a+1;
    cout<<((d&a&1)?d/2+1:d/2)<<endl;
    return 0;
}
