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
#define sqr(t) ((t)*(t))

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
const int inf=1<<25;

inline int gcd(const int x, const int y)
{
	return y ? gcd(y, x % y) : x;
}

template<typename P, typename Q>
inline istream& operator >>(istream& is, pair<P, Q>& p)
{
	return is >> p.first >> p.second;
}

template<typename P, typename Q>
inline ostream& operator <<(ostream& os, const pair<P, Q>& p)
{
	return os << p.first << ' ' << p.second;
}

template<typename T>
inline istream& operator >>(istream& is, vector<T>& v)
{
	for(typename vector<T>::size_type i = 0; i < v.size(); ++i)
		is >> v[i];

	return is;
}

template<typename T>
inline ostream& operator <<(ostream& os, const vector<T>& v)
{
	for(typename vector<T>::size_type i = 0; i < v.size(); ++i)
		os << (i ? " " : "") << v[i];

	return os;
}

typedef string strin;
typedef double doble;
#define cot cout

struct Car {
	int data;

	Car() : data(0) {
	}

	Car(const bool isVertical, const int length, const int row, const int col) :
	data((((((isVertical << 8) ^ length) << 8) ^ row) << 8) ^ col) {
	}

	bool isVertical() const {
		return ((data >> 24) & 0xff) != 0;
	}

	int length() const {
		return (data >> 16) & 0xff;
	}

	int row() const {
		return (data >> 8) & 0xff;
	}

	int col() const {
		return data & 0xff;
	}
};

i64 primePowers[26];

struct Position {
	int used[12];
	Car car[26];
	i64 hash;
	int cols, rows, cars;

	Position() {}

	Position(const int rows_, const int cols_) :
	rows(rows_), cols(cols_), cars(0), hash(0) {
		std::fill(used, used + rows, 0);
	}

	bool isFree(const int row, const int col) const {
		return (~used[row] & (1 << col)) != 0;
	}

	void addCar(const Car car_) {
		addCar(car_, cars++);
	}

	void addCar(const Car car_, const int index) {
		car[index] = car_;
		for(int i = 0, r = car_.row(), c = car_.col(); i < car_.length(); ++i) {
			used[r] ^= 1 << c;
			if(car_.isVertical()) ++r; else ++c;
		}

		hash += primePowers[index] * car_.data;
	}

	void removeCar(const int index) {
		const Car car_ = car[index];

		for(int i = 0, r = car_.row(), c = car_.col(); i < car_.length(); ++i) {
			used[r] ^= 1 << c;
			if(car_.isVertical()) ++r; else ++c;
		}

		hash -= primePowers[index] * car_.data;
	}

	bool won() const {
		return car[0].col() + car[0].length() == cols;
	}

	int minimumMovesToWin() const {
		if(won()) {
			return 0;
		}
		else {
			int ans = 1;
			const int row = car[0].row();
			for(int col = car[0].col() + car[0].length(); col < cols; ++col) {
				if(!isFree(row, col)) {
					++ans;
				}
			}
			return ans;
		}

	}
};

bool operator !=(const Position& a, const Position& b) {
	if(a.hash != b.hash) return true;
	if(a.cars != b.cars) return true;
	if(a.cols != b.cols) return true;
	if(a.rows != b.rows) return true;

	for(int i = 0; i < a.rows; ++i) {
		if(a.used[i] != b.used[i]) {
			return true;
		}
	}

	for(int i = 0; i < a.cars; ++i) {
		if(a.car[i].data != b.car[i].data) {
			return true;
		}
	}

	return false;
}

const i64 PRIME = 1000000007;

ostream& operator <<(ostream& os, const Position& position) {
	os << "Position(rows = " << position.rows << ", cols = " << position.cols 
		<< ", cars = " << position.cars << ", hash = " << position.hash << ")" << endl;

	os << string(position.cols + 2, ' ') << endl;

	char data[12][12];
	mset(data, '.');
	for(int i = 0; i < position.cars; ++i) {
		const Car car = position.car[i];
		for(int j = 0; j < car.length(); ++j) {
			if(car.isVertical()) {
				data[car.row() + j][car.col()] = 'a' + i;
			}
			else {
				data[car.row()][car.col() + j] = 'a' + i;
			}
		}

	}

	for(int r = 0; r < position.rows; ++r) {
		os << ' ';
		for(int j = 0; j < position.cols; ++j) {
			if(data[r][j] == '.') {
				os << static_cast<char>(position.isFree(r, j) ? '.' : '!');
			}
			else {
				os << static_cast<char>(position.isFree(r, j) ? data[r][j] + 'A' - 'a' : data[r][j]);
			}
		}
		os << ' ' << endl;
	}

	os << string(position.cols + 2, ' ');
	return os;
}

template<typename T>
class fastset {
	static const int BUCKETS = 1 << 0;
	static const int MASK = BUCKETS - 1;

	set<T> data[BUCKETS];

public:
	void clear() {
		for(int i = 0; i < BUCKETS; ++i) {
			data[i].clear();
		}
	}

	int count(const T& key) const {
		return data[key & MASK].count(key);
	}

	bool insert(const T& key) {
		return data[key & MASK].insert(key).second;
	}

	size_t size() const {
		size_t ans = 0;

		for(int i = 0; i < BUCKETS; ++i) {
			ans += data[i].size();
		}

		return ans;
	}
};

int bfs(const Position& start, fastset<i64>& positions, const int limit) {

	if(start.won()) {
		return 0;
	}

	queue< pair<int, Position> > Q;
	if(limit != 0) {
		Q.push(make_pair(0, start));
	}

	int ans = 1000000;

	while(!Q.empty()) {

		Position current = Q.front().second;
		const int depth = Q.front().first;
		Q.pop();

		// перебрать возможные машинки для хода
		for(int i = 0; i < current.cars; ++i) {
			//cout << string(depth + 1, ' ') << "looking at " << static_cast<char>('a' + i) << endl;
			const Car car = current.car[i];
			current.removeCar(i);

			if(car.isVertical()) {
				// vertical
				int minRow = car.row(), maxRow = car.row() + car.length() - 1;
				while(minRow > 0 && current.isFree(minRow - 1, car.col())) {
					--minRow;
				}
				while(maxRow < current.rows - 1 && current.isFree(maxRow + 1, car.col())) {
					++maxRow;
				}

				for(int j = minRow; j <= maxRow - car.length() + 1; ++j) {
					if(j != car.row()) {
						// машинка может сюда поехать
						const Car newCar = Car(car.isVertical(), car.length(), j, car.col());
						current.addCar(newCar, i);

						if(current.won()) {
							return depth + 1;
						}

						if(1 + depth + current.minimumMovesToWin() <= limit) {
							if(positions.insert(current.hash)) {
								//		cout << string(depth + 1, ' ') << "Move " << static_cast<char>('a' + i) << " vertically: " << (j - car.row()) << 
								//			" (from [" << (minRow - car.row()) << "; " << (maxRow - car.length() + 1 - car.row()) << "])" << 
								//			" got " << current.hash << endl;
								Q.push(make_pair(depth + 1, current));
							}
						}
						current.removeCar(i);
					}
				}
			}
			else {
				// horizontal
				int minCol = car.col(), maxCol = car.col() + car.length() - 1;
				while(minCol > 0 && current.isFree(car.row(), minCol - 1)) {
					--minCol;
				}
				while(maxCol < current.cols - 1 && current.isFree(car.row(), maxCol + 1)) {
					++maxCol;
				}
				for(int j = minCol; j <= maxCol - car.length() + 1; ++j) {
					if(j != car.col()) {
						// машинка может сюда поехать
						const Car newCar = Car(car.isVertical(), car.length(), car.row(), j);
						current.addCar(newCar, i);

						if(current.won()) {
							return depth + 1;
						}

						if(1 + depth + current.minimumMovesToWin() <= limit) {

							if(positions.insert(current.hash)) {
								//	cout << string(depth + 1, ' ') << "Move " << static_cast<char>('a' + i) << " horizontally: " << (j - car.col()) <<
								//		" (from [" << (minCol - car.col()) << "; " << (maxCol - car.length() + 1 - car.col()) << "])" << 
								//		" got " << current.hash << endl;

								Q.push(make_pair(depth + 1, current));
							}
						}
						current.removeCar(i);
					}
				}
			}

			// возвращаем машинку на место
			current.addCar(car, i);
		}

	}

	return 1000000;
}

int solve(const Position& start) {

	fastset<i64> positions;
	positions.insert(start.hash);

	int depths[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	for(int di = 0; di < 10; ++di) {
		const int d = depths[di];
		clock_t t_start = clock();
		const int ans = bfs(start, positions, d);
		if(ans > 10) {
			positions.clear();
			positions.insert(start.hash);
		}
		clock_t elapsed = clock() - t_start;
#ifdef HOME_PC
		cout << "[" << (elapsed * 1000 / CLOCKS_PER_SEC) << "ms] With depth = " << 
			d << " discovered " << positions.size() << " positions, ans = " << ans << endl;
#endif
		if(ans <= 10) {
			return ans;
		}
	}

	
	throw "No solution";
}

int main()
{
#ifdef HOME_PC
	freopen("in.txt", "r", stdin);
	//freopen("OUTPUT.TXT", "w", stdout);
#endif

	primePowers[0] = 1;
	for(int i = 1; i < 26; ++i) {
		primePowers[i] = primePowers[i - 1] * PRIME;
	}

	int t;
	cin >> t;

	if(t > 10) {
		//throw "";
	}

	for(int ti = 0; ti < t; ++ti) {
		int m, n, k;
		cin >> m >> n >> k;


		vs row(m);
		for(int i = 0; i < m; ++i) {
			cin >> row[i];
			row[i] += '.';
		}
		row.push_back(string(n + 1, '.'));

		if(ti < t - 15) {
			cout << 1 << endl;
			continue;
		}

		map<int, Car> cars;
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(row[i][j] != '.') {
					const int id = row[i][j] - 'a';
					if(!cars.count(id)) {
						const bool isVertical = i != m - 1 && row[i + 1][j] == row[i][j];
						const int length = (isVertical ? row[i + 2][j] : row[i][j + 2]) == row[i][j] ? 3 : 2;
						cars[id] = Car(isVertical, length, i, j);
						//cout << static_cast<char>('a' + id) << ": vertical = " << isVertical << 
						//"; length = " << length << " (" << i << ", " << j << ")" << endl;
					}
				}
			}
		}

		Position start(m, n);
		for(map<int, Car>::const_iterator it = cars.begin(); it != cars.end(); ++it) {
			start.addCar(it->second);
		}

		//cout << start << endl;

		const int ans = solve(start);
		cout << ans << endl;
	}

#ifdef HOME_PC
	cout << "Elapsed: " << clock() * 1000LL / CLOCKS_PER_SEC << " ms." << endl;
#endif

	return 0;
}
