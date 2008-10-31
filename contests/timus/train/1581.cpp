#include <iostream>

using namespace std;

int main()
{
    int n, previous, current=-1, count=0;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        previous=current;
        cin>>current;
        if(current==previous) count++;
        else
        {
            if(count>0) cout<<count<<" "<<previous<<" ";
            count=1;
        }
    }
    cout<<count<<" "<<current<<endl;
    return 0;
}
