// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Rick firmly believes that there are magical patterns related to some numbers. This belief is the result of his own tendency to find odd patterns everywhere. He has recently thought that some numbers have a "magical source". For example, the number 1370974 has a magical source equal to 1234 because of the following process:


     1234
+   12340
+  123400
+ 1234000
---------
  1370974

Formally, 1234 is a magical source of 1370974 because there exists a number n such that the sum of a sequence of n numbers, where the i-th number (0-indexed) is 1234 multipled by 10^i, is equal to 1370974.  Note that by this definition, a positive number is a magical source of itself.

Given a positive int source, and an int A return the minimum number x such that x is greater than A and source is a magical source of x.

DEFINITION
Class:ReverseMagicalSource
Method:find
Parameters:int, int
Returns:int
Method signature:int find(int source, int A)


CONSTRAINTS
-source will be between 1 and 1000000, inclusive.
-A will be between 1 and 1000000, inclusive.


EXAMPLES

0)
19
200

Returns: 209

19 + 190 = 209

1)
19
18

Returns: 19

A positive number is a magical source of itself.

2)
333
36963

Returns: 369963



3)
1234
1000000

Returns: 1370974



*/
// END CUT HERE

#line 69 "ReverseMagicalSource.cpp"

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

class ReverseMagicalSource {
	public:
	int find(int source, int A) {
		return 0;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 19; int Arg1 = 200; int Arg2 = 209; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 19; int Arg1 = 18; int Arg2 = 19; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 333; int Arg1 = 36963; int Arg2 = 369963; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 1234; int Arg1 = 1000000; int Arg2 = 1370974; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
    int main()
        {
        ReverseMagicalSource ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
