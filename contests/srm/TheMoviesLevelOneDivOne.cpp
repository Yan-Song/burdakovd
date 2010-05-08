// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// John and Brus are going to a theater to see a very interesting movie.  They would like to have seats next to each other in the same row.  The theater contains n rows, with m seats in each row.  Rows are numbered 1 to n from front to back, and seats are numbered 1 to m from left to right.  Some of the seats are already reserved, but John and Brus can book any of the available seats.

You are given vector <int>s row and seat.  The i-th elements of row and seat are the row number and seat number of the i-th reserved seat.  All remaining seats are available.  Return the number of ways for John and Brus to book two available seats next to each other in the same row.


DEFINITION
Class:TheMoviesLevelOneDivOne
Method:find
Parameters:int, int, vector <int>, vector <int>
Returns:long long
Method signature:long long find(int n, int m, vector <int> row, vector <int> seat)


NOTES
-Two bookings are considered different only if one contains a seat that the other does not contain.  In other words, they don't need to decide which seat John sits in and which seat Brus sits in.


CONSTRAINTS
-n and m will each be between 1 and 1,000,000,000, inclusive.
-row will contain between 1 and 47 elements, inclusive.
-row and seat will contain the same number of elements.
-Each element of row will be between 1 and n, inclusive.
-Each element of seat will be between 1 and m, inclusive.
-All pairs (row[i], seat[i]) will be distinct.


EXAMPLES

0)
2
3
{1, 2}
{2, 3}

Returns: 1

The first and the second seat in the second row are the only two free seats next to each other in the same row.

1)
2
3
{1, 1, 1, 2, 2, 2}
{1, 2, 3, 1, 2, 3}

Returns: 0

There are no free seats in the theater.

2)
4
7
{1}
{1}

Returns: 23

3)
10
8
{1, 9, 6, 10, 6, 7, 9, 3, 9, 2}
{7, 7, 3, 3, 7, 1, 5, 1, 6, 2}

Returns: 54

*/
// END CUT HERE
#line 71 "TheMoviesLevelOneDivOne.cpp"

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


class TheMoviesLevelOneDivOne {
	public:
	long long find(int n, int m, vector <int> row, vector <int> seat) {
		set<pii> bad;

		for(int i = 0; i < row.size(); ++i)
		{
			if(seat[i] > 1)
			{
				bad.insert(pii(row[i], seat[i] - 1));
			}
			if(seat[i] < m)
			{
				bad.insert(pii(row[i], seat[i]));
			}
		}

		const i64 ans = i64(n) * (m - 1) - bad.size();
		return ans;
	}

	public:
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 3; int Arr2[] = {1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2, 3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 1LL; verify_case(0, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 3; int Arr2[] = {1, 1, 1, 2, 2, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 2, 3, 1, 2, 3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 0LL; verify_case(1, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 7; int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 23LL; verify_case(2, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 8; int Arr2[] = {1, 9, 6, 10, 6, 7, 9, 3, 9, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {7, 7, 3, 3, 7, 1, 5, 1, 6, 2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 54LL; verify_case(3, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	TheMoviesLevelOneDivOne* q = new TheMoviesLevelOneDivOne();
	q->run_test(-1);
	delete q;

	return 0;
}
// END CUT HERE
