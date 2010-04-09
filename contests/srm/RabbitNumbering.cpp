#line 66 "RabbitNumbering.cpp"

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

class RabbitNumbering {
	public:
	int theCount(vector <int> maxNumber) {
		const int MOD = 1000000007;
		sort(maxNumber.begin(), maxNumber.end());

		i64 ans = 1;

		for(int i = 0; i < maxNumber.size(); ++i)
		{
			if(maxNumber[i] == i)
			{
				return 0;
			}
			else
			{
				ans *= (maxNumber[i] - i);
				ans %= MOD;
			}
		}

		return ans;
	}
	

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
