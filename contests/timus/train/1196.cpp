#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

int main()
{
    int n,m,prepod[16000],student,s=0;
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>prepod[i];
    cin>>m;
    for(int i=0; i<m; i++)
    {
        cin>>student;
        int l=0, r=n-1;
        while(l<r)
        {
            int m=(l+r)/2;
            if(prepod[m]<student) l=m+1;
            else r=m;
        }
        if(prepod[l]==student) s++;
    }
    cout<<s<<endl;
    return 0;
}
