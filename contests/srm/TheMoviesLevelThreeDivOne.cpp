// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// John and Brus have received a box of new movies to review.  There are N movies, numbered 0 to N-1, inclusive, and John and Brus each want to review every movie.  John has proposed that they use a special device called a review queue.  The device supports two operations: add a movie, and take a movie (if at least one exists in the queue).  When taking a movie, the movie in the queue that was added earliest is removed from the queue.  John and Brus each have their own review queue.



There are two phases to the review process.  In the first phase, John distributes the movies between the two queues.  He first takes movie 0 and adds it to either John's queue or Brus's queue, then he takes movie 1 and adds it to one of the queues, and so on, until each movie has been added to one of the queues.



In the second phase, John and Brus simultaneously start reviewing movies.  Each of them will continuously repeat the following sequence of moves.


Take a movie from his own review queue.  If this move is not successful because his queue is empty, he will quit completely (even if more movies will be added to his queue at a later time).

Review this movie.

Add this movie to the other person's review queue if he has not yet reviewed it.


Steps 1 and 3 take no time.  If a queue receives an add and a take operation at the same time, the add operation is completed first.  So, for example, if John's queue is empty and Brus attempts to add a movie to John's queue at the same time that John tries to take a movie from the same queue, the movie will get added and John will succeed in taking the movie from the queue.



The amount of time required for step 2 varies between John and Brus for each movie.  When reviewing a movie, neither John nor Brus feel that it is always necessary to view the entire movie.  It takes John timeJ[i] minutes to review movie i, and it takes Brus timeB[i] minutes.



In the first phase, since John has two choices for distributing each movie, there are 2^N ways to distribute the movies.  A distribution is considered good if John and Brus each review every movie during the second phase before quitting.  Return the total number of good ways to distribute the movies.

DEFINITION
Class:TheMoviesLevelThreeDivOne
Method:find
Parameters:vector <int>, vector <int>
Returns:long long
Method signature:long long find(vector <int> timeJ, vector <int> timeB)


CONSTRAINTS
-timeJ will contain between 1 and 47 elements, inclusive.
-timeJ and timeB will contain the same number of elements.
-Each element of timeJ will be between 1 and 20, inclusive.
-Each element of timeB will be between 1 and 20, inclusive.


EXAMPLES

0)
{4, 4}
{4, 4}

Returns: 2

We are interested in two distributions where John and Brus get one movie each.

1)
{1, 4}
{4, 2}

Returns: 1

Here the only possible distribution is where Brus gets the first movie and John gets the second one.

2)
{10, 10, 10, 10}
{1, 1, 1, 10}

Returns: 3

Brus must get all the movies except one of the first three during the distribution.

3)
{1, 2, 3, 4, 5, 6, 7}
{7, 6, 5, 4, 3, 2, 1}

Returns: 98

*/
// END CUT HERE
#line 82 "TheMoviesLevelThreeDivOne.cpp"

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


class TheMoviesLevelThreeDivOne {
	public:
	long long find(vector <int> timeJ, vector <int> timeB) {
		
	}

	public:
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {4, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {10, 10, 10, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 1, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 3LL; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1, 2, 3, 4, 5, 6, 7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7, 6, 5, 4, 3, 2, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 98LL; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	TheMoviesLevelThreeDivOne* q = new TheMoviesLevelThreeDivOne();
	q->run_test(-1);
	delete q;

	return 0;
}
// END CUT HERE
