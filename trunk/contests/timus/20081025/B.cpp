#include <iostream>
#include <math.h>

using namespace std;

double dist(int x, int y)
{
    return sqrt(double(x*x+y*y));
}

int main()
{
    int n, x, y;
    double r=0;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>x>>y;
        r=max(r, dist(x-1001,y-1001));
    }
    printf("1001 1001 %.9lf\n", r);
    return 0;
}
