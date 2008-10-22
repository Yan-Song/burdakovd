#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int x[100][100];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin>>x[i][j];
    for(int i=0; i<n; i++)
        for(int j=0; j<i+1; j++)
            cout<<x[i-j][j]<<" ";
    for(int i=n; i<2*n-1; i++)
        for(int j=0; j<2*n-1-i; j++)
            cout<<x[n-1-j][i-n+1+j]<<" ";
    //cout<<b-1<<" "<<a-1<<endl;
    return 0;
}
