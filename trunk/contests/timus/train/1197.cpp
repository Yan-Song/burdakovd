#include <iostream>
#include <string>

using namespace std;

int solve(int p, int d)
{
    p=min(p, 7-p);
    if(p==0) return 1;
    if(p==1) return (d==1)?2:1;
    else return 2;
}

int main()
{
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        string s;
        int x, y;
        cin>>s;
        x=s[0]-'a';
        y=s[1]-'1';
        // 0 <= x,y < 8
        cout<<solve(x,1)*solve(y,2)+solve(x,2)*solve(y,1)<<endl;
    }
    return 0;
}
