// BEGIN CUT HERE
// PROBLEM STATEMENT
// You are given a directed graph with n vertices, labeled 0 to n-1. The edges of 
// the graph contain values, and each time you traverse an edge, the value of 
// that edge gets added to your total score. If the same edge is traversed 
// multiple times, its value gets added every time. Values can be any number 
// between -499 and 499, inclusive. There are no edges that connect a vertex to 
// itself.
// 
// There's an ant at vertex 0 and it wants to get to vertex 1.  It must do this 
// in an integer number of seconds between 1 and timeLimit, inclusive. The ant 
// must make exactly stepsPerSecond steps each second, where each step consists 
// of moving from its current vertex V to an adjacent vertex W (W is adjacent to 
// V if there's a directed edge from V to W in the graph). The ant's goal is to 
// get the highest score possible.
// 
// The graph is given as three vector <string>s p0, p1 and p2. Concatenate the j-
// th characters of the i-th elements of p0, p1 and p2 (in that order) to get a 3-
// digit String S. If S is "000", then there is no edge from vertex i to vertex 
// j.  Otherwise, there is an edge from vertex i to vertex j, and its value is A 
// - 500, where A is the integer value of S. For example, if S is "100", then the 
// value is -400, and if S is "999", the value is 499.  Return the decimal 
// representation of the highest possible score as a string with no extra leading 
// zeroes.  If it is impossible to reach vertex 1 under the given constraints, 
// return "IMPOSSIBLE" (quotes for clarity) instead.
// 
// DEFINITION
// Class:AntOnGraph
// Method:maximumBonus
// Parameters:vector <string>, vector <string>, vector <string>, int, int
// Returns:string
// Method signature:string maximumBonus(vector <string> p0, vector <string> p1, 
// vector <string> p2, int stepsPerSecond, int timeLimit)
// 
// 
// CONSTRAINTS
// -p0 will contain between 2 and 50 elements, inclusive.
// -p1 and p2 will each contain the same number of elements as p0.
// -Each element in p0, p1 and p2 will contain exactly n characters, where n is 
// the number of elements in p0.
// -Each character in p0, p1 and p2 will be a digit ('0'-'9').
// -The i-th character of the i-th element of p0, p1 and p2 will be '0'.
// -stepsPerSecond will be between 1 and 100, inclusive.
// -timeLimit will be between 1 and 1000000000 (10^9), inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {"05","50"}
// {"00","00"}
// {"01","10"}
// 3
// 2
// 
// Returns: "3"
// 
// Here, there are two vertices.  There's an edge from vertex 0 to vertex 1 and 
// an edge from vertex 1 to vertex 0.  Both edges have a value of 1.  The ant 
// must make exactly 3 steps per second, so during the first second, it will make 
// the following moves: 0->1, 1->0, 0->1.  The time limit is 2, so there's time 
// for 3 more moves.  However, that would place the ant back at vertex 0, so the 
// ant should stop after the first second.
// 
// 1)
// {"05","50"}
// {"00","00"}
// {"01","10"}
// 2
// 3
// 
// Returns: "IMPOSSIBLE"
// 
// This is the same graph as the previous example, but this time, the ant must 
// make exactly 2 steps per second.  The ant can therefore never reach vertex 1 
// because it will always return to vertex 0 after each second.
// 
// 2)
// {"0550","0000","0005","5000"}
// {"0000","0000","0000","0000"}
// {"0110","0000","0001","1000"}
// 7
// 9
// 
// Returns: "49"
// 
// In this case the ant can traverse cycle 0->2->3->0 and earn 3 points. The ant 
// will keep moving along this cycle and finally go to vertex 1 and earn another 
// point. Thus the number of points modulo 3 is 1. Among all multiple of 7 less 
// than or equal to 63, 49 is the biggest one that satisfies the constraints.
// 
// 3)
// {"0540","0000","0004","4000"}
// {"0090","0000","0009","9000"}
// {"0190","0000","0009","9000"}
// 7
// 9
// 
// Returns: "-5"
// 
// This is the same as the previous example, but this time, the score for the 
// cycle is -3.
// 
// 4)
// {"079269665406","506042219642","720809987956",
//  "315099331918","952306192584","406390344278",
//  "999241035142","370785209189","728363760165",
//  "019367419000","279718007804","610188263490"}
// {"038604914953","804585763146","350629473403",
//  "028096403898","575205051686","427800322647",
//  "655168017864","582553303278","980402170192",
//  "620737714031","686142310509","092421645460"}
// {"063231394554","109852259379","740182746422",
//  "853015982521","476805512496","898530717993",
//  "430534005863","440162807186","132879980431",
//  "685312177072","780267345400","959947501200"}
// 37
// 1221
// 
// Returns: "20992235"
// 
// 
// 
// END CUT HERE

#line 127 "AntOnGraph.cpp"
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
const i64 inf = ((i64)1) << 54;

	i64 ndist[60][60][120]; // [from][to][n]
	i64 dd[60][60][120];

class AntOnGraph {


	int n;

	public:
	string maximumBonus(vector <string> p0, vector <string> p1, vector <string> p2, int stepsPerSecond, int timeLimit) {
		mset(ndist, 0);
		
		mset(dd, 0);
		n = p0.size();

		fo(i,0,n)
		{
			fo(j,0,n)
			{
				dd[i][j][0] = -inf;
				ndist[i][j][0] = -inf;
			}

			dd[i][i][0] = 0;
			ndist[i][i][0] = 0;
			
		}
		
		for(int a=0; a<n; ++a)
			for(int b=0; b<n; ++b)
			{
				int ans = 0;
				ans += 100*(p0[a][b]-'0');
				ans += 10*(p1[a][b]-'0');
				ans += 1*(p2[a][b]-'0');
				if(ans==0)
					dd[a][b][1] = -inf;
				else
					dd[a][b][1] = ans - 500;
			}

		for(int nn=2; nn<=stepsPerSecond; nn++)
			for(int a=0; a<n; a++)
				for(int b=0; b<n; b++)
				{
					i64& best = dd[a][b][nn];
					best = -inf;
					for(int i=0; i<n; ++i)
					{
						i64 cur = dd[a][i][nn-1] + dd[i][b][1];
						if(cur>best)
							best = cur;
					}
				}
		
		for(int a=0; a<n; ++a)
			for(int b=0; b<n; ++b)
				ndist[a][b][1] = dd[a][b][stepsPerSecond];

		for(int nn=2; nn<=n; ++nn)
			for(int a=0; a<n; ++a)
				for(int b=0; b<n; ++b)
				{
					i64& best = ndist[a][b][nn];
					best = -inf;
					for(int i=0; i<n; ++i)
					{
						i64 cur = ndist[a][i][nn-1] + ndist[i][b][1];
						if(a==0&&b==0&&nn==2)
							cur = cur;
						if(cur==6)
							cur=cur;
						if(cur>best)
							best = cur;
					}
				}

		i64 ans = -inf;
		for(int a=0; a<n; ++a)
			for(int b=0; b<n; ++b)
				for(int c=0; c<n; ++c)
					for(int cy=1; cy<=n; ++cy)
					{
						i64 t = timeLimit - a - b;
						if(t<0)
							continue;

						if(t%cy!=0)
							continue;

						t/=cy;
						if(a==0 && b==1 && c==0 && cy==1)
							t = t;

						i64 cur = ndist[0][c][a] + t * ndist[c][c][cy] + ndist[c][1][b];
						if(cur>ans)
						{
							debug(cur);
							ans = cur;
						}
					}
		debug(ans);
		if(ans < -10000000000000)
			return "IMPOSSIBLE";
		else
		{
			stringstream ss;
			ss<<ans;
			return ss.str();
		}
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
			string p0[]               = {"05","50"};
			string p1[]               = {"00","00"};
			string p2[]               = {"01","10"};
			int stepsPerSecond        = 3;
			int timeLimit             = 2;
			string expected__         = "3";

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus( vector <string>( p0, p0 + ( sizeof p0 / sizeof p0[0] ) ), vector <string>( p1, p1 + ( sizeof p1 / sizeof p1[0] ) ), vector <string>( p2, p2 + ( sizeof p2 / sizeof p2[0] ) ), stepsPerSecond, timeLimit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			string p0[]               = {"05","50"};
			string p1[]               = {"00","00"};
			string p2[]               = {"01","10"};
			int stepsPerSecond        = 2;
			int timeLimit             = 3;
			string expected__         = "IMPOSSIBLE";

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus( vector <string>( p0, p0 + ( sizeof p0 / sizeof p0[0] ) ), vector <string>( p1, p1 + ( sizeof p1 / sizeof p1[0] ) ), vector <string>( p2, p2 + ( sizeof p2 / sizeof p2[0] ) ), stepsPerSecond, timeLimit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			string p0[]               = {"0550","0000","0005","5000"};
			string p1[]               = {"0000","0000","0000","0000"};
			string p2[]               = {"0110","0000","0001","1000"};
			int stepsPerSecond        = 7;
			int timeLimit             = 9;
			string expected__         = "49";

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus( vector <string>( p0, p0 + ( sizeof p0 / sizeof p0[0] ) ), vector <string>( p1, p1 + ( sizeof p1 / sizeof p1[0] ) ), vector <string>( p2, p2 + ( sizeof p2 / sizeof p2[0] ) ), stepsPerSecond, timeLimit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			string p0[]               = {"0540","0000","0004","4000"};
			string p1[]               = {"0090","0000","0009","9000"};
			string p2[]               = {"0190","0000","0009","9000"};
			int stepsPerSecond        = 7;
			int timeLimit             = 9;
			string expected__         = "-5";

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus( vector <string>( p0, p0 + ( sizeof p0 / sizeof p0[0] ) ), vector <string>( p1, p1 + ( sizeof p1 / sizeof p1[0] ) ), vector <string>( p2, p2 + ( sizeof p2 / sizeof p2[0] ) ), stepsPerSecond, timeLimit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			string p0[]               = {"079269665406","506042219642","720809987956",  "315099331918","952306192584","406390344278",  "999241035142","370785209189","728363760165",  "019367419000","279718007804","610188263490"};
			string p1[]               = {"038604914953","804585763146","350629473403",  "028096403898","575205051686","427800322647",  "655168017864","582553303278","980402170192",  "620737714031","686142310509","092421645460"};
			string p2[]               = {"063231394554","109852259379","740182746422",  "853015982521","476805512496","898530717993",  "430534005863","440162807186","132879980431",  "685312177072","780267345400","959947501200"};
			int stepsPerSecond        = 37;
			int timeLimit             = 1221;
			string expected__         = "20992235";

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus( vector <string>( p0, p0 + ( sizeof p0 / sizeof p0[0] ) ), vector <string>( p1, p1 + ( sizeof p1 / sizeof p1[0] ) ), vector <string>( p2, p2 + ( sizeof p2 / sizeof p2[0] ) ), stepsPerSecond, timeLimit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 5: {
			string p0[]               = ;
			string p1[]               = ;
			string p2[]               = ;
			int stepsPerSecond        = ;
			int timeLimit             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus( vector <string>( p0, p0 + ( sizeof p0 / sizeof p0[0] ) ), vector <string>( p1, p1 + ( sizeof p1 / sizeof p1[0] ) ), vector <string>( p2, p2 + ( sizeof p2 / sizeof p2[0] ) ), stepsPerSecond, timeLimit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			string p0[]               = ;
			string p1[]               = ;
			string p2[]               = ;
			int stepsPerSecond        = ;
			int timeLimit             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus( vector <string>( p0, p0 + ( sizeof p0 / sizeof p0[0] ) ), vector <string>( p1, p1 + ( sizeof p1 / sizeof p1[0] ) ), vector <string>( p2, p2 + ( sizeof p2 / sizeof p2[0] ) ), stepsPerSecond, timeLimit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			string p0[]               = ;
			string p1[]               = ;
			string p2[]               = ;
			int stepsPerSecond        = ;
			int timeLimit             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus( vector <string>( p0, p0 + ( sizeof p0 / sizeof p0[0] ) ), vector <string>( p1, p1 + ( sizeof p1 / sizeof p1[0] ) ), vector <string>( p2, p2 + ( sizeof p2 / sizeof p2[0] ) ), stepsPerSecond, timeLimit );
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
