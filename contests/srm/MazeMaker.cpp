#line 118 "MazeMaker.cpp"

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
typedef pair<int,int> pii;

class MazeMaker {
	private:
	vector<string> maze;
	vector<vector<int> > d;
	vi moveRow, moveCol;

	void flood(int x, int y, int v)
	{
		if(x<0 || y < 0 || y>=maze.size() || x>=maze[0].size())
			return;

		if(maze[y][x] == 'X')
			return;

		if(d[y][x] <= v)
			return;

		d[y][x] = v;

		for(int i = 0; i < moveRow.size(); ++i)
			flood(x+moveCol[i], y+moveRow[i], v+1);
	}

	public:
	int longestPath(vector <string> maze, int startRow, int startCol, vector <int> moveRow, vector <int> moveCol) {
		this->maze = maze;
		this->moveRow = moveRow;
		this->moveCol = moveCol;

		d.clear();
		d.resize(maze.size(), vi(maze[0].size(), 1000000));

		flood(startCol, startRow, 0);

		int mx = 0;
		for(int i = 0; i < maze.size(); ++i)
			for(int j = 0; j < maze[i].size(); ++j)
				if(maze[i][j] == '.')
					mx = std::max(mx, d[i][j]);

		if(mx == 1000000)
			return -1;
		else
			return mx;

	}
	

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
