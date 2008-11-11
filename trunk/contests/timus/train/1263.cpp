#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n, m;
    cin>>n>>m;
    int v[12000];
    for(int i=0; i<n; i++)
        v[i] = 0;
    for(int i=0; i<m; i++)
    {
        int _;
        cin>>_;
        v[_-1]++;
    }
    for(int i=0; i<n; i++)
    {
        float p=100*float(v[i])/m;
        printf("%.2f%%\n", p);
    }
    return 0;
}
