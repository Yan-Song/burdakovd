#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n, _;
    cin>>n;
    double s=0;
    for(int i=0; i<n; i++)
    {
        cin>>_;
        s+=_;
    }
    printf("%.6lf\n", s/n);
    return 0;
}
