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
#include <iomanip>
#include <sstream>
#include <functional>
#include <numeric>

using namespace std;

typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<std::string> vs;

class Solver {
private:
	const int n, m;
	const vs& data;

	bool isValid(int i, int j) const {
		return i >= 0 && j >= 0 && i < n && j < m;
	}

	bool dfs(const int i, const int j, vvb& visited, vvi& colors, const int color, const bool withBorders) {
		if(isValid(i, j) && !visited[i][j]) {
			if(data[i][j] == '0') {
				visited[i][j] = true;
				colors[i][j] = color;
				for(int di = -1; di <= 1; ++di) {
					for(int dj = -1; dj <= 1; ++dj) {
						if((di || dj) && !(di && dj)) {
							dfs(i + di, j + dj, visited, colors, color, withBorders);
						}
					}
				}
				return true;
			} else if(withBorders) {
				if(colors[i][j] == -1) {
					visited[i][j] = true;
					colors[i][j] = color;
					return true;
				} else {
					return false;
				}
			} else {
				return true;
			}
		} else {
			return true;
		}
	}

public:
	Solver(const int n, const int m, const vs& data) : n(n), m(m), data(data) {
	}

	int solve() {
		int ans = 0;
		vvb visited(n, vb(m, false));
		vvi colors(n, vi(m, -1));

		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				if(i == 0 || j == 0 || i == n - 1 || j == m - 1) {
					dfs(i, j, visited, colors, 0, false);
				}
			}
		}

		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				if(data[i][j] == '0' && !visited[i][j]) {
					if(dfs(i, j, visited, colors, ans + 1, true)) {
						++ans;
					} else {
						throw "";
					}
				}
			}
		}
		
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				if(colors[i][j] == -1) {
					throw "";
				}
			}
		}

		return ans;
	}
};

int main()
{
#ifdef HOME_PC
	freopen("c:\\var\\tmp\\in.txt", "r", stdin);
	clock_t startTime = clock();
#endif

	int n;
	std::cin >> n;

	throw "";
	for(int i = 0; i < n; ++i) {
		cout << i + 1 << endl;
	}

#ifdef HOME_PC
	std::cerr << "[Total] Elapsed " << (1000 * static_cast<long long>(clock() - startTime) / CLOCKS_PER_SEC) << " ms." << std::endl;
#endif

	return 0;
}
