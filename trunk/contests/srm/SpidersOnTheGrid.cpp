#line 62 "SpidersOnTheGrid.cpp"

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

class SpidersOnTheGrid {
private:
	vector<string> B;
	public:

	bool check(int i, int j, char c)
	{
		return !(i >= 0 && i < B.size() && j >= 0 && j < B[0].size() && B[i][j] == c);
	}

	int find(vector <string> A) {
		int ans = 0;
		B = A;
		for(int i = 0; i < A.size(); ++i)
			for(int j = 0; j < A[0].size(); ++j)
				if(check(i - 1, j, 'S')
					&& check(i, j - 1, 'E')
					&& check(i, j + 1, 'W')
					&& check(i + 1, j, 'N'))
					++ans;

		return ans;
	}
	

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
