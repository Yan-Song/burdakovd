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

class Team {
public:
    int ID;
    short int solved;
};

istream& operator>> (istream& in, Team& t)
{
    in >> t.ID >> t.solved;
    return in;
}

ostream& operator<< (ostream& out, Team& t)
{
    out << t.ID << " " << t.solved;
    return out;
}

bool cmp(const Team& a, const Team& b)
{
    return a.solved>b.solved;
}

int main()
{
    /*
    "exactly the same final standings as old software" - похоже означает, что
    сортировка должна быть устойчивой, т.е. если кол-во решённых задач
    у нескольких команд совпадает, то выводить нужно в том же порядке
    как на входе */
    
    /*
    для начала можно попробовать sort из stl
    (чтоб хоть узнать как с ним работать)
    AC (0.531sec, 2 037 КБ)
    */
    /*
    Team teams[160000];
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>teams[i];
    stable_sort(teams, teams+n, cmp);
    for(int i=0; i<n; i++)
        cout<<teams[i]<<endl;
    return 0;
    */

    /*
    и другой способ, с 100 очередями
    AC (0.593sec, 1 909 КБ)
    */
    queue<int> q[120];
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        int ID, solved;
        cin>>ID>>solved;
        q[solved].push(ID);
    }
    for(int i=100; i>=0; i--)
        while(not q[i].empty())
        {
            cout<<q[i].front()<<" "<<i<<endl;
            q[i].pop();
        }
    return 0;
}
