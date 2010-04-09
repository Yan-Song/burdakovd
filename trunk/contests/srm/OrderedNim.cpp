#line 62 "OrderedNim.cpp"

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

class OrderedNim {
	public:
	
	string winner(vector <int> layout) {
		return _winner(layout) ? "Alice" : "Bob";
	}

	bool _winner(vector <int> layout) {
		bool win = false;
		for(int i = 0; i < layout.size(); ++i)
			if(layout[i] == 1)
				win = !win;
			else
				return !win;
		return win;
	}
	

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
