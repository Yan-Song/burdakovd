#line 108 "BunnyPuzzle.cpp"

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

class BunnyPuzzle {
	public:
	int theCount(vector <int> bunnies) {
		int ans = 0;

		for(int i = 0; i < bunnies.size(); ++i)
			for(int j = 0; j < bunnies.size(); ++j)
				if(i != j)
				{
					int c = 2 * bunnies[j] - bunnies[i];

					if(std::find(bunnies.begin(), bunnies.end(), c) == bunnies.end())
					{
						int d = std::lower_bound(bunnies.begin(), bunnies.end(), c) - (bunnies.begin() + i);
						if(d == 2 || d == -1)
						{
							++ans;
						}
					}
				}

		return ans;
	}
	

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
