#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define foreach(i,x) for(int i=0; i<x.size(); i++)
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()

using namespace std;

typedef long long i64;
typedef vector<int> VI;

int gcd(int a, int b)
{
    return a==0?b:gcd(b%a, a);
}

int main()
{
    /* ответом будет gcd этих чисел
    для одного числа это верно,
    при выкидывании одного из равных чисел gcd не меняется,
    при вычитании меньшего из большего тоже не меняется
    */
    int n, ans=0;
    cin>>n;
    fo(i, 0, n)
    {
        int _;
        cin>>_;
        ans = gcd(ans, _);
    }
    cout<<ans<<endl;
    return 0;
}
