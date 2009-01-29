#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

int main()
{
    int n, m, q[1000];
    cin>>n>>m;
    for(int i=0; i<n; i++)
        cin>>q[i];
    for(int i=0; i<10; i++)
        cout<<q[(i+m)%n];
    cout<<endl;
    return 0;
}
