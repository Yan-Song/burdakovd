#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#define PMAX 25000

using namespace std;

int main()
{
    // нужно отсортировать по убыванию, можно выебнуться и
    // воспользоваться тем что 1 <= pi <= 25000 и не сортировать
    int n, x[PMAX+10], _;
    cin>>n;
    for(int i=1; i<=PMAX; i++)
        x[i] = 0;
    for(int i=0; i<n; i++)
    {
        cin>>_;
        x[_]++;
    }
    for(int i=PMAX; i>0; i--)
        for(int j=0; j<x[i]; j++)
            cout<<i<<endl;
    return 0;
}
