#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

int main()
{
    int n,k,happy=1,hours=0;
    cin>>n>>k;
    while((happy<=k)&&(happy<n)) 
    {
        // пока количество компьютеров с игрой меньше количества кабелей
        happy *= 2;
        hours += 1;
    }
    // теперь k<happy, значит дальше будем копировать только по k игр в час
    if(happy<n)
    {
        hours += (n-happy)/k;
        if((n-happy)%k) hours++;
    }
    cout<<hours<<endl;
    return 0;
}
