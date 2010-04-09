// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
John and Brus have an interest in team sports tournaments.
They are currently investigating a basketball tournament.
Basketball is a team sport in which two teams of five players try to score points against one another by placing a ball through a ten foot high hoop.
Basketball is one of the most popular and widely viewed sports in the world.



There are n teams in the tournament. Each pair of teams plays exactly two games against each other. Each game results in one team winning.  There are no draws.
After the tournament is over, the team with the highest total number of wins takes 1st place, the team with the second highest number of wins takes 2nd place, and so on.



A sequence of integers W1, W2, ..., Wn is called a W-sequence if there exists a tournament where the team that took i-th place has exactly Wi total wins (for all i between 1 and n, inclusive).
Given ints n and m, return the number of W-sequences consisting of n integers where W1 = m.


DEFINITION
Class:TheBasketballDivOne
Method:find
Parameters:int, int
Returns:int
Method signature:int find(int n, int m)


CONSTRAINTS
-n will be between 2 and 5, inclusive.
-m will be between 1 and 9, inclusive.


EXAMPLES

0)
2
1

Returns: 1

The only possible W-sequence is (1, 1).

1)
3
1

Returns: 0

There is no valid outcome where the winning team has just one win.

2)
3
3

Returns: 2

The two possible sequences are (3, 2, 1) and (3, 3, 0).

3)
4
6

Returns: 5



*/
// END CUT HERE

#line 72 "TheBasketballDivOne.cpp"

#include <string>
#include <vector>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <deque>
#include <set>
#include <cassert>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> v64;
typedef unsigned long long u64;

class TheBasketballDivOne {
	int cache[100][10][10];

	private:

	int solve(int s, int n, int m)
	{
		if(s < 0)
			return 0;
		
		if(s == 0)
			return n == 0 ? 1 : 0;

		if(n == 0)
			return 0;

		assert(n>0);
		assert(s>0);
		assert(m>=0);

		assert(n<=5);
		assert(m<=10);
		assert(s<=30);

		int& ans = cache[s][n][m];

		if(ans == -1)
		{
			ans = 0;
			for(int p = 0; p <= m; ++p)
				ans += solve(s - p, n - 1, p);
		}

		return ans;
	}

	public:

	TheBasketballDivOne()
	{
		memset(cache, -1, sizeof(cache));
	}

	int find(int n, int m) {
		int ans = solve(n * (n - 1) - m, n - 1, m);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 1; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 0; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 2; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 6; int Arg2 = 5; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
    int main()
        {
        TheBasketballDivOne ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
