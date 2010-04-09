// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Taro and Hanako are playing a game called Nisoku, which is played as follows. Initially, there is a pile of cards. Each card contains a real number between 1.5 and 10.0, inclusive. You are given a vector <double> cards, the i-th element of which is the number written on the i-th card.


Repeat the following step until there is only one card left in the pile: Remove any two cards from the pile, and add one new card to the pile. Write either a+b or a*b on the new card, where a and b are the numbers written on the two cards that were removed.


Return the maximal possible number written on the final card in the pile.

DEFINITION
Class:Nisoku
Method:theMax
Parameters:vector <double>
Returns:double
Method signature:double theMax(vector <double> cards)


NOTES
-Your return value must have an absolute or relative error less than 1e-9.


CONSTRAINTS
-cards will contain between 2 and 50 elements, inclusive.
-Each element of cards will be between 1.5 and 10.0, inclusive.


EXAMPLES

0)
{5, 8}

Returns: 40.0

5 * 8 = 40.

1)
{1.5, 1.8}

Returns: 3.3

1.5 + 1.8 = 3.3.

2)
{8.26, 7.54, 3.2567}

Returns: 202.82857868



3)
{1.5, 1.7, 1.6, 1.5}

Returns: 9.920000000000002



4)
{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
10, 10, 10, 10, 10, 10, 10, 10, 10, 10}

Returns: 1.0E50

The answer can be extremely big.

*/
// END CUT HERE

#line 74 "Nisoku.cpp"

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

class Nisoku {
	public:
	double theMax(vector <double> cards) {
		sort(cards.begin(), cards.end());

		double ans = 0;

		for(int i = 0; i <= cards.size(); i += 2)
		{
			double p = 1;

			for(int j = 0; j < i / 2; ++j)
			{
				p *= (cards[j] + cards[i-1-j]);
			}

			for(int j = i; j < cards.size(); ++j)
			{
				p *= cards[j];
			}

			ans = max(ans, p);
		}

		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { double Arr0[] = {5, 8}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 40.0; verify_case(0, Arg1, theMax(Arg0)); }
	void test_case_1() { double Arr0[] = {1.5, 1.8}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.3; verify_case(1, Arg1, theMax(Arg0)); }
	void test_case_2() { double Arr0[] = {8.26, 7.54, 3.2567}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 202.82857868; verify_case(2, Arg1, theMax(Arg0)); }
	void test_case_3() { double Arr0[] = {1.5, 1.7, 1.6, 1.5}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 9.920000000000002; verify_case(3, Arg1, theMax(Arg0)); }
	void test_case_4() { double Arr0[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
10, 10, 10, 10, 10, 10, 10, 10, 10, 10}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.0E50; verify_case(4, Arg1, theMax(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
    int main()
        {
        Nisoku ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
