#include <iostream>
#include <assert.h>

using namespace std;

int main()
{
    int n, p[3000];
    cin>>n;
    for(int i=0; i<n; i++)
        scanf("%d", &p[i]);
    for(int i=1; i<=n; i++)
    {
        int x=1, y=n;
        for(int j=0; p[j]!=i; j++)
            if(p[j]>i) x++;
        for(int j=n-1; p[j]!=i; j--)
            if(p[j]<i) y--;
        assert(x<=n);
        assert(y>0);
        printf("%d %d\n", x, y);
    }
    return 0;
}
