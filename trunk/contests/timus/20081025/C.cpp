#include <iostream>
//#include <assert.h>
#include <stdlib.h>

using namespace std;

int n,k,m;

bool people[200];
bool pp[200][200];

void assert(bool b)
{
    int x;
    if(!b)
    {
        x=1/0;
    }
}

void spair(int x, int y)
{
    if((x-y)%k==0) return; // один и тот же кабинет
    people[x]=true;
    people[y]=true;
    assert(!(pp[x][y]));
    assert(!(pp[y][x]));
    pp[x][y]=pp[y][x]=true;
    cout<<x<<" "<<y<<endl;
    m--; // день прошёл
    if(m==0)
    {
        for(int i=1; i<=n; i++) assert(people[i]);
        exit(0); // финиш
    }
}

int main()
{
    for(int i=0; i<200; i++)
    {
        people[i]=false;
        for(int j=0; j<200; j++) pp[i][j]=false;
    }
    cin>>n>>k>>m;
    for(int i=0; i<n; i++)
        cout<<(i%k+1)<<endl;
    // стремимся сначала показать всем, что такое дежурство
    for(int i=1; i<n; i+=2)
        spair(i, i+1);
    for(int i=(n-1)/2*2+1; i>1; i-=2)
        spair(i, i-1);
    // потом просто вызываем разные пары
    for(int i=3; i<n; i++)
        for(int j=1; j+i<=n; j++)
            spair(j, j+i);
    assert(false);
    return 0;
}
