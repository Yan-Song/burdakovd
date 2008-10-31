#include <iostream>

using namespace std;

int main()
{
    int n, first, current, firstd, currentd;
    cin>>n;
    first=n*(n-1)/2+1;
    firstd=n-1;
    for(int i=0; i<n; i++)
    {
        current=first;
        currentd =firstd;
        for(int j=0; j<n; j++)
        {
            cout<<current<<" ";
            int d=(currentd<n) ? currentd : 2*n-1-currentd;
            currentd--;
            current -= d;
        }
        firstd++;
        first += n-i;
        cout<<endl;
    }
    return 0;
}
