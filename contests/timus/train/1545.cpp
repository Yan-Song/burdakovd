#include <iostream>
#include <string>
//#include 

using namespace std;

int main()
{
    int n;
    cin>>n;
    string ie[1000];
    for(int i=0; i<n; i++)
        cin>>ie[i];
    char c;
    cin>>c;
    for(int i=0; i<n; i++)
        if(ie[i][0]==c)
            cout<<ie[i]<<endl;
    return 0;
}
