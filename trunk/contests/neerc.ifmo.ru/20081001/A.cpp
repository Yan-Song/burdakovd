#include <iostream>
#include <cmath>

using namespace std;

float u[100000][5];

float dist(int i, int j)
{
    float s=0;
    for(int k=0; k<5; k++)
        s += abs(u[i][k]-u[j][k]);
    return s;
}

float slowsolve(int n)
{
    float max = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            {
                float s=dist(i,j);
                if(s>max) max=s;
            }
    return max;
}

float fastsolve(int n)
{
    return 0;
}

int main()
{
    int n;

    cin>>n;
    for(int i=0; i<n; i++)
        for(int j=0; j<5; j++)
            {
                scanf("%f", &u[i][j]);
                //cout<<u[i][j]<<endl;
            }
    printf("%0.2f\n", slowsolve(n));
    return 0;
}
