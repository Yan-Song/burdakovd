// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// John is obsessed with security.
// He has several old houses and he wants to build one new.
// John is very afraid of thieves, so he will choose the location of the new 
// house using the following method.
// From each of his old houses, he will measure the Manhattan distance to the new 
// house.
// He will then take the k-th (1 based) shortest distance.
// The location that minimizes this distance will be the location of his new house.
// 
// 
// 
// You are given the locations of his old houses in vector <int>s x and y.
// The i-th old house is located at (x[i], y[i]).
// Return the smallest possible k-th distance.
// 
// 
// 
// DEFINITION
// Class:TheNewHouseDivOne
// Method:distance
// Parameters:vector <int>, vector <int>, int
// Returns:double
// Method signature:double distance(vector <int> x, vector <int> y, int k)
// 
// 
// NOTES
// -The returned value must be accurate to within a relative or absolute value of 
// 1E-9.
// -The Manhattan distance between two points (x1, y1) and (x2, y2) is |x1 - x2| 
// + |y1 - y2|.
// -Several houses can be located at the same point.
// 
// 
// CONSTRAINTS
// -x will contain between 1 and 50 elements, inclusive.
// -x and y will contain the same number of elements.
// -Each element of x will be between -50 and 50, inclusive.
// -Each element of y will be between -50 and 50, inclusive.
// -k will be between 1 and the number of elements in x, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {-1, -1, 1, 1}
// {-1, 1, -1, 1}
// 3
// 
// Returns: 2.0
// 
// One of the optimal ways is to build a new house at (0, 0).
// 
// 1)
// {-1, -1, 1, 1}
// {-1, 1, -1, 1}
// 2
// 
// Returns: 1.0
// 
// And here we have four possible locations for the new house - (-1, 0), (1, 0), 
// (0, -1) and (0, 1).
// 
// 2)
// {4, 4, 4, 4, 4, 3, 3, 5, 5}
// {7, 7, 7, 4, 4, 5, 6, 5, 6}
// 9
// 
// Returns: 1.5
// 
// Some houses are located at the same point.
// 
// 3)
// {30, -15, 24, -23, 43, -8, -6, -47, 23, -11, 43, 6, -18, 44, -46, 16, 32, 31, 
// 13, 9, 22, 25, 4, -44, 38, -41, -20, 41, -35, 7, 25, 39, -36, -20, -5, -38, 
// -15, -22, 0}
// {-45, -7, -33, 31, -8, -33, -20, -14, -50, -48, -31, 35, -24, -31, -11, 41, 
// -41, -11, 46, -1, -5, 5, -39, -26, -40, -9, 16, 38, -30, 34, 46, -17, -27, 33, 
// -38, 28, 46, -16, -46}
// 13
// 
// Returns: 32.0
// 
// END CUT HERE

#line 89 "TheNewHouseDivOne.cpp"
#include <ctime>
#include <float.h>
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

class TheNewHouseDivOne {
	public:
	double distance(vector <int> x, vector <int> y, int k) {
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
	
	bool isinf(const double x) { return !_finite(x); }
	bool isnan(const double x) { return _isnan(x); }
	static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ( double expected, double result ) { if ( isnan( expected ) ) { return isnan( result ); } else if ( isinf( expected ) ) { if ( expected > 0 ) { return result > 0 && isinf( result ); } else { return result < 0 && isinf( result ); } } else if ( isnan( result ) || isinf( result ) ) { return false; } else if ( fabs( result - expected ) < MAX_DOUBLE_ERROR ) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
	double moj_relative_error( double expected, double result ) { if ( isnan( expected ) || isinf( expected ) || isnan( result ) || isinf( result ) || expected == 0 ) return 0; return fabs( result-expected ) / fabs( expected ); }
	
	int verify_case(int casenum, const double &expected, const double &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if ( topcoder_fequ( expected, received ) ) {
			verdict = "PASSED";
			double rerr = moj_relative_error( expected, received ); 
			if ( rerr > 0 ) {
				sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			int x[]                   = {-1, -1, 1, 1};
			int y[]                   = {-1, 1, -1, 1};
			int k                     = 3;
			double expected__         = 2.0;

			clock_t start__           = clock();
			double received__         = TheNewHouseDivOne().distance( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ), k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			int x[]                   = {-1, -1, 1, 1};
			int y[]                   = {-1, 1, -1, 1};
			int k                     = 2;
			double expected__         = 1.0;

			clock_t start__           = clock();
			double received__         = TheNewHouseDivOne().distance( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ), k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			int x[]                   = {4, 4, 4, 4, 4, 3, 3, 5, 5};
			int y[]                   = {7, 7, 7, 4, 4, 5, 6, 5, 6};
			int k                     = 9;
			double expected__         = 1.5;

			clock_t start__           = clock();
			double received__         = TheNewHouseDivOne().distance( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ), k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			int x[]                   = {30, -15, 24, -23, 43, -8, -6, -47, 23, -11, 43, 6, -18, 44, -46, 16, 32, 31, 13, 9, 22, 25, 4, -44, 38, -41, -20, 41, -35, 7, 25, 39, -36, -20, -5, -38, -15, -22, 0};
			int y[]                   = {-45, -7, -33, 31, -8, -33, -20, -14, -50, -48, -31, 35, -24, -31, -11, 41, -41, -11, 46, -1, -5, 5, -39, -26, -40, -9, 16, 38, -30, 34, 46, -17, -27, 33, -38, 28, 46, -16, -46};
			int k                     = 13;
			double expected__         = 32.0;

			clock_t start__           = clock();
			double received__         = TheNewHouseDivOne().distance( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ), k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 4: {
			int x[]                   = ;
			int y[]                   = ;
			int k                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheNewHouseDivOne().distance( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ), k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 5: {
			int x[]                   = ;
			int y[]                   = ;
			int k                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheNewHouseDivOne().distance( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ), k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			int x[]                   = ;
			int y[]                   = ;
			int k                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheNewHouseDivOne().distance( vector <int>( x, x + ( sizeof x / sizeof x[0] ) ), vector <int>( y, y + ( sizeof y / sizeof y[0] ) ), k );
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
