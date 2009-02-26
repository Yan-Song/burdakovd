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

using namespace std;

struct f
{
    double p, q, r;
    f() {};
    f(double rr): r(rr) {};
    f(double pp, double qq, double rr): p(pp), q(qq), r(rr) {}
    f operator+(const f& second)
    {
        return f(p+second.p, q+second.q, r+second.r);
    }
    f operator-(const f& second)
    {
        return f(p-second.p, q-second.q, r-second.r);
    }
    f operator*(double d)
    {
        return f(p*d, q*d, r*d);
    }

};

int main()
{
    /* из исходной формулы получаем a[i+1]=2*a[i]-a[i-1]+2*c[i]
    затем выражаем a[i] через a[0] и a[1],
    и зная a[n+1] находим a[1]
    Пусть a[i] = p[i]*a[0] + q[i]*a[1] + r[i]...
    */
    int n;
    double a0, anp1, c[6000];
    cin>>n>>a0>>anp1;
    for(int i=0; i<n; i++)
        cin>>c[i];

    f prev(1, 0, 0), cur(0, 1, 0); // a[0], a[1]
    for(int i=1; i<n+1; i++)
    {
        f tmp = (cur*2)-prev+2*c[i-1];
        prev = cur;
        cur = tmp;
    }
    double a1 = (anp1-cur.p*a0-cur.r)/cur.q;
    printf("%.2lf\n", a1);
    return 0;
}
