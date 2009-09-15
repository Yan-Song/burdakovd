// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// Consider the 3x3x3 cube shown above.  There are nine squares on each of its 
// six faces, and each face is colored using the following pattern:
// 	
// 		The four corner squares are red.
// 		The center square is green.
// 		The remaining four squares are blue.
// 	
// There is a robot standing in the green square of the top face of the cube, 
// facing one of the blue squares.  It receives a sequence of commands.  Each 
// command is one of the following:
// 	
// 		'L': Stay in the current square and turn left 90 degrees.
// 		'R': Stay in the current square and turn right 90 degrees.
// 		'W': Walk forward in the current direction to the next square.
// 	
// Note that the robot can cross an edge of the cube into another face.  When 
// that happens, the cube will rotate automatically to keep the robot on the top 
// face.
// You are given a string movement containing the sequence of commands received 
// by the robot.  The robot will execute all of the commands in order.  Return 
// the color of the robot's final landing square - "RED", "GREEN" or "BLUE" (all 
// quotes for clarity).
// 
// DEFINITION
// Class:CubeWalking
// Method:finalPosition
// Parameters:string
// Returns:string
// Method signature:string finalPosition(string movement)
// 
// 
// NOTES
// -The answer does not depend on the initial direction of the robot.
// 
// 
// CONSTRAINTS
// -movement will contain between 1 and 50 characters, inclusive.
// -Each character in movement will be 'L', 'R' or 'W'.
// 
// 
// EXAMPLES
// 
// 0)
// "LLRR"
// 
// Returns: "GREEN"
// 
// In this example, the robot only turns left or right without ever moving to a 
// different square.
// 
// 1)
// "WWWWWWWWWWWW"
// 
// Returns: "GREEN"
// 
// Walking 12 squares forward in the same direction will lead the robot back to 
// its original position.
// 
// 2)
// "WLWRW"
// 
// Returns: "RED"
// 
// 
// 
// 3)
// "WWLLWRWLWLLRWW"
// 
// Returns: "BLUE"
// 
// 
// 
// END CUT HERE

#line 79 "CubeWalking.cpp"
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

class CubeWalking {
	public:
	string finalPosition(string movement) {
		int x=1, y=1, dx=1, dy=0;
		foreach(i,movement)
			if(movement[i]=='L')
			{
				int t = dx;
				dx = -dy;
				dy = t;
			}
			else if(movement[i]=='R')
			{
				int t = dx;
				dx = dy;
				dy = -t;
			}
			else if(movement[i]=='W')
			{
				x += dx + 3;
				y += dy + 3;
				x %= 3;
				y %= 3;
			}

		debug(x);
		debug(y);
		if(x==1 && y==1)
			return "GREEN";

		if(x==1 || y==1)
			return "BLUE";

		return "RED";
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
	
	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
			cerr << "    Expected: \"" << expected << "\"" << endl; 
			cerr << "    Received: \"" << received << "\"" << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case( int casenum ) {
		switch( casenum ) {
		case 0: {
			string movement           = "LLRR";
			string expected__         = "GREEN";

			clock_t start__           = clock();
			string received__         = CubeWalking().finalPosition( movement );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			string movement           = "WWWWWWWWWWWW";
			string expected__         = "GREEN";

			clock_t start__           = clock();
			string received__         = CubeWalking().finalPosition( movement );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			string movement           = "WLWRW";
			string expected__         = "RED";

			clock_t start__           = clock();
			string received__         = CubeWalking().finalPosition( movement );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			string movement           = "WWLLWRWLWLLRWW";
			string expected__         = "BLUE";

			clock_t start__           = clock();
			string received__         = CubeWalking().finalPosition( movement );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 4: {
			string movement           = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CubeWalking().finalPosition( movement );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 5: {
			string movement           = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CubeWalking().finalPosition( movement );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			string movement           = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CubeWalking().finalPosition( movement );
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
