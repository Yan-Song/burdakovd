#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#define LEN 180

using namespace std;

typedef unsigned short int digit;

void short2Long(digit *a, int x) // a = x
{
    for(int i=0; i<LEN; i++)
    {
        a[i] = x%10;
        x /= 10;
    }
}

void longSum(digit *a, digit *b, digit *c) // c = a + b
{
    int _ = 0; // перенос
    for(int i=0; i<LEN; i++)
    {
        _ = a[i] + b[i] + _;
        c[i] = _ % 10;
        _ /= 10;
    }
}

void mulLongShort(digit *a, int p) // a *= p, p<=10
{
    int _ = 0;
    for(int i=0; i<LEN; i++)
    {
        _ += a[i] * p;
        a[i] = _%10;
        _ /= 10;
    }
}

void printLong(digit* a)
{
    int m=LEN-1;
    while((m>0)&&(a[m]==0))
        m--;
    for(int i=m; i>=0; i--)
        cout<<a[i];
}

int main()
{
    int n,k;
    cin>>n>>k;
    digit *a, *b, *t;
    a = (digit*)malloc(LEN*sizeof(digit));
    b = (digit*)malloc(LEN*sizeof(digit));
    short2Long(a, 1); // a = 1
    short2Long(b, k); // b = k
    for(int i=2; i<n; i++)
    {
        longSum(a, b, a); // a = a + b
        mulLongShort(a, k-1); // a = (k-1)*a;
        //cout<<"f["<<i<<"] = "<<b<<endl;
        t = a;
        a = b; // a = b;
        b = t; // b = t;
    }
    mulLongShort(b, k-1); // b *= (k-1)
    printLong(b);
    cout<<endl;
    free(a);
    free(b);
    return 0;
}
