#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int main()
{
    int B,R,Y,k,N=1;
    string s; // "Red" || "Yellow" || "Blue"
    cin>>B>>R>>Y>>k;
    for(int i=0; i<k; i++)
    {
        cin>>s;
        if(s == "Red") N *= R;
        if(s == "Yellow") N *= Y;
        if(s == "Blue") N *= B;
    }
    cout<<N<<endl;
    return 0;
}
