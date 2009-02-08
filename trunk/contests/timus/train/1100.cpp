#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#pragma comment(linker, "/STACK:16777216")

using namespace std;

class Team {
public:
    int ID;
    short int solved;

istream & operator >> (istream & in)
{
    in >> ID >> solved;
    return in;
}

ostream& operator << (ostream& out)
{
    out << ID << " " << solved;
    return out;
}
};


int main()
{
    /*
    "exactly the same final standings as old software" - похоже означает, что
    сортировка должна быть устойчивой, т.е. если кол-во решённых задач
    у нескольких задач совпадает, то выводить нужно в том же порядке
    как на входе

    для начала можно попробовать sort из stl
    (чтоб хоть узнать как с ним работать)
    */
    vector<Team> teams;
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        Team t;
        cin>>t;
    }
    return 0;
}
