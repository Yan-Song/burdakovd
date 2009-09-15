// BEGIN CUT HERE
// PROBLEM STATEMENT
// We have a collection of strings, and we want to right justify them.
// Given a vector <string> text, your task is to return
// a vector <string> containing the same strings, right justified, in the same 
// order as they
// appear in text.
// 
// The returned strings should be padded on the left with space characters 
// so that they are all the same length as the longest string in textIn.
// 
// 
// 
// 
// DEFINITION
// Class:JustifyText
// Method:format
// Parameters:vector <string>
// Returns:vector <string>
// Method signature:vector <string> format(vector <string> text)
// 
// 
// CONSTRAINTS
// -text will contain between 1 and 50 elements inclusive
// -each element of text will contain only uppercase letters 'A'-'Z'
// -each element of text will contain between 1 and 50 characters inclusive
// 
// 
// EXAMPLES
// 
// 0)
// {"BOB","TOMMY","JIM"}
// 
// Returns: {"  BOB", "TOMMY", "  JIM" }
// 
// The longest string is "TOMMY" which has 5 characters. So the returned strings 
// all contain exactly 5 characters. 
// 
// 1)
// {"JOHN","JAKE","ALAN","BLUE"}
// 
// Returns: {"JOHN", "JAKE", "ALAN", "BLUE" }
// 
// No padding is necessary since they all contain the same number of characters.
// 
// 2)
// {"LONGEST","A","LONGER","SHORT"}
// 
// Returns: {"LONGEST", "      A", " LONGER", "  SHORT" }
// 
// END CUT HERE

#line 54 "JustifyText.cpp"
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

class JustifyText {
	public:
	vector <string> format(vector <string> text) {
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
	
	template<typename T> ostream& operator<<( ostream &os, const vector<T> &v ) { os << "{"; for ( typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi ) { if ( vi != v.begin() ) os << ","; os << " " << *vi; } os << " }"; return os; }
	template<> ostream& operator<<( ostream &os, const vector<string> &v ) { os << "{"; for ( vector<string>::const_iterator vi=v.begin(); vi!=v.end(); ++vi ) { if ( vi != v.begin() ) os << ","; os << " \"" << *vi << "\""; } os << " }"; return os; }

	int verify_case(int casenum, const vector <string> &expected, const vector <string> &received, clock_t elapsed) { 
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
			string text[]             = {"BOB","TOMMY","JIM"};
			string expected__[]       = {"  BOB", "TOMMY", "  JIM" };

			clock_t start__           = clock();
			vector <string> received__ = JustifyText().format( vector <string>( text, text + ( sizeof text / sizeof text[0] ) ) );
			return verify_case( casenum, vector <string>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}
		case 1: {
			string text[]             = {"JOHN","JAKE","ALAN","BLUE"};
			string expected__[]       = {"JOHN", "JAKE", "ALAN", "BLUE" };

			clock_t start__           = clock();
			vector <string> received__ = JustifyText().format( vector <string>( text, text + ( sizeof text / sizeof text[0] ) ) );
			return verify_case( casenum, vector <string>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}
		case 2: {
			string text[]             = {"LONGEST","A","LONGER","SHORT"};
			string expected__[]       = {"LONGEST", "      A", " LONGER", "  SHORT" };

			clock_t start__           = clock();
			vector <string> received__ = JustifyText().format( vector <string>( text, text + ( sizeof text / sizeof text[0] ) ) );
			return verify_case( casenum, vector <string>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}

		// custom cases

/*      case 3: {
			string text[]             = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = JustifyText().format( vector <string>( text, text + ( sizeof text / sizeof text[0] ) ) );
			return verify_case( casenum, vector <string>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}*/
/*      case 4: {
			string text[]             = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = JustifyText().format( vector <string>( text, text + ( sizeof text / sizeof text[0] ) ) );
			return verify_case( casenum, vector <string>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}*/
/*      case 5: {
			string text[]             = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = JustifyText().format( vector <string>( text, text + ( sizeof text / sizeof text[0] ) ) );
			return verify_case( casenum, vector <string>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
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
