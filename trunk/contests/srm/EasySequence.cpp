// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Petya likes sequences. He has an infinite sequence A[] with the following properties: 

A[0], A[1], ..., A[N-1] are given; 
A[i]=(A[i-1]+A[i-2]+...+A[i-N])%10 for all i>=N;
Sequence B[] with length M is a substring of A[] if there is such index P that B[0]=A[P], B[1]=A[P+1], ..., B[M-1]=A[P+M-1]. Your task is to find the smallest possible such P. If there is no such index, return -1.

DEFINITION
Class:EasySequence
Method:find
Parameters:vector <int>, vector <int>
Returns:int
Method signature:int find(vector <int> A, vector <int> B)


CONSTRAINTS
-A will contain between 1 and 7 elements, inclusive. 
-B will contain between 1 and 50 elements, inclusive.
-Each element of A will be between 0 and 9, inclusive.
-Each element of B will be between 0 and 9, inclusive.


EXAMPLES

0)
{1,2,3}
{0,7,8,5}

Returns: 5

Starting with 1,2,3 we have:
1+2+3 =  6,  6 % 10 = 6
2+3+6 = 11, 11 % 10 = 1
3+6+1 = 10, 10 % 10 = 0
6+1+0 =  7,  7 % 10 = 7
1+0+7 =  8,  8 % 10 = 8
0+7+8 = 15, 15 % 10 = 5
7+8+5 = 20, 20 % 10 = 0

1,2,3,6,1,0,7,8,5,0
          0,7,8,5      answer = 5

1)
{1,2,8}
{7,4,2,3}

Returns: -1



2)
{1,2,3,4,5}
{4,5}

Returns: 3



3)
{1}
{1,1,1}

Returns: 0



*/
// END CUT HERE

#line 73 "EasySequence.cpp"

#include <string>
#include <vector>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <deque>
#include <set>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> v64;
typedef unsigned long long u64;

class EasySequence {
	private:
		vector<int> data;
		int N;
		int sum;
		int p;

		inline int& operator [](const int index)
		{
			return data[index % N];
		}

		inline bool compare(const vector<int>& B)
		{
			int lim = std::min<int>(N, B.size());

			for(int i = 0; i < lim; ++i)
				if((*this)[p + i] != B[i])
					return false;

			return true;
		}

		void shift()
		{
			int last = sum % 10;
			sum = (sum - (*this)[p] + last + 10) % 10;
			(*this)[p + N] = last;

			++p;
		}
	public:
	int find(vector <int> A, vector <int> B) {
		N = A.size();
		data = A;
		sum = 0;

		for(int i = 0; i < N; ++i)
			sum += data[i];

		p = 0;

		int limit = 1;
		for(int i = 0; i < N; ++i)
			limit *= 10;

		do
		{
			if(compare(B))
				return p;

			shift();
		}
		while(p <= limit);

		cout << p << endl;

		return -1;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,7,8,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,2,8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7,4,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,2,3,4,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
    int main()
        {
        EasySequence ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
