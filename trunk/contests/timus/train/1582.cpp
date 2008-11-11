#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    folat k1,k2,k3,s;
    cin>>k1>>k2>>k3;
    s=1000/(1/k1+1/k2+1/k3);
    printf("%.0f\n", s);
    return 0;
}
