#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define foreach(i,x) for(int i=0; i<x.size(); i++)
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()

using namespace std;

typedef long long i64;
typedef vector<int> VI;

template<class T> T sqr(T x)
{
    return x*x;
}

template<class T> struct Line;

template<class T> class Point
{
public:
    T x,y;
    Point(T _x, T _y): x(_x), y(_y) {};
    Point(const Line<T>& l1, const Line<T>& l2)
    {
        x=(l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b);
        y=(l1.c*l2.a-l2.c*l1.a)/(l1.a*l2.b-l2.a*l1.b);
    }
    Point() {};
    T operator*(const Point<T>& b) const
    {
        return x*b.x+y*b.y;
    }
    Point<T> operator+(const Point<T>& b) const
    {
        return Point<T>(x+b.x, y+b.y);
    }
    Point<T> operator-(const Point<T>& b) const
    {
        return Point<T>(x-b.x, y-b.y);
    }
};

istream& operator>>(istream& in, Point<double>& t)
{
    in >> t.x >> t.y;
    return in;
}

ostream& operator<<(ostream& out, Point<double>& t)
{
    //out.precision(12);
    printf("%.10lf %.10lf", t.x, t.y);
    return out;
}

// template<class T>  Point<T> operator-(const Point<T>& a, const Point<T>& b)
// {
//     return Point<T>(a.x-b.x, a.y-b.y);
// }

//template<class T>

template<class T> T dist2(const Point<T>& a, const Point<T>& b)
{
    Point<T> d=a-b;
    return sqr(d.x)+sqr(d.y);
}

template<class T> struct Line
{
    T a,b,c;
    
    Line(T aa,T bb,T cc): a(aa), b(bb), c(cc) {};
    
    Line(const Point<T>& A, const Point<T> &B)
    {
        a = (B-A).y;
        b = (A-B).x;
        c = -(a*A.x+b*A.y);
    }

    Line(const Point<T>& A, const Line<T> &L)
    {
        a = L.b;
        b = -L.a;
        c = -(a*A.x+b*A.y);
    }
};

template<class T> ostream& operator<<(ostream& os, const Line<T>& t)
{
    os<<t.a<<"x + "<<t.b<<"y + "<<t.c;
    return os;
}

#define Point Point<double>
#define Line Line<double>
#define eps 0.00000001
///////////////////////

bool inotrezok(const Point& x, const Point& a, const Point& b)
{
    Point a1=a-x;
    Point b1=b-x;
    return a1*b1<0;
}

bool solve(Point a, Point b, Point c)
{
    Point b0=b;
    a = a-b0;
    b = b-b0;
    c = c-b0;

    //cout<<"a = "<<a<<endl;
    //cout<<"b = "<<b<<endl;
    //cout<<"c = "<<c<<endl;
    Line ac(a,c);
    //cout<<"ac: "<<ac<<endl;
    
    Line h(b,ac);
    //cout<<"h: "<<h<<endl;
    
    Point bh(h,ac);

    //cout<<"bh = "<<bh<<endl;
    Point c2=bh-(c-bh);
    //cout<<"c2 = "<<c2<<endl;
    if(dist2(c2,a)>eps && dist2(c2,c)>eps && !inotrezok(a,c,c2))
    {

        double avx=(a.x+b.x+c2.x)/3;
        double avy=(a.y+b.y+c2.y)/3;

        a.x-=avx;
        b.x-=avx;
        c2.x-=avx;

        a.y-=avy;
        b.y-=avy;
        c2.y-=avy;
        cout<<"NO"<<endl;
        cout<<a<<endl;
        
        cout<<b<<endl;
        
        cout<<c2<<endl;
        
        return false;
    }
    else return true;
}

int main()
{
    Point a,b,c;
    cin>>a>>b>>c;
    if(solve(a,b,c)) cout<<"YES"<<endl;
    
    return 0;
}
