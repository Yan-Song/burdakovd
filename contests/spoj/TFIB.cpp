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
#include <complex>

#pragma comment(linker, "/STACK:16777216")

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define fosz(i,s,x) for(int i=s; i<x.size(); i++)
#define foreach(i,x) fosz(i,0,x)
#define debug(x) cerr<<(#x)<<" = "<<(x)<<endl
#define adebug(x,n) fo(i,0,n) cerr<<(#x)<<"["<<i<<"] = "<<x[i]<<endl
#define vdebug(x) foreach(i,x) cerr<<(#x)<<"["<<i<<"] = "<<x[i]<<endl
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()

using namespace std;

typedef long long i64;
typedef unsigned long long u64;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<i64> v64;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef complex<double> cd;
typedef vector<cd> vcd;

const double pi=2*acos(0.0);
const int inf=1e9;
const int ibase=1000;

struct LongNumber
{
    v64 digits;

    void null()
    {
        digits.clear();
        digits.push_back(0);
    }

    void read(const string& s)
    {
        vi t;
        t.resize(s.size());
        foreach(i,s)
            t[i] = s[i]>='A' ? s[i]-'A'+10 : s[i]-'0';
        reverse(ALL(t));
        while(t.size()%3) t.push_back(0);
        digits.resize(t.size()/3);
        foreach(i,digits)
            digits[i] = t[3*i] + 10 * (t[3*i+1] + 10 * t[3*i+2]);
        while(!digits[digits.size()-1])
            digits.resize(digits.size()-1);
    }

    LongNumber(const string& s)
    {
        read(s);
    }

    void writeln() const
    {
        int base=10;
        vi ans(digits.size()*3);
        foreach(i,digits)
        {
            ans[3*i] = digits[i]%10;
            ans[3*i+1] = digits[i]/10%10;
            ans[3*i+2] = digits[i]/100;
        }
        while(!ans[ans.size()-1])
            ans.resize(ans.size()-1);
        if(ans.empty()) ans.push_back(0);
        reverse(ALL(ans));
        foreach(i,ans)
            printf("%c", char(ans[i]>9 ? 'A'+ans[i]-10 : '0'+ans[i]));
        printf("\n");
    }

    bool operator==(i64 z) const
    {
        return !(*this!=z);
    }
    
    bool operator!=(i64 z) const
    {
        foreach(i,digits)
        {
            if(z%ibase!=digits[i]) return true;
            z /= ibase;
        }
        return z!=0;
    }

    int operator%(int z) const
    {
        i64 k=1, ans=0;
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
        i64 _=0;
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

    LongNumber operator+(const LongNumber& z) const
    {
        LongNumber tmp(*this);
        tmp += z;
        return tmp;
    }
    
    const LongNumber& operator+=(const LongNumber& z)
    {
        i64 _=0;
        fo(i,0,max(z.digits.size(), digits.size()))
        {
            while(i>=digits.size()) digits.push_back(0);
            _ += digits[i];
            _ += i<z.digits.size() ? z.digits[i] : 0;
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

    const LongNumber& operator*=(i64 y)
    {
        i64 _ = 0;
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

    LongNumber operator*(i64 z) const
    {
        LongNumber ans(*this);
        ans *= z;
        return ans;
    }

    bool operator<(const LongNumber& z) const
    {
        if(digits.size()<z.digits.size()) return true;
        if(digits.size()>z.digits.size()) return false;
        for(int i=digits.size()-1; i>=0; i--)
            if(digits[i]<z.digits[i]) return true;
            else if (digits[i]>z.digits[i]) return false;
        return false;
    }

    bool operator==(const LongNumber& z) const
    {
        if(digits.size()!=z.digits.size()) return false;
        foreach(i,digits)
            if(digits[i]!=z.digits[i])
                return false;
        return true;
    }

    bool operator<=(const LongNumber& z) const
    {
        return *this<z || *this==z;
    }
};


int main()
{
    /*
    LongNumber e("1");
    fo(i,0,100) e *= 10;
    //e.writeln();
    LongNumber a("1"), b("1");
    for(int i=3; b<e; i++)
    {
        LongNumber c = a + b;
        a = b;
        b = c;
        cout<<" fibo["<<i<<"] = ";
        b.writeln();
    }*/
    while(true)
    {
        char c1[1000], c2[1000];
        scanf("%s %s\n", c1, c2);
        LongNumber a(c1), b(c2);
        if(a==0 && b==0) break;
        if(b<a)
        {
            LongNumber t=a;
            a=b;
            b=t;
        }
        LongNumber x("0"), y("1");
        int ans = 0;

        while(y<=b)
        {
            if(a<=y) ++ans;
            LongNumber z = x + y;
            x = y;
            y = z;
        }

        printf("%d\n", ans);
    }
    return 0;
}
