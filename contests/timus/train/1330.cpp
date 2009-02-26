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

struct Node // хранит информацию о отрезке [lbound, rbound]
{
    int lbound, rbound, sum;
    Node *left, *right;
    Node(int _lbound, int _rbound);
    ~Node();
    void add(int point, int value);
    int get(int l, int r);
};

Node::Node(int _lbound, int _rbound): lbound(_lbound), rbound(_rbound), sum(0)
{
   if(lbound==rbound)
       left = right = NULL;
   else
   {
       int middle = (lbound+rbound)/2;
       left = new Node(lbound, middle);
       right = new Node(middle+1, rbound);
   }
}

Node::~Node()
{
    if(lbound!=rbound)
        delete left, right;
}

void Node::add(int point, int value)
{
    if(point<lbound||point>rbound) return; // это не наш диапазон
    sum += value;
    if(lbound!=rbound)
    {
        left->add(point, value);
        right->add(point, value);
    }
}

int Node::get(int l, int r)
{
    //cout << "get(" << l << ", " << r << ") на [" << lbound << ", " << rbound << "]" << endl;
    if(l<=lbound && r>=rbound) return sum;
    if(l>rbound || r<lbound) return 0;
    return left->get(l,r) + right->get(l,r); // если мы дошли до сюда, значит lbound!=rbound и дети есть
}

int main()
{
    Node tree(1, 10000);
    int n, _;
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>_;
        tree.add(i, _);
    }
    cin>>n;
    for(int i=0; i<n; i++)
    {
        int l, r;
        cin>>l>>r;
        cout<<tree.get(l,r)<<endl;
    }
    return 0;
}
