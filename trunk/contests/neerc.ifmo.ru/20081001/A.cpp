#include <iostream>
#include <cmath>

using namespace std;

float slowsolve(int n, float u[110000][5])
{
    float max = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            {
                float s=0;
                for(int k=0; k<5; k++)
                {
                    s += abs(u[i][k]-u[j][k]);
                    //cout<<"k="<<k<<" abs(...)="<<fabs(u[i][k]-u[j][k])<<" s="<<s<<endl;
                    //cout<<" abs(-1)="<<fabs(-1.0)<<endl;
                }
                //cout<<"i="<<i<<" j="<<j<<" s="<<s<<endl;
                if(s>max) max=s;
            }
    return max;
}

float fastsolve(int n, float u[110000][5])
{
    return 0;
}

int main()
{
    int n;
    float u[100000][5];
    cin>>n;
    for(int i=0; i<n; i++)
        for(int j=0; j<5; j++)
            {
                scanf("%f", &u[i][j]);
                //cout<<u[i][j]<<endl;
            }
    printf("%0.2f\n", slowsolve(n, u));
    return 0;
}
