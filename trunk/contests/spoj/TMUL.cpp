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
#define debug(x) cerr<<#x<<" = "<<x<<endl
#define adebug(x,n) fo(i,0,n) cerr<<#x<<"["<<i<<"] = "<<x[i]<<endl
#define vdebug(x) foreach(i,x) cerr<<#x<<"["<<i<<"] = "<<x[i]<<endl
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()

using namespace std;

typedef long long i64;
typedef unsigned long long u64;
typedef vector<int> vi;
typedef vector<i64> v64;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef complex<double> cd;
typedef vector<cd> vcd;

const double pi=2*acos(0.0);
const i64 ibase = 1000;

vcd fft(const vcd& a, bool invert=false)
{
    int n = a.size();
    vcd A(a.size());
    for(int i=0, j=0; i<a.size(); ++i)
    {
        A[j] = a[i];
        int bit = n>>1;
        for(; j>=bit && bit>1; bit>>=1)
            j -= bit;
        j += bit;
    }
    for(int s=2; s<=n; s<<=1)
    {
        double ang = 2 * pi / s * (invert ? -1 : 1);
        cd ws(cos(ang), sin(ang));
        for(int j=0; j<n; j+=s)
        {
            cd w=1;
            for(int k=0; k<s/2; k++)
            {
                cd u = A[j+k];
                cd t = A[j+s/2+k];
                A[j+k] = u + w * t;
                A[j+s/2+k] = u - w * t;
                w *= ws;
            }
        }
    }
    if(invert)
        foreach(i,A)
            A[i] /= n;
    return A;
}

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

    void writeln()
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

    LongNumber operator*(i64 z)
    {
        LongNumber ans(*this);
        ans *= z;
        return ans;
    }
    
    LongNumber operator*(const LongNumber& z)
    {
        //debug("enter operator*");
        // быстрое преобразование Фурье
        int n=1;
        //debug(n);
        vcd a(ALL(digits)), b(ALL(z.digits));
        while(a.size()+b.size()-1>n) n<<=1;
        //n<<=1;
        while(a.size()<n) a.push_back(0);
        while(b.size()<n) b.push_back(0);
        a = fft(a);
        b = fft(b);
        vcd c(n);
        foreach(i,a)
            c[i] = a[i] * b[i];
        c = fft(c, true);
        LongNumber ans("0");
        ans.digits.resize(n);
        foreach(i,c)
            ans.digits[i] = int(c[i].real() + 0.5);
        int _=0;
        foreach(i,ans.digits)
        {
            _ += ans.digits[i];
            ans.digits[i] = _ % ibase;
            _ /= ibase;
        }
        while(_>0)
        {
            ans.digits.push_back(_%ibase);
            _ /= ibase;
        }
        while(ans.digits[ans.digits.size()-1]==0)
            ans.digits.resize(ans.digits.size()-1);
        if(ans.digits.empty()) ans.digits.push_back(0);
        return ans;
    }
};

int main()
{
    int n;
    cin>>n;
    char l1[20000], l2[20000];
    fo(i,0,n)
    {
        scanf("%s %s", l1, l2);
        //debug("read");
        LongNumber ll1(l1);
        LongNumber ll2(l2);
        //debug("constructed LongNumbers");
        LongNumber m = ll1 * ll2;
        //debug("Multiplication done");
        m.writeln();
    }
    return 0;
}
