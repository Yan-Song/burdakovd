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
#include <iomanip>
#include <sstream>

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
#define sqr(t) ((t)*(t))

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

inline int gcd(const int x, const int y)
{
	return y ? gcd(y, x % y) : x;
}

template<typename P, typename Q>
inline istream& operator >>(istream& is, pair<P, Q>& p)
{
	return is >> p.first >> p.second;
}

template<typename P, typename Q>
inline ostream& operator <<(ostream& os, const pair<P, Q>& p)
{
	return os << p.first << ' ' << p.second;
}

template<typename T>
inline istream& operator >>(istream& is, vector<T>& v)
{
	for(typename vector<T>::size_type i = 0; i < v.size(); ++i)
		is >> v[i];

	return is;
}

template<typename T>
inline ostream& operator <<(ostream& os, const vector<T>& v)
{
	for(typename vector<T>::size_type i = 0; i < v.size(); ++i)
		os << (i ? " " : "") << v[i];

	return os;
}

typedef string strin;
typedef double doble;
#define cot cout

const int MOD = 1000000007;

template<int N>
class GenericMatrix {

public:
	int data[N][N];

	GenericMatrix() {
	}

	void nullify() {
		mset(data, 0);
	}

	void ones() {
		nullify();
		for(int i = 0; i < N; ++i) {
			data[i][i] = 1;
		}
	}

	void addWay(const int from, const int to) {
		++data[from][to];
	}
};

template<int N>
const GenericMatrix<N> operator *(const GenericMatrix<N>& a, const GenericMatrix<N>& b) {
	GenericMatrix<N> ans;
	ans.nullify();
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j) {
			for(int k = 0; k < N; ++k) {
				ans.data[i][j] = (ans.data[i][j] + static_cast<i64>(a.data[i][k]) * b.data[k][j]) % MOD;
			}
		}
	}
	return ans;
}

template<int N>
GenericMatrix<N>& operator *=(GenericMatrix<N>& source, const GenericMatrix<N>& multiplier) {
	source = source * multiplier;
	return source;
}

typedef GenericMatrix<64> Matrix;

template<typename T>
T fastPower(const T& t, const int n) {
	T ans;
	ans.ones();
	T multiplier = t;

	for(int power = n; power > 0; power >>= 1, multiplier *= multiplier) {
		if(power & 1) {
			ans *= multiplier;
		}
	}

	return ans;
}

int main()
{
	int d, k;
	cin >> d >> k;

	Matrix a;
	a.nullify();

	for(int offset1 = 0; offset1 <= d; ++offset1) {
		for(int offset2 = 0; offset2 <= d; ++offset2) {
			if(offset1 > 0) {
				a.addWay(offset1 * (d + 1) + offset2, (offset1 - 1) * (d + 1) + offset2);
			}
			if(offset2 > 0 && offset1 < d) {
				a.addWay(offset1 * (d + 1) + offset2, (offset1 + 1) * (d + 1) + offset2 - 1);
			}
			if(offset2 < d) {
				a.addWay(offset1 * (d + 1) + offset2, offset1 * (d + 1) + offset2 + 1);
			}
		}
	}


	const Matrix b = fastPower(a, k);

	cout << b.data[0][0] << endl;

	return 0;
}
