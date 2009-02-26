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
    int n, l=3;
    cin>>n;
    while(n%l>0) l++;
    l--;
    cout<<l<<endl;
    return 0;
}
