// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// The game "Barons and Coins" utilizes a customized chess board that can be much larger than the usual 8x8. The game involves the use of a special chess piece, the baron. Initially, a baron is placed on the top-left cell of the board (specified as  x=0, y=0) and coins are placed by the other players on specific cells of the board. The objective of the game is to use the baron to capture as many coins as possible. A coin is considered captured when the player moves the baron to the cell where the coin has been placed.

A baron's movement is as follows: In the first turn, the baron moves from its cell (x,y) to cell (x + K1, y + 1) such that K1 is positive.  After the first turn, the i-th move is specified as moving from current cell (x,y) to a new cell (x+Ki , y+1) such that Ki is strictly greater than Ki-1 . 

The coordinates of every coin are given in the vector <int> x and the vector <int> y, where the i-th coin is located on cell (x[i], y[i]). Return the maximum number of coins a player can capture.

DEFINITION
Class:BaronsAndCoins
Method:getMaximum
Parameters:vector <int>, vector <int>
Returns:int
Method signature:int getMaximum(vector <int> x, vector <int> y)


CONSTRAINTS
-x will contain between 1 and 50 elements, inclusive.
-y will contain the same number of elements as x.
-Each element of x will be between 1 and 10000, inclusive.
-Each element of y will be between 1 and 10000, inclusive.
-Each pair x[i], y[i] will be distinct.


EXAMPLES

0)
{15, 5, 30}
{4, 5, 6}

Returns: 2

The baron can move in this order to obtain the coins at (15,4) and (30,6):
(0,0) -> (2,1) -> (5,2) -> (9,3) -> (15,4) -> (22,5) -> (30,6)

1)
{10}
{10}

Returns: 0

No valid sequence of baron movements can take the baron from (0,0) to (10,10).

2)
{1, 3, 6, 10, 15, 21}
{1, 2, 3, 4, 5, 6}

Returns: 6



3)
{5, 10, 15, 20, 25, 30, 35, 40, 45}
{1, 1, 1, 2, 2, 2, 3, 3, 3}

Returns: 3



4)
{1, 3, 6, 10, 22, 35, 50, 66}
{1, 2, 3, 1, 2, 3, 4, 5}

Returns: 5



*/
// END CUT HERE

#line 73 "BaronsAndCoins.cpp"

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

class BaronsAndCoins {
	public:
	int getMaximum(vector <int> x, vector <int> y) {
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {15, 5, 30}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 5, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(0, Arg2, getMaximum(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, getMaximum(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1, 3, 6, 10, 15, 21}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3, 4, 5, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(2, Arg2, getMaximum(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {5, 10, 15, 20, 25, 30, 35, 40, 45}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 1, 2, 2, 2, 3, 3, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(3, Arg2, getMaximum(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1, 3, 6, 10, 22, 35, 50, 66}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3, 1, 2, 3, 4, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(4, Arg2, getMaximum(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
    int main()
        {
        BaronsAndCoins ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
