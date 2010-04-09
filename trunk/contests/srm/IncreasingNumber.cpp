// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// A positive integer is called Increasing Number if its digits are in non-descending order from left to right in decimal notation. For example, 1234, 111, 58 and 8899 are Increasing Numbers, while 314, 7654 and 2009 are not.


You are given a long long digits and an int divisor. Calculate the number of Increasing Numbers that satisfy both of the following conditions and return this number modulo 1,000,000,007.

The number contains exactly digits digits in the decimal notation with no leading zeroes.
The number is divisible by divisor.


DEFINITION
Class:IncreasingNumber
Method:countNumbers
Parameters:long long, int
Returns:int
Method signature:int countNumbers(long long digits, int divisor)


CONSTRAINTS
-digits will be between 1 and 1,000,000,000,000,000,000 (10^18), inclusive.
-divisor will be between 1 and 500, inclusive.


EXAMPLES

0)
2
12

Returns: 4

12, 24, 36, and 48 satisfy the conditions.

1)
3
111

Returns: 9

All 3-digits numbers divisible by 111 are Increasing Numbers.

2)
452
10

Returns: 0

There is no Increasing Number divisible by 10.

3)
6
58

Returns: 38



*/
// END CUT HERE

#line 64 "IncreasingNumber.cpp"

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

class IncreasingNumber {
	public:
	int countNumbers(long long digits, int divisor) {
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 2LL; int Arg1 = 12; int Arg2 = 4; verify_case(0, Arg2, countNumbers(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 3LL; int Arg1 = 111; int Arg2 = 9; verify_case(1, Arg2, countNumbers(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 452LL; int Arg1 = 10; int Arg2 = 0; verify_case(2, Arg2, countNumbers(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 6LL; int Arg1 = 58; int Arg2 = 38; verify_case(3, Arg2, countNumbers(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
    int main()
        {
        IncreasingNumber ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
