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

    longNumber(const longNumber& q): digits(q.digits.size())
    {
        copy(ALL(q.digits), digits.begin());
    }
    
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

    longNumber operator*(int num) const
    {
        longNumber q=*this;
        q*=num;
        return q;
    }

    bool operator<(const longNumber& v) const
    {
        if(digits.size()<v.digits.size()) return true; // <
        for(int i=digits.size()-1; i>=0; i--)
            if(digits[i]<v.digits[i])
                return true; // <
            else
                if(digits[i]>v.digits[i])
                    return false; // >
        return false;
    }
};

ostream& operator<<(ostream& out, const longNumber& v)
{
    vector<int> d = v.digits;
    reverse(ALL(d));
    foreach(i, d)
        out<<d[i];
    return out;
}

template<class T, int base> struct indexer
{
    T data[base];
    
    T& operator[](int i)
    {
        return data[(i+base)%base];
    }
};

int main()
{
    /*
    утверждение: в любой группе  с N>1 найдётся
    хотя бы один двух- или трёх-головый орёл (доказывается индуктивно)

    благодаря этому можно динамически решить задачу
    */
    int n;
    cin>>n;
    indexer<longNumber,3> dp;
    dp[0]=1;
    dp[1]=1;
    dp[2]=2;
    fo(i,3,n+1)
    {
        dp[i]=max(dp[i-3]*3, dp[i-2]*2);
        //cout<<"["<<i<<"] "<<dp[i]<<endl;
    }
    cout<<dp[n]<<endl;
    return 0;
}
