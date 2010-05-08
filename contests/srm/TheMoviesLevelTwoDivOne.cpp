// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// John has decided to watch some horror movies tonight.  He has a collection of N scary movies, numbered 0 to N-1, inclusive.  The lengths of the movies are given in the vector <int> length, where the i-th element is the length in minutes of movie i.



However, John is very tired, so it is possible for him to fall asleep while watching a movie.  The only way he can stay awake is to maintain a certain level of being scared.  He has a "scare level" which is a real number initially equal to 74.  His scare level will continuously decrease at a speed of 1 per minute.  For example, after 6 seconds, it will go down by 0.1.  Once this level falls below -0.5, John will fall asleep.  Each of John's movies has exactly one scary moment.  Once John sees this moment, his scare level will instantly increase by 47.  The scary moments are given in the vector <int> scary.  In movie i, the scary moment will occur exactly scary[i] minutes after the beginning of the movie.



John would like to determine the best order in which to watch the movies.  Each order can be described by an vector <int> containing N distinct numbers between 0 and N-1, inclusive.  The first element is the number of the first movie he watches, the second element is the number of the second movie he watches, and so on.  Once a movie is finished playing, the next one starts immediately.  If John falls asleep while watching a movie, he won't be able to watch the rest of the current movie, and he won't be able to watch any of the movies that he planned to watch after the current movie.  Among all the possible orders, return the one that allows John to watch as many movies as possible in their entirety (i.e., from beginning to end) before falling asleep.  If there are several such orders, return the one that comes earliest lexicographically.


DEFINITION
Class:TheMoviesLevelTwoDivOne
Method:find
Parameters:vector <int>, vector <int>
Returns:vector <int>
Method signature:vector <int> find(vector <int> length, vector <int> scary)


NOTES
-A vector <int> A comes before a vector <int> B lexicographically if A contains a smaller number at the first index where they differ.


CONSTRAINTS
-length will contain between 1 and 20 elements, inclusive.
-length and scary will contain the same number of elements.
-Each element of length will be between 2 and 474, inclusive.
-The i-th element of scary will be between 1 and length[i] - 1, inclusive.


EXAMPLES

0)
{100, 50}
{1, 1}

Returns: {0, 1 }

There are two possible playlists, and John can watch either one in its entirety without falling asleep.

1)
{100, 50}
{1, 49}

Returns: {1, 0 }

The only way John can see all the movies is to start with the last one.

2)
{100, 100, 100, 100}
{77, 76, 75, 74}

Returns: {3, 0, 1, 2 }

If John starts with the last movie, he will fall asleep during the second movie.  If he starts with any other movie, he will fall asleep during the first movie.

3)
{100}
{99}

Returns: {0 }

Here John has no choice at all.

*/
// END CUT HERE
#line 71 "TheMoviesLevelTwoDivOne.cpp"

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


class TheMoviesLevelTwoDivOne {
	public:
	vector <int> find(vector <int> length, vector <int> scary) {
		
	}

	public:
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {100, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {100, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 49}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {100, 100, 100, 100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {77, 76, 75, 74}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3, 0, 1, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {99}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	TheMoviesLevelTwoDivOne* q = new TheMoviesLevelTwoDivOne();
	q->run_test(-1);
	delete q;

	return 0;
}
// END CUT HERE
