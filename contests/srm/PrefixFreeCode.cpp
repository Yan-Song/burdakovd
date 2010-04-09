// BEGIN CUT HERE
// PROBLEM STATEMENT
// A prefix-free code of size N which uses K characters is a set of N distinct 
// strings such that 
// 
// each string of the set contains only characters '0','1', ..., ('0'+K-1)
// 
// no string of the set is a prefix of any other string of the set.
// 
// The cost of a prefix-free code can be calculated as sum of costs of characters 
// used to write down
// all strings of the set.
// 
// You are given the size of the code N and the costs of using the characters 
// characterCosts.
// Return the minimal possible cost of a prefix-free code of size N which uses 
// these character costs.
// 
// 
// DEFINITION
// Class:PrefixFreeCode
// Method:minCost
// Parameters:int, vector <int>
// Returns:int
// Method signature:int minCost(int N, vector <int> characterCosts)
// 
// 
// CONSTRAINTS
// -N will be between 2 and 500, inclusive.
// -characterCosts will contain between 2 and 50 elements, inclusive.
// -Each element of characterCosts will be between 1 and 100, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 3
// {1,4}
// 
// Returns: 11
// 
// The cheapest code of size 3 is {"00","01","1"}.
// 
// 1)
// 3
// {1,3,5}
// 
// Returns: 9
// 
// Here exist two cheapest codes - {"0","1","2"} and {"00","01","1"}.
// 
// 2)
// 500
// { 2, 4, 6, 8,10,12,14,16,18,20,
//  22,24,26,28,30,32,34,36,38,40,
//  42,44,46,48,50,52,54,56,58,60,
//  62,64,66,68,70,72,74,76,78,80,
//  82,84,86,88,90,92,94,96,98,100}
// 
// Returns: 9464
// 
// 
// 
// 3)
// 500
// {1,2,3,4,5,6,7,8,9,10}
// 
// Returns: 4732
// 
// 
// 
// END CUT HERE

#line 75 "PrefixFreeCode.cpp"
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

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define fosz(i,s,x) for(int i=s; i<x.size(); i++)
#define foreach(i,x) fosz(i,0,x)
#define debug(x) cerr<<(#x)<<" = "<<(x)<<endl
#define adebug(x,n) fo(i,0,n) cerr<<(#x)<<"["<<i<<"] = "<<x[i]<<endl
#define vdebug(x) foreach(i,x) cerr<<(#x)<<"["<<i<<"] = "<<x[i]<<endl
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()
 
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
const i64 inf=1000000000;

class PrefixFreeCode {
	public:
	int minCost(int N, vector <int> characterCosts) {
		//
	}
};


// BEGIN CUT HERE

namespace moj_harness {
	int isinf(double x) {return !_finite(x);}
	int isnan(double x) {return _isnan(x);}
};

namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if ( casenum != -1 ) {
			if ( run_test_case( casenum ) == -1 && !quiet )
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			return;
		}
		
		int correct = 0, total = 0;
		for ( int i=0;; ++i ) {
			int x = run_test_case(i);
			if ( x == -1 ) {
				if ( i >= 100 ) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if ( total == 0 ) {
			cerr << "No test cases run." << endl;
		} else if ( correct < total ) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}
	
	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if ( expected == received ) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;
		
		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl; 
			cerr << "    Received: " << received << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case( int casenum ) {
		switch( casenum ) {
		case 0: {
			int N                     = 3;
			int characterCosts[]      = {1,4};
			int expected__            = 11;

			clock_t start__           = clock();
			int received__            = PrefixFreeCode().minCost( N, vector <int>( characterCosts, characterCosts + ( sizeof characterCosts / sizeof characterCosts[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			int N                     = 3;
			int characterCosts[]      = {1,3,5};
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = PrefixFreeCode().minCost( N, vector <int>( characterCosts, characterCosts + ( sizeof characterCosts / sizeof characterCosts[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			int N                     = 500;
			int characterCosts[]      = { 2, 4, 6, 8,10,12,14,16,18,20,  22,24,26,28,30,32,34,36,38,40,  42,44,46,48,50,52,54,56,58,60,  62,64,66,68,70,72,74,76,78,80,  82,84,86,88,90,92,94,96,98,100};
			int expected__            = 9464;

			clock_t start__           = clock();
			int received__            = PrefixFreeCode().minCost( N, vector <int>( characterCosts, characterCosts + ( sizeof characterCosts / sizeof characterCosts[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			int N                     = 500;
			int characterCosts[]      = {1,2,3,4,5,6,7,8,9,10};
			int expected__            = 4732;

			clock_t start__           = clock();
			int received__            = PrefixFreeCode().minCost( N, vector <int>( characterCosts, characterCosts + ( sizeof characterCosts / sizeof characterCosts[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 4: {
			int N                     = ;
			int characterCosts[]      = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PrefixFreeCode().minCost( N, vector <int>( characterCosts, characterCosts + ( sizeof characterCosts / sizeof characterCosts[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 5: {
			int N                     = ;
			int characterCosts[]      = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PrefixFreeCode().minCost( N, vector <int>( characterCosts, characterCosts + ( sizeof characterCosts / sizeof characterCosts[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			int N                     = ;
			int characterCosts[]      = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PrefixFreeCode().minCost( N, vector <int>( characterCosts, characterCosts + ( sizeof characterCosts / sizeof characterCosts[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
		default:
			return -1;
		}
	}
}


int main() {
    moj_harness::run_test();
}
// END CUT HERE
