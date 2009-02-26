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
    /* руку пожмёт каждый каждому n*(n-1)/2, кроме супругов k */
    int n,k,r;
    cin>>n>>k;
    r = n*(n-1)/2 - k;
    cout<<r<<endl;
    return 0;
}
