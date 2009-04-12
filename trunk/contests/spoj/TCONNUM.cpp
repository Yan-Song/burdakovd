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
#define fosz(i,s,x) for(int i=s; i<x.size(); i++)
#define foreach(i,x) fosz(i,0,x)
#define debug(x) cout<<#x<<" = "<<x<<endl
#define adebug(x,n) fo(i,0,n) cout<<#x<<"["<<i<<"] = "<<x[i]<<endl
#define vdebug(x) foreach(i,x) cout<<#x<<"["<<i<<"] = "<<x[i]<<endl
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()

using namespace std;

typedef long long i64;
typedef unsigned long long u64;
typedef vector<int> vi;
typedef vector<i64> v64;
typedef vector<string> vs;
typedef pair<int,int> pii;

const int ibase = 1<<25;

struct LongNumber
{
vi digits;

void null()
{
    digits.clear();
    digits.push_back(0);
}

void read(const string& s, int base)
{
    null();
    //cout<<"s="<<s<<endl;
    foreach(i,s)
    {
        int d = s[i]>='A' ? s[i]-'A'+10 : s[i]-'0';
        (*this) *= base;
        //vdebug(this->digits);
        //debug(d);
        (*this) += d;
        //vdebug(this->digits);
    }
    //cout<<"digits: ";
    //showv(digits);
}

void writeln(int base)
{
    vi ans;
    LongNumber z = *this;
    while(z!=0)
    {
        ans.push_back(z%base);
        z /= base;
    }
    reverse(ALL(ans));
    if(ans.empty()) ans.push_back(0);
    foreach(i,ans)
        printf("%c", char(ans[i]>9 ? 'A'+ans[i]-10 : '0'+ans[i]));
    printf("\n");
}

bool operator!=(int z)
{
    foreach(i,digits)
    {
        if(z%ibase!=digits[i]) return true;
        z /= ibase;
    }
    return z!=0;
}

int operator%(int z)
{
    int k=1, ans=0;
    foreach(i,digits)
    {
        ans += k*digits[i];
        ans %= z;
        k = k*ibase % z;
    }
    return ans;
}

const LongNumber& operator/=(int z)
{
    int _=0;
    for(int i=digits.size()-1; i>=0; i--)
    {
        _ += digits[i];
        digits[i] = _ / z;
        _ = _ % z * ibase;
    }
    return *this;
}

const LongNumber& operator+=(int y)
{
    int pos=0;
    while(y>0)
    {
        //cout<<":)"<<endl;
        while(pos>=digits.size()) digits.push_back(0);
        y += digits[pos];
        digits[pos] = y % ibase;
        y /= ibase;
        pos++;
    }
    return *this;
}

const LongNumber& operator*=(int y)
{
    int _ = 0;
    foreach(i,digits)
    {
        _ += y * digits[i];
        digits[i] = _ % ibase;
        _ /= ibase;
    }
    while(_>0)
    {
        digits.push_back(_%ibase);
        _ /= ibase;
    }
    return *this;
}

};

int main()
{
    int t;
    cin>>t;
    fo(i,0,t)
    {
        string s;
        char sc[10000];
        int base1, base2;
        LongNumber z;
        scanf("%s %d %d", sc, &base1, &base2);
        s=string(sc);
        //debug(base1); debug(base2); debug(s);
        z.read(s, base1);
        //cout<<"read"<<endl;
        z.writeln(base2);
        //cout<<"write"<<endl;
    }
    return 0;
}
