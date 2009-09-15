// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// John and Brus are training for a card game tournament.
// There they will be playing Black Jack.
// Black Jack is played using a standard deck containing 52 distinct cards.
// Each card can be represented as a two-character string where the first 
// character is the rank ('2' - '9' for ranks Two through Nine, 'T' for Ten, 'J' 
// for Jack, 'Q' for Queen, 'K' for King and 'A' for Ace) and the second 
// character is the suit ('S' for Spades, 'C' for Clubs, 'D' for Diamonds and 'H' 
// for Hearts).
// For example, the Jack of Spades can be represented as "JS" and the Nine of 
// Hearts as "9H".
// 
// 
// 
// Each time a player receives a card from the deck, his score increases by the 
// card's value.
// Ranks Two through Ten have values of 2 - 10, respectively.
// Jacks, Queens and Kings each have a value of 10, and Aces have a value of 11.
// 
// 
// 
// Brus randomly shuffles the full card deck and gives John one or more cards 
// from the top of the deck.
// You are given a vector <string> cards, where each element represents a single 
// card given to John in this initial step.
// John will then take extra cards from the top of the deck, one by one, until 
// his score is greater than or equal to 21.
// Return the expected number of extra cards that John will take.
// 
// 
// 
// DEFINITION
// Class:TheBlackJackDivOne
// Method:expected
// Parameters:vector <string>
// Returns:double
// Method signature:double expected(vector <string> cards)
// 
// 
// NOTES
// -The returned value must be accurate to within a relative or absolute value of 
// 1E-9.
// 
// 
// CONSTRAINTS
// -cards will contain between 1 and 50 elements, inclusive.
// -Each element of cards will contain exactly two characters, where the first 
// character is '2'-'9', 'T', 'J', 'Q', 'K' or 'A', and the second character is 
// 'S', 'C', 'D' or 'H'.
// -All elements of cards will be distinct.
// 
// 
// EXAMPLES
// 
// 0)
// {"JS"}
// 
// Returns: 2.105854341736695
// 
// 
// 
// 1)
// {"KD", "8S"}
// 
// Returns: 1.08
// 
// John will take the second extra card only if the first one is Two.
// 
// 2)
// {"KD", "2S", "2C", "2D", "2H"}
// 
// Returns: 1.0
// 
// The same situation, but here there are no Twos left in the deck.
// 
// 3)
// {"AS", "KS", "9S", "JC", "2D"}
// 
// Returns: 0.0
// 
// Here John's score is already more than 21.
// 
// END CUT HERE

#line 88 "TheBlackJackDivOne.cpp"
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

class TheBlackJackDivOne {
	public:
	double expected(vector <string> cards) {
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
			string cards[]            = {"JS"};
			double expected__         = 2.105854341736695;

			clock_t start__           = clock();
			double received__         = TheBlackJackDivOne().expected( vector <string>( cards, cards + ( sizeof cards / sizeof cards[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			string cards[]            = {"KD", "8S"};
			double expected__         = 1.08;

			clock_t start__           = clock();
			double received__         = TheBlackJackDivOne().expected( vector <string>( cards, cards + ( sizeof cards / sizeof cards[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			string cards[]            = {"KD", "2S", "2C", "2D", "2H"};
			double expected__         = 1.0;

			clock_t start__           = clock();
			double received__         = TheBlackJackDivOne().expected( vector <string>( cards, cards + ( sizeof cards / sizeof cards[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			string cards[]            = {"AS", "KS", "9S", "JC", "2D"};
			double expected__         = 0.0;

			clock_t start__           = clock();
			double received__         = TheBlackJackDivOne().expected( vector <string>( cards, cards + ( sizeof cards / sizeof cards[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 4: {
			string cards[]            = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheBlackJackDivOne().expected( vector <string>( cards, cards + ( sizeof cards / sizeof cards[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 5: {
			string cards[]            = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheBlackJackDivOne().expected( vector <string>( cards, cards + ( sizeof cards / sizeof cards[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			string cards[]            = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheBlackJackDivOne().expected( vector <string>( cards, cards + ( sizeof cards / sizeof cards[0] ) ) );
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
