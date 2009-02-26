#include <iostream>
#include <string>
#include <cmath>
#include <stack>

using namespace std;

int main()
{
    stack<double> q;
    long long _;
    while(cin>>_)
        q.push(sqrt(double(_)));
    while(!q.empty())
    {
        printf("%.4f\n", q.top());
        q.pop();
    }
    //priority_queue<int> qf;
    //vector<int> tty;
    return 0;
}
