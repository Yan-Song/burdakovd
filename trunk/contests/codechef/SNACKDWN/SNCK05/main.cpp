#include <cassert>
#include <cstdio>
#include <iostream>

typedef long long i64;

const i64 MOD = 1000000007;

const int N = 2;

struct Vector
{
	i64 data[N];
};

struct Matrix
{
	i64 data[N][N];

	Matrix() {}

	Matrix(const i64 k)
	{
		data[0][0] = k;
		data[0][1] = 0;
		data[1][0] = 0;
		data[1][1] = k;
	}
};

Vector operator *(const Matrix& m, const Vector& v)
{
	Vector ans;

	for(int i = 0; i < 2; ++i)
	{
		ans.data[i] = 0;
		for(int j = 0; j < 2; ++j)
		{
			ans.data[i] += (m.data[i][j] * v.data[j]) % MOD;
			ans.data[i] %= MOD;
		}
	}
	return ans;
}

Matrix operator *(const Matrix& a, const Matrix& b)
{
	Matrix ans;

	for(int r = 0; r < 2; ++r)
		for(int c = 0; c < 2; ++c)
		{
			ans.data[r][c] = 0;
			for(int k = 0; k < 2; ++k)
			{
				ans.data[r][c] += (a.data[r][k] * b.data[k][c]) % MOD;
				ans.data[r][c] %= MOD;
			}
		}

	return ans;
}

Matrix operator +(const Matrix& a, const Matrix& b)
{
	Matrix ans;

	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 2; ++j)
			ans.data[i][j] = (a.data[i][j] + b.data[i][j]) % MOD;

	return ans;
}

template<class T>
T fastpow(const T& a, const int n)
{
	if(n == 0)
		return T(1);

	assert(n > 0);

	return (n % 2 == 0) ? 
		fastpow(a * a, n / 2)
		: a * fastpow(a, n - 1);
}

inline int solve(const int n)
{
	if(n == 0)
		return 0;

	if(n == 1)
		return 0; //1 : 1

	if(n == 2)
		return 1;//2: 1+1|2

	assert(n > 1);

	Matrix m;
	m.data[0][0] = 1;
	m.data[0][1] = 1;
	m.data[1][0] = 1;
	m.data[1][1] = 0;

	m = fastpow(m, n - 1);

	Vector v;
	v.data[0] = 1;
	v.data[1] = 1;

	v = m * v;

	return v.data[0];
}

using namespace std;

int main()
{
	int tc;
	cin>>tc;
	while(tc--)
	{
		int n;
		scanf("%d", &n);
		printf("%d\n", solve(n));
	}
}