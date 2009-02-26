#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define foreach(i,x) for(int i=0; i<x.size(); i++)
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()

using namespace std;

typedef long long i64;
typedef vector<int> VI;

struct longNumber
{
    vector<int> digits;
    longNumber() { digits.push_back(0); }
    longNumber(int v)
    {
        while(v>0)
        {
            digits.push_back(v%10);
            v/=10;
        }
        if(digits.empty())
            digits.push_back(0);
    }

    longNumber operator*=(int num) // num <= MAXINT/10
    {
        int _=0;
        foreach(i, digits)
        {
            _ += digits[i]*num;
            digits[i] = _%10;
            _ /= 10;
        }
        while(_>0)
        {
            digits.push_back(_%10);
            _ /= 10;
        }
        return *this;
    }
};

ostream& operator<<(ostream& out, const longNumber& v)
{
    vector<int> d = v.digits;
    while(d.size()>1&&d[d.size()-1]==0) d.pop_back(); // удаляем лидирующие нули
    reverse(ALL(d));
    foreach(i, d)
        out<<d[i];
    return out;
}

int main()
{
    int k;
    cin>>k;
    /*
    вроде как исходное условие "S(A + B) = S(A) + S(B)" будет верно если при
    сложении не было переносов в другой разряд.
    тогда для пары первых цифр вариантов 36 (учитываем что не допустимы
    лидирующие нули), для последующих 55
    ответ 36*55^(k-1);
    */
    longNumber ans(36);
    fo(i,0,k-1)
            ans *= 55;
    cout<<ans<<endl;
    return 0;
}
