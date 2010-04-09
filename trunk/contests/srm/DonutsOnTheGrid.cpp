// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Petya likes donuts. He tries to find them everywhere. For example if he is given a grid where each cell contains a '0' or '.' he will construct donuts from the cells.

To make the donuts:

Petya first selects a rectangle of cells of width, w, and height, h, where both are at least 3.
Then he removes a rectangular hole of width w-2 and height h-2 centered in the larger rectangle.
For the remaining cells (a closed rectangular ring) to be a valid donut, all of the cells must contain '0' (because donuts are shaped like zeros). Cells in the hole can contain anything since they are not part of the donut.


Here is an example with three overlapping donuts.

..........
.00000000.
.0......0.
.0.000000.
.0.0...00.
.0.0...00.
.0.000000.
.0......0.
.00000000.
..........

The grid in this problem will be pseudo-randomly generated using the following method:
You are given four ints: H (the grid height), W (the grid width), seed and threshold. Let x0=seed and for all i>=0 let xi+1 = (xi * 25173 + 13849) modulo 65536. Process the cells of the matrix in row major order (i.e., first row left to right, second row left to right, etc.). Each time you process a cell, calculate the next xi (starting with x1 for the upper left corner). If it is greater than or equal to threshold, the current cell will contain a '.', otherwise it will contain a '0'.
Return the number of distinct donuts in the figure. Two donuts are considered distinct if they either have different width or height, or if the top left hand corner is in a different location (i.e., overlapping donuts are counted).

DEFINITION
Class:DonutsOnTheGrid
Method:calc
Parameters:int, int, int, int
Returns:long long
Method signature:long long calc(int H, int W, int seed, int threshold)


NOTES
-The random generation of the input is only for keeping the input size small. The author's solution does not depend on any properties of the generator, and would work fast enough for any input of allowed dimensions.


CONSTRAINTS
-H will be between 1 and 350, inclusive.
-W will be between 1 and 350, inclusive.
-seed will be between 0 and 65535, inclusive.
-threshold will be between 0 and 65536, inclusive.


EXAMPLES

0)
5
5
222
55555

Returns: 4

Here is an example of the grid:
00000
00.0.
.0000
00.00
00000

1)
5
6
121
58000

Returns: 3

Here is the grid and three donuts in it:

00000.   XXX...   XXX...   ..XXX.
0.0000   X.X...   X.X...   ..X.X.
0.000.   X.X...   X.X...   ..XXX.
000.00   XXX...   X.X...   ......
000.00   ......   XXX...   ......



2)
4
5
6
50000

Returns: 1

The grid is:

0.0.0
00000
.00.0
0.000


3)
4
4
1
65536

Returns: 9

Here, the grid is completely filled by 0's. There are 9 possible placements of a donut:

XXX.  XXX.  .XXX  .XXX  ....  ....  XXXX  ....  XXXX
X.X.  X.X.  .X.X  .X.X  XXX.  .XXX  X..X  XXXX  X..X
XXX.  X.X.  .XXX  .X.X  X.X.  .X.X  XXXX  X..X  X..X
....  XXX.  ....  .XXX  XXX.  .XXX  ....  XXXX  XXXX


*/
// END CUT HERE

#line 120 "DonutsOnTheGrid.cpp"

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

class DonutsOnTheGrid {
	public:
	long long calc(int H, int W, int seed, int threshold) {
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 5; int Arg2 = 222; int Arg3 = 55555; long long Arg4 = 4LL; verify_case(0, Arg4, calc(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 6; int Arg2 = 121; int Arg3 = 58000; long long Arg4 = 3LL; verify_case(1, Arg4, calc(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 5; int Arg2 = 6; int Arg3 = 50000; long long Arg4 = 1LL; verify_case(2, Arg4, calc(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 4; int Arg2 = 1; int Arg3 = 65536; long long Arg4 = 9LL; verify_case(3, Arg4, calc(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
    int main()
        {
        DonutsOnTheGrid ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
