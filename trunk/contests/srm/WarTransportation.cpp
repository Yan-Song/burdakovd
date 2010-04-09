// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
A country is at war, and one of its messenger soldiers must transport something of great importance from city 1 to city 2 using the highway system, which consists entirely of one-way highways.  As soon as the soldier sets out on his mission, he is informed by an agent that the enemy has destroyed exactly one of the highways in the country.  Unfortunately, it is unknown which highway was destroyed.  He won't know which highway was destroyed until he arrives at the starting city of the destroyed highway.  The soldier wants to use a strategy that will make the worst-case distance he has to travel as short as possible.


You are given an int n, the number of cities in the country.  The cities are numbered 1 to n.  The highways between cities are given in the vector <string> highways.   Concatenate the elements of highways to get a comma separated list of integer triplets. Each triplet is formatted "a b c" (quotes for clarity), which means that there's a one-way highway of length c from city a to city b.  Return the distance the messenger soldier will have to travel in the worst case.  If there is a chance that he will never reach his destination, return -1 instead.


DEFINITION
Class:WarTransportation
Method:messenger
Parameters:int, vector <string>
Returns:int
Method signature:int messenger(int n, vector <string> highways)


NOTES
-Note that there may be multiple parallel highways from one city to another.


CONSTRAINTS
-n will be between 2 and 100, inclusive.
-highways will contain between 1 and 50 elements, inclusive.
-Each element of highways will contain between 1 and 50 characters, inclusive.
-When concatenated, highways will contain a comma separated list of triplets of integers.
-Each integer triplet will be formatted "a b c" (quotes for clarity), where a and b are distinct integers between 1 and n, inclusive, and c is an integer between 1 and 1000, inclusive.
-Each integer in integer triplets will have no leading zeros and will contain only digits ('0'-'9').


EXAMPLES

0)
3
{"1 2 1,1 3 2,3 2 3"}

Returns: 5

The best strategy is to take the path 1->2 if the first highway is not destroyed.  Otherwise, take the path 1->3->2.

1)
8
{"1 3 1,1 4 1,3 5 1,4 5 1,5 6 1,6 7 1,6 8 1,7 2 1,",
 "8 2 1"}

Returns: -1

If the highway from city 5 to city 6 is destroyed, the messenger can't finish the transportation. 

2)
4
{"1 3 1,1 3 2,3 2 1,1 4 1,4 2 1"}

Returns: -1

No matter what strategy the messenger adopts, there is a chance that the transportation can't be finished.

3)
4
{"1 3 1,3 2 1,1 4 1,4 2 1,3 4 1"}

Returns: 3

The best strategy is to move to city 3 at first.

4)
20
{"1 13 3,13 4 7,4 3 4,3 10 8,10 18 9,18 12 6,12 2 3,",
 "1 17 6,17 13 6,13 9 4,9 10 8,10 7 2,7 5 5,5 19 9,1",
 "9 14 6,14 16 9,16 18 7,18 15 5,15 20 3,20 12 9,12 ",
 "8 4,8 11 3,11 4 1,4 3 7,3 2 3,20 10 2,1 18 2,16 19",
 " 9,4 15 9,13 15 6"}

Returns: 23



*/
// END CUT HERE

#line 83 "WarTransportation.cpp"

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

class WarTransportation {
	public:
	int messenger(int n, vector <string> highways) {
		return 0;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; string Arr1[] = {"1 2 1,1 3 2,3 2 3"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(0, Arg2, messenger(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 8; string Arr1[] = {"1 3 1,1 4 1,3 5 1,4 5 1,5 6 1,6 7 1,6 8 1,7 2 1,",
 "8 2 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(1, Arg2, messenger(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 4; string Arr1[] = {"1 3 1,1 3 2,3 2 1,1 4 1,4 2 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(2, Arg2, messenger(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 4; string Arr1[] = {"1 3 1,3 2 1,1 4 1,4 2 1,3 4 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(3, Arg2, messenger(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 20; string Arr1[] = {"1 13 3,13 4 7,4 3 4,3 10 8,10 18 9,18 12 6,12 2 3,",
 "1 17 6,17 13 6,13 9 4,9 10 8,10 7 2,7 5 5,5 19 9,1",
 "9 14 6,14 16 9,16 18 7,18 15 5,15 20 3,20 12 9,12 ",
 "8 4,8 11 3,11 4 1,4 3 7,3 2 3,20 10 2,1 18 2,16 19",
 " 9,4 15 9,13 15 6"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 23; verify_case(4, Arg2, messenger(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
    int main()
        {
        WarTransportation ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
