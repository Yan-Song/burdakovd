// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// You may have heard of the game "Heroes of Might and Magic".  Recently, battles in this game have been broadcast online, and the weekly battles between Petr and Vasyl have been very popular.  Petr usually wins these battles, so Vasyl has decided to develop a new strategy.

The battlefield in this game consists of equal hexagonal cells arranged in the form of a larger hexagon.  The number of cells on each side of the battlefield represents the size of the field.  The coordinate system is shown in the following figure, which depicts a battlefield of size 3:



This week, Petr and Vasyl are playing on a battlefield of size N.  Some of the cells are already occupied by Petr's heroes.  The locations of these cells are given in the vector <int>s X and Y, where (X[i], Y[i]) is the location of Petr's i-th hero.  To defeat Petr, Vasyl must occupy every single free cell with his own heroes.  Unfortunately, Vasyl only has equestrian heroes, each of which occupy exactly two adjacent cells.  No two heroes can occupy a single cell.  One possible correct arrangement is shown in the following figure:



Vasyl wants to simulate a battle with every possible arrangement of his heroes so that he can determine the optimal one.  Calculate the number of different possible arrangements he will consider.  The answer might be very large, so return the number modulo 2000000011.

DEFINITION
Class:HexagonalBattlefield
Method:countArrangements
Parameters:vector <int>, vector <int>, int
Returns:int
Method signature:int countArrangements(vector <int> X, vector <int> Y, int N)


CONSTRAINTS
-N will be between 1 and 8, inclusive.
-X will contain between 1 and 50 elements, inclusive.
-X and Y will each contain the same number of elements.
-All points (X[i], Y[i]) will lie inside the battlefield of size N.
-All points (X[i], Y[i]) will be distinct.


EXAMPLES

0)
{-2,0,1,1,0}
{-2,0,1,0,2}
3

Returns: 10

This is the battlefield shown in the figure above.

1)
{0}
{0}
2

Returns: 2

2)
{0}
{0}
3

Returns: 104

3)
{-1,0,0,1,2}
{0,0,1,0,0}
3

Returns: 6

4)
{0,1,0,0,1,-1,-1}
{0,0,-1,1,1,0,-1}
2

Returns: 1

Here the entire battlefield is occupied by Petr's heroes. Therefore there exists only one possible arrangement.

*/
// END CUT HERE

#line 77 "HexagonalBattlefield.cpp"

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

class HexagonalBattlefield {
	public:
	int countArrangements(vector <int> X, vector <int> Y, int N) {
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {-2,0,1,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-2,0,1,0,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 10; verify_case(0, Arg3, countArrangements(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 2; verify_case(1, Arg3, countArrangements(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 104; verify_case(2, Arg3, countArrangements(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {-1,0,0,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,1,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 6; verify_case(3, Arg3, countArrangements(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {0,1,0,0,1,-1,-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,-1,1,1,0,-1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 1; verify_case(4, Arg3, countArrangements(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
    int main()
        {
        HexagonalBattlefield ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
