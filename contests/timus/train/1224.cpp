#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

int main()
{
    // видно из картинки:
    // f(n,m) = 1 + f(m,n-1), n>1, m>0
    // f(1, k) = 0, k>0

    // f(n,n+k) = 2+f(n-1,n-1+k) =
    // = <повторяем предыдущее преобразование n-1 раз> = 2*(n-1),  k>=0
    // и f(n+k,n) = 1+f(n+k-1,n) = 2*(n-1)+1, k>0

    long long n,m,f;
    cin>>n>>m;

    if(n>m) f=2*(m-1)+1;
    else f=2*(n-1);

    cout<<f<<endl;
    
    return 0;
}
