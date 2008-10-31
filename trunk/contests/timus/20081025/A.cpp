#include <iostream>

using namespace std;

int cache[100][100];

int _solve(int, int);

int solve(int m, int n)
{
    if(cache[m][n]==-1) return cache[m][n]=_solve(m,n);
    else return cache[m][n];
}

int _solve(int m, int n)
{
    for(int k=1; k<m; k++)
        if(solve(k, n)==solve(m-k, n)) return 1;
    for(int k=1; k<n; k++)
        if(solve(m, k)==solve(m, n-k)) return 1;
    return 0;
}

int main()
{
    for(int i=0; i<100; i++)
        for(int j=0; j<100; j++)
            cache[i][j] = -1;
    int m,n;
    cin>>m>>n;
    cout<<(solve(m,n)?"[:=[first]":"[second]=:]")<<endl;
    return 0;
}
