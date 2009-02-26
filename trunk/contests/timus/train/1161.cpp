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
    /*
    на каждом шаге сталкиваем маскимальные массы, доказать не могу, чисто интуитивно
    */
    int n;
    cin>>n;
    priority_queue<double> pq;
    for(int i=0; i<n; i++)
    {
        double _;
        cin>>_;
        pq.push(_);
    }
    while(pq.size()>1)
    {
        double x,y;
        x = pq.top();
        pq.pop();
        y = pq.top();
        pq.pop();
        pq.push(2*sqrt(x*y));
    }
    printf("%.2lf\n", pq.top());
    return 0;
}
