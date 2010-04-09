// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
In the Kocurkovo village there is a shop that sells simple planar graphs. (See Notes for a definition.)


The cost of any graph with X vertices and Y edges is (X^3 + Y^2) gold coins.


Monika has N gold coins, and she wants to spend all of them on simple planar graphs.


Write a method that gets the value N and computes the minimum number of simple planar graphs Monika has to buy in order to spend exactly N gold coins.
She is allowed to buy multiple graphs of the same type.


DEFINITION
Class:PlanarGraphShop
Method:bestCount
Parameters:int
Returns:int
Method signature:int bestCount(int N)


NOTES
-A simple graph is an ordered pair (V,E) where V is a finite non-empty set of objects called vertices, and E is a finite set of edges. Each edge is a two-element subset of V.  (You can find drawings of several graphs in Example #3.)
-Note that a simple graph does not contain any loops (edges that connect a vertex to itself) and any duplicate edges. In other words, each edge connects two different vertices, and each pair of vertices is connected by at most one edge.
-A graph is called planar if it has a drawing in the plane such that no two edges intersect.
-Note that a simple planar graph does not have to be connected.


CONSTRAINTS
-N will be between 1 and 50,000, inclusive.


EXAMPLES

0)
36

Returns: 1

For 36 gold coins she can buy a triangle: a simple planar graph with 3 vertices and 3 edges.

1)
7

Returns: 7

The only simple planar graph that costs 7 gold coins or less is the graph that consists of a single vertex (and no edges). This graph costs 1^3 + 0^2 = 1, so Monika has to buy 7 of them.

2)
72

Returns: 2

She can buy 2 triangles for 36 gold coins each. No simple planar graph costs exactly 72 gold coins, hence the optimal answer in this case is 2.

3)
46

Returns: 3

All the graphs Monika can afford are shown in the following picture:



One optimal solution is to buy graphs worth 1 + 9 + 36 gold coins.

*/
// END CUT HERE

#line 75 "PlanarGraphShop.cpp"

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

int MAX=51000;

class PlanarGraphShop {
	private:
		vector<int> costs;
		vector<int> ans;

	inline int lim(const int v) const
	{
		if(v == 1)
			return 0;

		if(v == 2)
			return 1;

		return 3 * (v - 2);
	}

	public:

	PlanarGraphShop() : costs(), ans(MAX, 1000000)
	{
		costs.reserve(40 * 3 * 40);

		for(int v = 1; v <= 40; ++v)
			for(int e = 0; e <= lim(v); ++e)
			{
				if(v*v*v + e*e <= 50000)
					costs.push_back(v*v*v + e*e);
			}

		sort(costs.begin(), costs.end());

		costs.resize( unique(costs.begin(), costs.end()) - costs.begin() );

		std::cout<<"costs.size() == "<<costs.size()<<std::endl;

		ans[0] = 0;

		for(int g = 1; g < MAX; ++g)	
		{

			for(int cc = 0; cc < costs.size() && costs[cc] <= g; ++cc)
			{
				ans[g] = std::min(ans[g], ans[g - costs[cc]] + 1);
			}
		}

		std::cout<<"precalc done"<<std::endl;
	}

	int bestCount(int N) {
		return ans[N];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 36; int Arg1 = 1; verify_case(0, Arg1, bestCount(Arg0)); }
	void test_case_1() { int Arg0 = 7; int Arg1 = 7; verify_case(1, Arg1, bestCount(Arg0)); }
	void test_case_2() { int Arg0 = 72; int Arg1 = 2; verify_case(2, Arg1, bestCount(Arg0)); }
	void test_case_3() { int Arg0 = 46; int Arg1 = 3; verify_case(3, Arg1, bestCount(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
    int main()
        {
        PlanarGraphShop ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
