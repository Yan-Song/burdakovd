// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// There is an NxN square with its cells initially empty. The rows of the square are indexed from top to bottom, and columns from left to right. All indices start from 0.

You wish to fill the cells of the square with consecutive integers, starting from 1, using the following algorithm. At the beginning you stand at the topmost leftmost cell and put 1 in this cell. Each time you want to find the cell for the next number, you use the following method: Move a cells down and b cells right from your current cell (all moves are cyclic, so moving down one row from row N-1 takes you to row 0, and moving right one column from column N-1 takes you to column 0). If the current cell is empty, then you put the next number in this cell. Otherwise, move an additional c cells down and d cells right. If the current cell is empty, then you put the next number in this cell, otherwise the entire algorithm is finished.

Return a vector <string> describing the final state of the square after the algorithm is finished. The i-th element of the return should be a list of N integers, separated by single spaces and without leading or trailing spaces. The j-th integer in this list should be the integer written in the cell in row i, column j of the square, or -1 if this cell is empty.

DEFINITION
Class:SquareConstruction
Method:construct
Parameters:int, int, int, int, int
Returns:vector <string>
Method signature:vector <string> construct(int N, int a, int b, int c, int d)


CONSTRAINTS
-N will be between 1 and 10, inclusive.
-a, b, c and d will each be between 0 and N-1, inclusive.


EXAMPLES

0)
5
0
0
0
0

Returns: {"1 -1 -1 -1 -1", "-1 -1 -1 -1 -1", "-1 -1 -1 -1 -1", "-1 -1 -1 -1 -1", "-1 -1 -1 -1 -1" }

Here you don't move at all, so the algorithm finishes after putting 1 in the topmost leftmost cell.

1)
5
1
1
2
2

Returns: {"1 -1 -1 -1 -1", "-1 2 -1 -1 -1", "-1 -1 3 -1 -1", "-1 -1 -1 4 -1", "-1 -1 -1 -1 5" }

First you put numbers 1, 2, 3, 4 and 5 in the cells on the main diagonal. Then you analyze the cells at row 0, column 0 and at row 2, column 2. Neither cell is empty, so the algorithm is finished.

2)
5
1
1
1
0

Returns: {"1 22 18 14 10", "6 2 23 19 15", "11 7 3 24 20", "16 12 8 4 25", "21 17 13 9 5" }

In this case you will fill all the cells with numbers.

3)
5
0
1
2
3

Returns: {"1 2 3 4 5", "17 18 19 20 16", "8 9 10 6 7", "24 25 21 22 23", "15 11 12 13 14" }



4)
6
1
2
2
2

Returns: {"1 -1 15 -1 11 -1", "12 -1 2 -1 16 -1", "17 -1 7 -1 3 -1", "4 -1 18 -1 8 -1", "9 -1 5 -1 13 -1", "14 -1 10 -1 6 -1" }



5)
1
0
0
0
0

Returns: {"1" }



*/
// END CUT HERE
#line 94 "SquareConstruction.cpp"

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


class SquareConstruction {
	public:
	vector <string> construct(int N, int a, int b, int c, int d) {
		
	}

	public:
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; string Arr5[] = {"1 -1 -1 -1 -1", "-1 -1 -1 -1 -1", "-1 -1 -1 -1 -1", "-1 -1 -1 -1 -1", "-1 -1 -1 -1 -1" }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(0, Arg5, construct(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 1; int Arg2 = 1; int Arg3 = 2; int Arg4 = 2; string Arr5[] = {"1 -1 -1 -1 -1", "-1 2 -1 -1 -1", "-1 -1 3 -1 -1", "-1 -1 -1 4 -1", "-1 -1 -1 -1 5" }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(1, Arg5, construct(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; int Arg4 = 0; string Arr5[] = {"1 22 18 14 10", "6 2 23 19 15", "11 7 3 24 20", "16 12 8 4 25", "21 17 13 9 5" }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(2, Arg5, construct(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 5; int Arg1 = 0; int Arg2 = 1; int Arg3 = 2; int Arg4 = 3; string Arr5[] = {"1 2 3 4 5", "17 18 19 20 16", "8 9 10 6 7", "24 25 21 22 23", "15 11 12 13 14" }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(3, Arg5, construct(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 6; int Arg1 = 1; int Arg2 = 2; int Arg3 = 2; int Arg4 = 2; string Arr5[] = {"1 -1 15 -1 11 -1", "12 -1 2 -1 16 -1", "17 -1 7 -1 3 -1", "4 -1 18 -1 8 -1", "9 -1 5 -1 13 -1", "14 -1 10 -1 6 -1" }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(4, Arg5, construct(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_5() { int Arg0 = 1; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; string Arr5[] = {"1" }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(5, Arg5, construct(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	SquareConstruction* q = new SquareConstruction();
	q->run_test(-1);
	delete q;

	return 0;
}
// END CUT HERE
