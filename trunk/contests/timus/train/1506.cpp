#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#pragma comment(linker, "/STACK:16777216")

using namespace std;

int main()
{
    int n,k,data[120],c;
    cin>>n>>k;
    for(int i=0; i<n; i++)
        cin>>data[i];
    c = n/k; // количество строк
    if(n%k>0) c++;
    for(int l=0; l<c; l++)
    {
        for(int i=l; i<n; i+=c)
            printf("%4d", data[i]);
        cout<<endl;
    }
    return 0;
}
