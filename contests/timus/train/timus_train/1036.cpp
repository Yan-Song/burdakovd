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
#include <cassert>
 
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
typedef vector<i64> vv64;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
 
const double pi=2*acos(0.0);
const int inf=1<<25;
 
struct Long
{
	static const int base = 10;

	vector<int> digits;

	Long() : digits(1)
	{
	}

	Long(const vi& digits_) : digits(digits_)
	{
	}

	Long& operator =(int v)
	{
		digits.clear();
		while(v || digits.empty())
		{
			digits.push_back(v % base);
			v /= base;
		}
		return *this;
	}

	Long(int v) : digits()
	{
		*this = v;
	}
};

typedef vector<Long> vL;
typedef vector<vL> vvL;

inline Long operator +(const Long& firstN, const Long& secondN)
{
	vi first = firstN.digits;
	vi second = secondN.digits;

	int len = max(first.size(), second.size());

	first.resize(len);
	second.resize(len);

	vi third(len);

	int _ = 0;
	for(int i = 0; i < len; ++i)
	{
		_ += first[i] + second[i];

		third[i] = _ % Long::base;
		_/= Long::base;
	}

	if(_ > 0)
		third.push_back(_);

	return Long(third);
}

inline void operator +=(Long& th, const Long& other)
{
	th = th + other;
}

inline Long operator *(const Long& x, const int n)
{
	assert(n < Long::base && n >= 0);
	
	int _ = 0;

	vi res(x.digits.size());

	for(int i = 0; i < x.digits.size(); ++i)
	{
		_ += x.digits[i] * n;
		res[i] = _ % Long::base;
		_ /= Long::base;
	}

	if(_ > 0)
		res.push_back(_);

	while(res.size() > 1 && res.back() == 0)
		res.pop_back();

	return Long(res);
}

inline Long operator *(const Long& firstN, const Long& secondN)
{
	vi ans(firstN.digits.size() + secondN.digits.size() + 1);

	for(int i = 0; i < secondN.digits.size(); ++i)
	{
		Long _ = firstN * secondN.digits[i];
		for(int j = 0; j < _.digits.size(); ++j)
			ans[i + j] += _.digits[j];
	}

	int _ = 0;
	for(int i = 0; i < ans.size(); ++i)
	{
		_ += ans[i];
		ans[i] = _ % Long::base;
		_ /= Long::base;
	}
	if(_ > 0)
		ans.push_back(_);

	assert(_ < Long::base && _ >= 0);

	while(ans.size() > 1 && ans.back() == 0)
		ans.pop_back();

	return Long(ans);
}

ostream& operator <<(ostream& os, const Long& n)
{
	vi digits(n.digits.rbegin(), n.digits.rend());

	for(int i = 0; i < digits.size(); ++i)
		cout << digits[i];

	return os;
}

int main()
{
	int N, S;
	cin >> N >> S;

	const int maxS = 9 * N;

	if(S % 2 || S > 2 * maxS)
	{
		cout << 0 << endl;
	}
	else
	{
		S /= 2;

		vvL dp(N + 1, vL(S + 1, 0));

		dp[0][0] = 1;

		for(int n = 1; n <= N; ++n)
			for(int s = 0; s <= S; ++s)
			{
				dp[n][s] = 0;
				for(int k = 0; k <= min(9, s); ++k)
					dp[n][s] += dp[n-1][s-k];
			}

		cout << dp[N][S] * dp[N][S] << endl;
	}
	return 0;
}
