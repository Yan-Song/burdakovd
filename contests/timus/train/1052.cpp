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

class Point
{
public:
    int x,y;
    Point(int _x, int _y): x(_x), y(_y) {};
    Point() {};
};

istream& operator>>(istream& in, Point& t)
{
    in >> t.x >> t.y;
    return in;
}

Point operator-(const Point& a, const Point& b)
{
    return Point(a.x-b.x, a.y-b.y);
}

bool line(const Point& a, const Point& b, const Point& c)
{
    Point p=b-a, q=c-a;
    return p.x*q.y==q.x*p.y;
}

int main()
{
    int n;
    Point r[240];
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>r[i];
    int ans=2;
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            {
                int c=2;
                for(int k=j+1; k<n; k++)
                    if(line(r[i], r[j], r[k]))
                        c++;
                if(ans<c) ans=c;
            }
    cout<<ans<<endl;
    return 0;
}
