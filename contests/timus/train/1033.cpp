#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#pragma comment(linker, "/STACK:16777216")

using namespace std;

struct Labyrinth
{
    int n, square;
    bool wall[35][35];
    bool seen[35][35];
    Labyrinth(int);
    void walk(int, int);
};

Labyrinth::Labyrinth(int _n): n(_n), square(0)
{
    for(int i=0; i<35; i++)
        for(int j=0; j<35; j++)
            {
                seen[i][j] = false;
                wall[i][j] = true;
            }
    wall[0][0] = wall[1][0] = wall[0][1] = wall[1][1] = false;
    wall[n][n] = wall[n+1][n] = wall[n][n+1] = wall[n+1][n+1] = false;
}

void Labyrinth::walk(int x, int y)
{
    if(x<1 || x>n || y<1 || y>n) return; // выходить низя
    if(wall[x][y]) return; // сквозь стену нельзя
    if(seen[x][y]) return; // тут уже были
    seen[x][y] = true;
    // смотрим, какие стены видно
    if(wall[x+1][y]) square++;
    if(wall[x-1][y]) square++;
    if(wall[x][y+1]) square++;
    if(wall[x][y-1]) square++;
    walk(x+1, y); // идём дальше
    walk(x-1, y);
    walk(x, y-1);
    walk(x, y+1);
}

istream& operator>>(istream& in, Labyrinth& l)
{
    string s;
    for(int i=1; i<=l.n; i++)
    {
        cin>>s;
        for(int j=0; j<l.n; j++)
            l.wall[i][j+1] = s[j]=='#';
    }
    return in;
}

int main()
{
    int n;
    cin>>n;
    Labyrinth l(n);
    cin>>l;
    l.walk(1,1);
    l.walk(n,n);
    cout<<(l.square*9)<<endl;
    return 0;
}
