#include <iostream>

using namespace std;

class Point
{
    private:
        int x,y;
    public:
        Point() { x=0; y=0; }
        Point(int, int);
        void print();
};

Point::Point(int _x, int _y)
{
    x=_x;
    y=_y;
}

void Point::print()
{
    cout<<"Point("<<x<<","<<y<<")"<<endl;
}

int main()
{
    Point a;
    a.print();
    // cout<<a.x<<endl; - ошибка "error: ‘int Point::x’ is private"
    Point b(3,5);
    Point *p=new Point(8,9);
    b.print();
    p->print();
    return 0;
}
