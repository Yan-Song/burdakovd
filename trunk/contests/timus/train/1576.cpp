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

struct Tariff
{
    int prepaid, cost, bill;
    Tariff(int _prepaid, int _cost, int _abonplata):
            prepaid(_prepaid), cost(_cost), bill(_abonplata) {};
    int pay() { return bill; }
    void process(int, int);
};

void Tariff::process(int m, int s)
{
    int minutes;
    minutes = m;
    if(s>0) minutes++;
    if(m*60+s<=6) minutes = 0;
    int pp = min(minutes, prepaid);
    prepaid -= pp;
    minutes -= pp;
    bill += minutes*cost;
}

int main()
{
    /*
    Basic:     155
    Combined:  230
    Unlimited: 300
    */
    int n1, c1, n2, t, c2, n3, n, m, s;
    cin>>n1>>c1>>n2>>t>>c2>>n3>>n;
    Tariff basic(0, c1, n1), combined(t, c2, n2), unlim(1000000000, 0, n3);
    for(int i=0; i<n; i++)
    {
        char d;
        cin>>m>>d>>s;
        basic.process(m, s);
        combined.process(m, s);
        unlim.process(m, s);
    }
    cout<<"Basic:     "<<basic.pay()<<endl;
    cout<<"Combined:  "<<combined.pay()<<endl;
    cout<<"Unlimited: "<<unlim.pay()<<endl;
    return 0;
}
