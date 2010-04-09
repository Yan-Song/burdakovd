#line 62 "NotTwo.cpp"

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

class NotTwo {
	public:
	int calc(int x)
	{
		if(x<=0) return 0;

		if( x % 4 == 0)
		{
			return x/4 * 2;
		}
		else
		{
			if(x%4 ==1 || x%4==2)
				return 1 + calc(x-1);
			else
				return calc(x-1);
		}
	}
	int maxStones(int width, int height) {
		int k = height / 4;
		int ans = 2 * calc(width) * k;
		ans += 2 * calc(width-2) * k;
		height %= 4;

		if(height > 0)
		{
			ans += calc(width);
			--height;
		}
		if(height > 0)
		{
			ans += calc(width);
			--height;
		}

		if(height > 0)
		{
			ans += calc(width-2);
			--height;
		}

		return ans;

	}
	

};


int main()
{
	int a= (4%4==3);
	cout<<a<<endl;
	return 0;
}

// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
