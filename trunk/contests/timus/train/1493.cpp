#include <iostream>
#include <string>

using namespace std;

int sum(int n)
{
    return n/100 + n/10%10 + n%10;
}

bool isLucky(int n)
{
    return sum(n/1000)==sum(n%1000);
}

int main()
{
    int n;
    cin>>n;
    if(isLucky(n-1)||isLucky(n+1))
        cout<<"Yes\n";
    else
        cout<<"No\n";
    return 0;
}
