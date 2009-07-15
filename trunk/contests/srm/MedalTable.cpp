// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// The Olympic Games in Athens end tomorrow.
// Given the results of the olympic disciplines, generate and return the medal 
// table.
// 
// The results of the disciplines are given as a vector <string> results,
// where each element is in the format "GGG SSS BBB". GGG, SSS and
// BBB are the 3-letter country codes (three capital letters from 'A' to 'Z') of 
// the countries winning
// the gold, silver and bronze medal, respectively.
// 
// The medal table is a vector <string> with an element for each country 
// appearing in results.
// Each element has to be in the format "CCO G S B" (quotes for clarity), where
// G, S and B are the number of gold, silver and bronze medals won
// by country CCO, e.g. "AUT 1 4 1". The numbers should not have any extra 
// leading zeros.
// 
// Sort the elements by the number of gold medals won in decreasing order.
// If several countries are tied, sort the tied countries by the number of silver 
// medals won in decreasing order.
// If some countries are still tied, sort the tied countries by the number of 
// bronze medals won in decreasing order.
// If a tie still remains, sort the tied countries by their 3-letter code in 
// ascending alphabetical order.
// 
// 
// DEFINITION
// Class:MedalTable
// Method:generate
// Parameters:vector <string>
// Returns:vector <string>
// Method signature:vector <string> generate(vector <string> results)
// 
// 
// CONSTRAINTS
// -results contains between 1 and 50 elements, inclusive.
// -Each element of results is formatted as described in the problem statement.
// -No more than 50 different countries appear in results.
// 
// 
// EXAMPLES
// 
// 0)
// {"ITA JPN AUS", "KOR TPE UKR", "KOR KOR GBR", "KOR CHN TPE"}
// 
// Returns: { "KOR 3 1 0",  "ITA 1 0 0",  "TPE 0 1 1",  "CHN 0 1 0",  "JPN 0 1 
// 0",  "AUS 0 0 1",  "GBR 0 0 1",  "UKR 0 0 1" }
// 
// These are the results of the archery competitions.
// 
// 1)
// {"USA AUT ROM"}
// 
// Returns: { "USA 1 0 0",  "AUT 0 1 0",  "ROM 0 0 1" }
// 
// 2)
// {"GER AUT SUI", "AUT SUI GER", "SUI GER AUT"}
// 
// Returns: { "AUT 1 1 1",  "GER 1 1 1",  "SUI 1 1 1" }
// */

// END CUT HERE

#line 66 "MedalTable.cpp"
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

class MedalTable {
	public:
	vector <string> generate(vector <string> results) {
		return vs();
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
			string results[]          = {"ITA JPN AUS", "KOR TPE UKR", "KOR KOR GBR", "KOR CHN TPE"};
			string expected__[]       = { "KOR 3 1 0",  "ITA 1 0 0",  "TPE 0 1 1",  "CHN 0 1 0",  "JPN 0 1 0",  "AUS 0 0 1",  "GBR 0 0 1",  "UKR 0 0 1" };

			clock_t start__           = clock();
			vector <string> received__ = MedalTable().generate( vector <string>( results, results + ( sizeof results / sizeof results[0] ) ) );
			return verify_case( casenum, vector <string>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}
		case 1: {
			string results[]          = {"USA AUT ROM"};
			string expected__[]       = { "USA 1 0 0",  "AUT 0 1 0",  "ROM 0 0 1" };

			clock_t start__           = clock();
			vector <string> received__ = MedalTable().generate( vector <string>( results, results + ( sizeof results / sizeof results[0] ) ) );
			return verify_case( casenum, vector <string>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}
		case 2: {
			string results[]          = {"GER AUT SUI", "AUT SUI GER", "SUI GER AUT"};
			string expected__[]       = { "AUT 1 1 1",  "GER 1 1 1",  "SUI 1 1 1" };

			clock_t start__           = clock();
			vector <string> received__ = MedalTable().generate( vector <string>( results, results + ( sizeof results / sizeof results[0] ) ) );
			return verify_case( casenum, vector <string>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}

		// custom cases

/*      case 3: {
			string results[]          = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = MedalTable().generate( vector <string>( results, results + ( sizeof results / sizeof results[0] ) ) );
			return verify_case( casenum, vector <string>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}*/
/*      case 4: {
			string results[]          = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = MedalTable().generate( vector <string>( results, results + ( sizeof results / sizeof results[0] ) ) );
			return verify_case( casenum, vector <string>( expected__, expected__ + ( sizeof expected__ / sizeof expected__[0] ) ), received__, clock()-start__ );
		}*/
/*      case 5: {
			string results[]          = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = MedalTable().generate( vector <string>( results, results + ( sizeof results / sizeof results[0] ) ) );
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
