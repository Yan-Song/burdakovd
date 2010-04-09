// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// A string s is called an IOI string if it satisfies the following two conditions:

s contains only uppercase 'I' and uppercase 'O' letters.
There is at least one pair of non-negative integers (a,b) such that the a-th (0-indexed) character of s is 'I', the (a+b)-th character is 'O', and the (a+2*b)-th character is 'I'.

You are given a vector <string> mask. Concatenate the elements of mask to get one string. Each '?' character in mask can be replaced with either 'I' or 'O'.


Return the number of different IOI strings that can be formed, modulo 1,000,000,007 (1E9+7).


DEFINITION
Class:IOIString
Method:countIOIs
Parameters:vector <string>
Returns:int
Method signature:int countIOIs(vector <string> mask)


CONSTRAINTS
-mask will contain between 1 and 50 elements, inclusive.
-Each element of mask will contain between 1 and 50 characters, inclusive.
-Each character in mask will be uppercase 'I' or uppercase 'O' or '?'.


EXAMPLES

0)
{"IO?"}

Returns: 1

Two strings can be formed here : "IOI" and "IOO". Only "IOI" is an IOI string.

1)
{"????"}

Returns: 4

There are four IOI strings of length 4 : "IIOI", "IOII", "IOIO", and "OIOI".

2)
{"?II"}

Returns: 0

No IOI string can be formed from "?II".

3)
{"I??O??I"}

Returns: 16

Character 0 is 'I', character 3 is 'O', and character 6 is 'I'.
Therefore, all possible strings are IOI strings here.

4)
{"???I???????O???","???????????O??IO????????I???"}

Returns: 438952513

Don't forget to concatenate strings.

*/
// END CUT HERE

#line 71 "IOIString.cpp"

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

class IOIString {
	public:
	int countIOIs(vector <string> mask) {
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"IO?"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, countIOIs(Arg0)); }
	void test_case_1() { string Arr0[] = {"????"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, countIOIs(Arg0)); }
	void test_case_2() { string Arr0[] = {"?II"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, countIOIs(Arg0)); }
	void test_case_3() { string Arr0[] = {"I??O??I"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(3, Arg1, countIOIs(Arg0)); }
	void test_case_4() { string Arr0[] = {"???I???????O???","???????????O??IO????????I???"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 438952513; verify_case(4, Arg1, countIOIs(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
    int main()
        {
        IOIString ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
