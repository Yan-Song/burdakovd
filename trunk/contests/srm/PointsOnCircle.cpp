// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// You are given the radius r of a circle centered at the origin.  Your task is to return the number of lattice points (points whose coordinates are both integers) on the circle.  The number of pairs of integers (x, y) that satisfy x^2 + y^2 = n is given by the formula 4*(d1(n) - d3(n)), where di(n) denotes the number of divisors of n that leave a remainder of i when divided by 4.

DEFINITION
Class:PointsOnCircle
Method:count
Parameters:int
Returns:long long
Method signature:long long count(int r)


CONSTRAINTS
-r will be between 1 and 2*10^9, inclusive.


EXAMPLES

0)
1

Returns: 4

The only lattice points on the circle are (0, 1), (1, 0), (-1, 0), (0, -1).

1)
2000000000

Returns: 76



2)
3

Returns: 4

The number of lattice points on the circle of radius 3 is the same as the number of integer solutions of the equation x^2 + y^2 = 9. Using the formula from the problem statement we can calculate this number as 4*(d1(9) - d3(9)). It is easy to see that d1(9) = 2 (divisors 1 and 9) and d3(9) = 3 (divisor 3). So the answer is 4*(2 - 1) = 4.

3)
1053

Returns: 12



*/
// END CUT HERE
#line 51 "PointsOnCircle.cpp"

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


class PointsOnCircle {
	public:
	long long count(int r) {
		return 0;
	}

	public:
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; long long Arg1 = 4LL; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { int Arg0 = 2000000000; long long Arg1 = 76LL; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { int Arg0 = 3; long long Arg1 = 4LL; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { int Arg0 = 1053; long long Arg1 = 12LL; verify_case(3, Arg1, count(Arg0)); }

// END CUT HERE

};


int main()
{
	PointsOnCircle* q = new PointsOnCircle();
	q->run_test(-1);
	delete q;

	return 0;
}
