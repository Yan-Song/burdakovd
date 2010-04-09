// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// As a serious strategy-games player, you know how important it is for your country to have a strong economy.  In order to make this happen, you've just built n factories and hired k specialists.  Unfortunately, you now have no gold left, and you must figure out the fastest way to raise target units of gold.
In a single round, you earn F*S units of gold, where F is the number of factories and S is the number of specialists you currently have.  At the end of each round, you can build more factories and hire more specialists.  Building one new factory or hiring one new specialist costs price units of gold.  As long as you can afford them, there is no limit to the number of factories and specialists you have.  Return the minimum number of rounds required to earn at least target units of gold.

DEFINITION
Class:StrongEconomy
Method:earn
Parameters:long long, long long, long long, long long
Returns:long long
Method signature:long long earn(long long n, long long k, long long price, long long target)


CONSTRAINTS
-n, k, price and target will each be between 1 and 10^12, inclusive.


EXAMPLES

0)
2
1
2
10

Returns: 4

In the first round you will earn 2*1 = 2 units of gold and must spend them on hiring a new specialist. In each of the rounds that follow, you will earn 2*2 = 4 units of gold. You need 3 more rounds in order to earn at least 10 units of gold.

1)
2
1
2
9

Returns: 3

In the first round you will earn 2*1 = 2 units of gold and must spend them on hiring a new specialist. In the second round you will earn 2*2 = 4 units of gold and must spend them on building a factory and hiring another specialist. In the third round you will earn 3*3 = 9 units of gold.

2)
1
1
500000
1000002

Returns: 1000001

Wait 500000 rounds in order to earn 500000*1*1 = 500000 units of gold. At the end of the 500000th round, spend all your money to build a factory (or to hire a specialist). In each of the rounds that follow, you will earn 2*1 = 2 units of gold, so you need 500001 more rounds in order to earn the required 1000002 units of gold.

3)
5
4
15
100

Returns: 5

Don't spend your gold at all.

*/
// END CUT HERE

#line 65 "StrongEconomy.cpp"

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

class StrongEconomy {
	public:

	inline long long calc(long long n, long long k, long long target)
	{
		long long ans = target / (n * k);
		if(ans * n * k < target)
			++ans;
		return ans;
	}

	long long earn(long long n, long long k, long long price, long long target) {
		long long ans = 10000000000000LL;
		long long year = 0;
		long long built = 0;
		long long gold = 0;
		while(true) // цикл выполн€етс€ не более 3000000*2 раз, т.к. строим не более 3ћ раз и ждем не более
		{
			// если сейчас прекратить строить
			ans = min(ans, year + calc(n, k, target - gold));

			if(year >= ans)
				break;

			if(ans == year+1)
				break;

			if(gold >= price) 
			{
				if(built == 210000000LL) // уже много построено // должно хватить
				{
					break;
				}
				else
				{
					// build строить
					if(n < k)
						++n;
					else
						++k;
					gold -= price;
					++built;
				}
			}
			else
			{
				// wait ждать пока не наберЄтс€ голда на стройку
				long long wait = calc(n, k, price-gold);

				year += wait;
				gold += wait * (n*k);
			}
		}

		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 2LL; long long Arg1 = 1LL; long long Arg2 = 2LL; long long Arg3 = 10LL; long long Arg4 = 4LL; verify_case(0, Arg4, earn(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { long long Arg0 = 2LL; long long Arg1 = 1LL; long long Arg2 = 2LL; long long Arg3 = 9LL; long long Arg4 = 3LL; verify_case(1, Arg4, earn(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { long long Arg0 = 1LL; long long Arg1 = 1LL; long long Arg2 = 500000LL; long long Arg3 = 1000002LL; long long Arg4 = 1000001LL; verify_case(2, Arg4, earn(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { long long Arg0 = 5LL; long long Arg1 = 4LL; long long Arg2 = 15LL; long long Arg3 = 100LL; long long Arg4 = 5LL; verify_case(3, Arg4, earn(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
    int main()
        {
        StrongEconomy ___test; 
        //___test.run_test(-1); 
		std::cout<<___test.earn(1844674408, 999999999999, 1000000000000, 1000000000000)<<endl;
        } 
// END CUT HERE
