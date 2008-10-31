#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int e=0, m=0, l=0;
    for(int i=0; i<n; i++)
    {
        string s;
        cin>>s; // тип
        if(s[0]=='E') e++;
        else if(s[0]=='M') m++;
        else if(s[0]=='L') l++;
        cin>>s; // Penguin
    }
    int mx=max(e,max(m,l));
    if(mx==m) cout<<"Macaroni";
    else if(mx==e) cout<<"Emperor";
    else if(mx==l) cout<<"Little";
    cout<<" Penguin"<<endl;
    return 0;
}
