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

const double pi=2*acos(0.0);

vector<complex<double> > fft(const vector<complex<double> >& a, bool invert=false)
{
    int len=1, n=a.size();
    vector<complex<double> > A(n);
    while((1<<len)<n) len++;
    //debug(len);
    for(int i=0; i<n; i++)
    {
        int j=0;
        for(int k=0; k<len; k++)
            if(i & (1<<k))
                j |= (1<<(len-1-k));
        A[j] = a[i];
        //cout<<"A["<<j<<"] <= "<<"a["<<i<<"]"<<endl;
    }
    for(int s=2; s<=n; s<<=1)
    {
        double ang = 2 * pi / s * (invert ? -1 : 1);
        complex<double> ws(cos(ang), sin(ang));
        for(int j=0; j<n; j+=s)
        {
            complex<double> w=1;
            for(int k=0; k<s/2; k++)
            {
                complex<double> u = A[j+k];
                complex<double> t = A[j+s/2+k];
                A[j+k] = u + w*t;
                A[j+s/2+k] = u - w*t;
                if(invert)
                {
                    A[j+k] /= 2;
                    A[j+s/2+k] /= 2;
                }
                w *= ws;
            }
        }
    }
    return A;
}

int main()
{
    vector<complex<double> > a, b, c;
    a.push_back(1);
    a.push_back(2); a.push_back(0); a.push_back(0);
    b.push_back(3);
    b.push_back(4); b.push_back(0); b.push_back(0);
    vdebug(a); // размеры a и b должны быть степенями двойки хотя бы в два раза больше чем степень многочлена
    vdebug(b);
    a = fft(a); // преобразование Фурье
    b = fft(b);
    cout<<" After FFT:"<<endl;
    vdebug(a);
    vdebug(b);
    c.resize(a.size());
    foreach(i,a)
        c[i] = a[i] * b[i];
    cout<<" After c[i] <= a[i]*b[i]"<<endl;
    vdebug(c);
    c = fft(c, true); // обратное преобразование Фурье
    cout<<" After unFFT:"<<endl;
    vdebug(c);
    return 0;
}
