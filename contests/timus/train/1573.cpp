#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int main()
{
    int B,R,Y,k,N=1;
    char s[10]; // "Red" || "Yellow" || "Blue"
    cin>>B>>R>>Y>>k;
    for(int i=0; i<k; i++)
    {
        cin>>s;
        if(strcmp(s, "Red")==0) N *= R; // !!! как нормально сравивать строки??
        if(strcmp(s, "Yellow")==0) N *= Y;
        if(strcmp(s, "Blue")==0) N *= B;
    }
    cout<<N<<endl;
    return 0;
}
