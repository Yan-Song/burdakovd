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

#pragma comment(linker, "/STACK:128536216")

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
typedef vector<v64> vv64;
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

inline int nbits(const int x) {
	int ans = 0;
	for(int i = x; i > 0; i >>= 1) {
		ans += i & 1;
	}
	return ans;
}

template<class K, class V>
struct MyPair {
	K first;
	V second;
	
	MyPair() {
	}
	MyPair(const K& k, const V& v) : first(k), second(v) {
	}
};

template<class K, class V>
inline MyPair<K, V> MyMakePair(const K& k, const V& v) {
	return MyPair<K, V>(k, v);
}

#define pair MyPair
#define make_pair MyMakePair

const i64 MODULO_PH = 12137177371739LL;

struct PairHasher {	
	int operator ()(const pair<int, i64>& p) const {
		return static_cast<int>((p.second + i64(p.first) * MODULO_PH) * MODULO_PH);
	}
};

struct IdHasher {	
	int operator ()(const int p) const {
		return p;
	}
};

#define MYMAP
#ifdef MYMAP

//#define USE_VECTORS

#ifndef USE_VECTORS
#define SAFE_MAP
#endif

template<class K, class V, class KeyHasher>
class HashMap {
public:
	typedef pair<K, V> Element;
private:
	static const int size_ = 1 << 19;
	static const int size2_ = 1 << 3;
	KeyHasher hasher;

#ifdef USE_VECTORS
	typedef vector<Element> Data[size_];
	Data data_;
#else
	char count[size_];
	typedef Element Data[size_][size2_];
	//char data_[sizeof(Data) / sizeof(char)];
#endif
	Data* data;
	int currentSize;

	int makeHash(const K& key) const {
		return static_cast<unsigned int>(hasher(key)) * 31 % size_;
	}

public:
	typedef const Element *const_iterator;

	HashMap() : hasher(), currentSize(0)
#ifdef USE_VECTORS
		, data(&data_)
#else
		, data(static_cast<Data*>(malloc(sizeof(Data))))
		//, data(static_cast<Data*>(&data_)
#endif
	{
#ifndef USE_VECTORS
		mset(count, 0);
#endif
	}

#ifndef USE_VECTORS
	void clear() {
		mset(count, 0);
		currentSize = 0;
	}
#endif

	int size() const {
		return currentSize;
	}

	void reportCollision(const int h) const {
		cerr << "hard collision detected: [" << endl;
#ifdef USE_VECTORS
		for(size_t i = 0; i < (*data)[h].size(); ++i) {
			cerr << " key = [" << (*data)[h][i].first << "], hash = " << makeHash((*data)[h][i].first) << endl;
		}
#else
		for(int i = 0; i < count[h]; ++i) {
			cerr << " key = [" << (*data)[h][i].first << "], hash = " << makeHash((*data)[h][i].first) << endl;
		}
#endif
		throw "";
	}

	V& operator [](const K& key) {
		return get(key, V());
	}

	V& get(const K& key, const V& value) {
		const int h = makeHash(key);
#ifdef USE_VECTORS
		for(size_t i = 0; i < (*data)[h].size(); ++i) {
#else
		Element* const start = (*data)[h];
		Element* const end = start + count[h];
		for(Element* p = start; p != end; ++p) {
#endif
			if(p->first == key) {
				return p->second;
			}
		}

#ifdef USE_VECTORS
		if((*data)[h].size() < size2_) {
#else
		if(count[h] < size2_) {
#endif
			const Element element = make_pair(key, value);
#ifdef USE_VECTORS
			(*data)[h].push_back(element);
#else
			(*data)[h][count[h]++] = element;
#endif
			++currentSize;
#ifdef USE_VECTORS
			return (*data)[h][(*data)[h].size() - 1].second;
#else
			return (*data)[h][count[h] - 1].second;
#endif
		}

		reportCollision(h);
	}

#ifndef USE_VECTORS
	const_iterator find(const K& key) const {
		const int h = makeHash(key);
		const int cnt = count[h];
		for(int i = 0; i < cnt; ++i) {
			const Element& element = (*data)[h][i];
			if(element.first == key) {
				return &element;
			}
		}
		return end();
	}
#endif

	const_iterator end() const {
		return 0;
	}

	~HashMap() {
		#ifndef USE_VECTORS
			free(data);
		#endif
	}
};
#else

template<class K, class V, class KeyHasher>
class HashMap : public std::map<K, V> {
public:
	V& get(const K& key, const V& value) {
		std::map<K, V>::const_iterator it = this->find(key);
		if(it == this->end()) {
			return (*this)[key] = value;
		} else {
			return (*this)[key];
		}
	}
};

#endif

const i64 PoolHashModulo = 1030105007;

class Pool {
private:
	static i64 multipliers[8][8];
	static int h, w;
	i64 hash;
	int total;
	char pool[8][8];

	void generateMultipliers() {
		i64 seed = 1;
		for(int i = 0; i < h; ++i) {
			for(int j = 0; j < w; ++j) {
				multipliers[i][j] = seed;
				seed *= PoolHashModulo;
			}
		}
	}

public:
	Pool(const int h, const int w) : hash(0), total(0)
		//,	multipliers(h, v64(w)), pool(h, vi(w))
	{
		Pool::h = h;
		Pool::w = w;
		generateMultipliers();
		mset(pool, 0);
	}

	int height() const {
		return h;
	}

	int width() const {
		return w;
	}

	int isValid(const int row, const int col) const {
		return row >= 0 && row < h && col >= 0 && col < w;
	}

	int get(const int row, const int col) const {
		return pool[row][col];
	}

	void add(const int row, const int col, const int value) {
		pool[row][col] += value;
		total += value;
		hash += value * multipliers[row][col];
	}

	i64 getHash() const {
		return hash;
	}

	int getTotal() const {
		return total;
	}

	int hashPosition(const int row, const int col) const {
		return col + row * w;
	}
};

int Pool::h;
int Pool::w;
i64 Pool::multipliers[8][8];

const int MAX_QUEUE = 4000000;

int pushc, popc;

// Пришли в какое-то состояние
inline void processVertex(const int row, const int col, const Pool& pool, const int needTotal,
	queue< pair< pair<int, int>, Pool> >& q, HashMap<int, int, IdHasher>& cache,
	HashMap<int, int, IdHasher>& destination, const int multiplier) {

		if(pool.isValid(row, col) && pool.get(row, col) > 0) {
			const int hash = PairHasher()(make_pair(pool.hashPosition(row, col), pool.getHash()));
			if(pool.getTotal() == needTotal) {
				destination[hash] += multiplier;
				//cerr << "updated destination +" << multiplier << endl;
			} else {
#ifdef SAFE_MAP
				int& old = cache.get(hash, -1);
#else
				int old = cache.get(hash, -1);
#endif
				if(old < 0) {
					++pushc;
					q.push(make_pair(make_pair(row, col), pool));
					//cerr << "push (=" << multiplier << ")" << endl;
					old = multiplier;
				} else {
					// already in queue
					old += multiplier;
					//cerr << "update (+" << multiplier << ")" << endl;
				}
#ifndef SAFE_MAP
				cache[hash] = old;
#endif
			}
		}
}

void fillMap(Pool& pool,
			const int moves,
			HashMap<int, int, IdHasher>& destination,
			const int startRow,
			const int startCol) {
	pushc = popc = 0;
	const int needTotal = pool.getTotal() - moves;

	queue< pair< pair<int, int>, Pool> > q;
	HashMap<int, int, IdHasher> cache;
	processVertex(startRow, startCol, pool, needTotal, q, cache, destination, 1);

	while(!q.empty()) {
		const pair< pair<int, int>, Pool>& state = q.front();
		const pair<int, int>& coords = state.first;
		const int row = coords.first, col = coords.second;
		Pool pool = state.second;
		const int hash = PairHasher()(make_pair(pool.hashPosition(row, col), pool.getHash()));
		const int multiplier = cache[hash];
		pool.add(row, col, -1);
		processVertex(row, col - 2, pool, needTotal, q, cache, destination, multiplier);
		processVertex(row, col - 1, pool, needTotal, q, cache, destination, multiplier);
		processVertex(row, col + 1, pool, needTotal, q, cache, destination, multiplier);
		processVertex(row, col + 2, pool, needTotal, q, cache, destination, multiplier);
		processVertex(row - 2, col, pool, needTotal, q, cache, destination, multiplier);
		processVertex(row - 1, col, pool, needTotal, q, cache, destination, multiplier);
		processVertex(row + 1, col, pool, needTotal, q, cache, destination, multiplier);
		processVertex(row + 2, col, pool, needTotal, q, cache, destination, multiplier);
		q.pop();
		++popc;
	}

#ifdef HOME_PC
	cerr << "pushc = " << pushc << "; popc = " << popc << endl;
#endif
}

// Пришли в какое-то состояние
inline int rProcessVertex(const int row, const int col, const Pool& original,
	Pool& pool_, const int needTotal,
	queue< pair< pair<int, int>, Pool> >& q,
	const HashMap<int, int, IdHasher>& fromStart,
	HashMap<int, int, IdHasher>& cache,
	const int multiplier,
	int* const multipliers, 
	const int popped) {

		if(pool_.isValid(row, col) && pool_.get(row, col) < original.get(row, col)) {
			//Pool pool = pool_;
			pool_.add(row, col, 1);
			const int hash = PairHasher()(make_pair(pool_.hashPosition(row, col), pool_.getHash()));

			int ans;

			if(pool_.getTotal() == needTotal) {
				const pair<int, int> *element = fromStart.find(hash);
				ans = element ? multiplier * element->second : 0;
			} else {
#ifdef SAFE_MAP
				int& old = cache.get(hash, -1);
#else
				int old = cache.get(hash, -1);
#endif
				if(old < 0) {
					++pushc;
					old = popped + q.size();
					q.push(make_pair(make_pair(row, col), pool_));
					multipliers[old] = multiplier;
				} else {
					multipliers[old] += multiplier;
				}
#ifndef SAFE_MAP
				cache[hash] = old;
#endif
				ans = 0;
			}

			pool_.add(row, col, -1);

			return ans;
		} else {
			return 0;
		}
}

int multipliers[MAX_QUEUE];

int fromFinish(const Pool& original, Pool& reverse, const int moves, const HashMap<int, int, IdHasher>& fromStart,
	const int finishRow, const int finishCol, HashMap<int, int, IdHasher>& cache) {
	
	pushc = popc = 0;

	const int needTotal = moves + 1;
	int popped = 0;
	queue< pair< pair<int, int>, Pool> > q;
	
	rProcessVertex(finishRow, finishCol, original, reverse, needTotal, q, fromStart, cache, 1, multipliers, popped);

	int prevTotal = 0;
	int ans = 0;
	while(!q.empty()) {
		const pair< pair<int, int>, Pool>& state = q.front();
		const pair<int, int>& coords = state.first;
		const int row = coords.first, col = coords.second;

		Pool pool = state.second;

		if(pool.getTotal() > prevTotal) {
			prevTotal = pool.getTotal();
			//cache.clear();
		}

		const int hash = PairHasher()(make_pair(pool.hashPosition(row, col), pool.getHash()));
		const int multiplier = multipliers[popped];
		
		ans += rProcessVertex(row, col - 2, original, pool, needTotal, q, fromStart, cache, multiplier, multipliers, popped);
		ans += rProcessVertex(row, col - 1, original, pool, needTotal, q, fromStart, cache, multiplier, multipliers, popped);
		ans += rProcessVertex(row, col + 1, original, pool, needTotal, q, fromStart, cache, multiplier, multipliers, popped);
		ans += rProcessVertex(row, col + 2, original, pool, needTotal, q, fromStart, cache, multiplier, multipliers, popped);
		ans += rProcessVertex(row - 2, col, original, pool, needTotal, q, fromStart, cache, multiplier, multipliers, popped);
		ans += rProcessVertex(row - 1, col, original, pool, needTotal, q, fromStart, cache, multiplier, multipliers, popped);
		ans += rProcessVertex(row + 1, col, original, pool, needTotal, q, fromStart, cache, multiplier, multipliers, popped);
		ans += rProcessVertex(row + 2, col, original, pool, needTotal, q, fromStart, cache, multiplier, multipliers, popped);
		
		q.pop();
		++popped;
		++popc;
	}

#ifdef HOME_PC
	cerr << "[reverse] pushc = " << pushc << "; popc = " << popc << endl;
#endif

	return ans;
}

inline int randInt(int n) {
	return (rand() >> 4) % n;
}

bool randomWalk(Pool& pool, const int row, const int col, const int moves) {
	if(pool.isValid(row, col)) {
		pool.add(row, col, 1);
		if(moves == 0) {
			cout << (row + 1) << ' ' << (col + 1) << endl;
		} else {
			while(true) {
				const int dr = randInt(5) - 2;
				const int dc = randInt(5) - 2;

				if(dr * dc == 0 && abs(dr) + abs(dc) != 0 && randomWalk(pool, row + dr, col + dc, moves - 1)) {
					break;
				}
			}
		}
		return true;
	} else {
		return false;
	}
}

void generateTests(const int n) {
	cout << n << endl;
	for(int i = 0; i < n; ++i) {
		int h = randInt(6) + 3;
		int w = randInt(6) + 3;
		cout << endl << h << ' ' << w << endl;
		int fr = randInt(h), fc = randInt(w);
		Pool pool(h, w);
		randomWalk(pool, fr, fc, randInt(11) + 15);
		cout << (fr + 1) << ' ' << (fc + 1) << endl;
		for(int i = 0; i < h; ++i) {
			for(int j = 0; j < w; ++j) {
				cout << pool.get(i, j) << ' ';
			}
			cout << endl;
		}
	}
}

int main()
{
	const int tests = 0;
	if(tests) {
		freopen("c:\\var\\tmp\\test.txt", "w", stdout);
		generateTests(tests);
		return 0;
	}

	//return 0;
	#ifdef HOME_PC
	freopen("c:\\var\\tmp\\in.txt", "r", stdin);
	#endif
	//freopen("OUTPUT.TXT", "w", stdout);

	int t;
	cin >> t;

#ifdef HOME_PC
	clock_t startTime = clock();
#endif

	HashMap<int, int, IdHasher> fromStart;
	HashMap<int, int, IdHasher> cache;
	
	for(int ti = 0; ti < t; ++ti) {
		int h, w;
		cin >> h >> w;
		int sr, sc;
		cin >> sr >> sc; --sr; --sc;
		int fr, fc;
		cin >> fr >> fc; --fr; --fc;

		Pool original(h, w);
		for(int i = 0; i < h; ++i) {
			for(int j = 0; j < w; ++j) {
				int v;
				cin >> v;
				original.add(i, j, v);
			}
		}

		const int willDo = 5;
		if(ti < t - willDo) {
			continue;
		}

		const int totalMoves = original.getTotal() - 1;
		const int leftPart = totalMoves / 2;

		fromStart.clear();
		fillMap(original, leftPart, fromStart, sr, sc);
#ifdef HOME_PC
		cerr << "Map size [1]: " << fromStart.size() << endl;
#endif
		Pool reverse(h, w);
		cache.clear();
		const i64 ans = fromFinish(original, reverse, totalMoves - leftPart, fromStart, fr, fc, cache);
#ifdef HOME_PC
		cerr << "Map size [2]: " << fromStart.size() << endl;
#endif
		cout << ans << endl;
	}
	//throw "";

#ifdef HOME_PC
	cerr << "Elapsed " << (1000 * static_cast<i64>(clock() - startTime) / CLOCKS_PER_SEC) << " ms." << std::endl;
#endif

	return 0;
}
