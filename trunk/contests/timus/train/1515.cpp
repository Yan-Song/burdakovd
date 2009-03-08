#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define forsz(i,start,container) fo(i,start,container.size())
#define foreach(i,container) forsz(i,0,container)
#define showv() foreach(i,v) cout<<(i?" ":"")<<v[i]; cout<<endl
#define ALL(container) container.begin(),container.end()

using namespace std;

typedef long long i64;


int main()
{
    /*
    пусть b[i] - исходные номиналы, упорядоченные по возрастанию
    dp[i] = b[1]+b[2]+...+b[i]

    рассмотрим неравенство b[i]<=dp[i-1]+1                           [1]

    пока оно выполняется верно следующее:

    "из купюр b[1]...b[i] можно составить любые суммы 0..dp[i]"

    док-во:
        для i=0 - верно (т.к. dp[0] = 0)

        дальше умея составлять суммы 0..dp[i-1] и добавляя b[i]
        можно получить и суммы 0+b[i]..dp[i-1]+b[i]
        объединяя эти отрезки получаем 0..dp[i] - переход индукции

    ///////////////////////////////////////////////////////////////

    если для некоторого i неравенство [1] не выполняется, т.е. b[i]>dp[i-1]+1
    то очевидно что мы не можем составить сумму dp[i-1]+1 ни какими купюрами

    находим минимальное такое i и выводим dp[i-1]+1

    если же такого i не найти, то выводим сумму dp[n]+1
    */
    i64 n,b,dp=0;
    cin>>n;
    fo(i,0,n)
    {
        cin>>b;
        if(b>dp+1) break;
        dp+=b;
    }
    cout<<dp+1<<endl;
    return 0;
}
