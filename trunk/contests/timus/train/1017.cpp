#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#pragma comment(linker, "/STACK:16777216")

using namespace std;

int main()
{
    /* 
    после некоторых размышлений получаем:
    Q(n,k) - количество лестниц из N кубиков с K ступеньками,
    Ans = \sum(k=2..n, Q(n,k))
    Q(n,k) = Q(n-k,k) + Q(n-k,k-1)
    */
    long long n, Q[510][510];
    cin>>n;
    Q[0][0] = 1;
    for(int i=1; i<n; i++)
        Q[i][0] = 0;
    for(int k=1; k<=n; k++)
        for(int i=0; i<=n; i++)
            {
                if(i<k) Q[i][k] = 0; // количество кубиков меньше количества ступенек
                else Q[i][k] = Q[i-k][k] + Q[i-k][k-1];
                //printf("Из %d кубиков можно построить %d лестниц с %d ступеньками\n", i, int(Q[i][k]), k);
            }
    long long ans=0;
    for(int k=2; k<n; k++)
        ans += Q[n][k];
    cout<<ans<<endl;
    return 0;
}
