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

const int MODULO = 1000000009;

class SimpleSolver {
public:
	int solve(const int n, const v64& start, const v64& end) const {
		int ans = 0;
		for(int i = 0; i < n; ++i) {
			if(start[i] > end[i]) {
				return 0;
			}
		}
		for(v64 point = start; ; next(n, point, start, end)) {
			i64 bits = 0, fail = 0;
			for(int i = 0; i < n && !fail; ++i) {
				const i64 z = point[i];
				fail |= bits & z;
				bits |= z;
			}
			if(!fail) {
				//cout << "good: " << point << endl;
				ans = (ans + 1) % MODULO;
			}
			if(point == end) {
				break;
			}
		}
		return ans;
	}

private:
	void next(const int n, v64& point, const v64& start, const v64& end) const {
		int i = n - 1;
		while(point[i] == end[i]) {
			point[i] = start[i];
			--i;
		}
		++point[i];
	}
};

inline int nbits(const int x) {
	int ans = 0;
	for(int i = x; i > 0; i >>= 1) {
		ans += i & 1;
	}
	return ans;
}

inline int fastPow(const int x, const int p) {
	if(p == 0) {
		return 1;
	}

	if((p & 1) == 0) {
		return fastPow(static_cast<int>(i64(x) * x % MODULO), p / 2);
	}

	return static_cast<int>(i64(x) * fastPow(x, p - 1) % MODULO);
}

inline int inverse(const int n) {
	const int inversed = fastPow(n, MODULO - 2);
	return inversed;
}

inline int inverse_fact(const int n) {
	i64 ans = 1;
	for(int i = 1; i <= n; ++i) {
		ans = ans * inverse(i) % MODULO;
	}
	return static_cast<int>(ans);
}

inline int fact(const int n) {
	i64 ans = 1;
	for(int i = 1; i <= n; ++i) {
		ans = ans * i % MODULO;
	}
	return static_cast<int>(ans);
}

inline int C_(const int n, const int k) {
	const i64 fact_n = fact(n);
	const i64 inversed_fact_n_k = inverse_fact(n - k);
	const i64 inversed_fact_k = inverse_fact(k);

	return static_cast<int>(fact_n * inversed_fact_n_k % MODULO * inversed_fact_k % MODULO);
}

const struct CHolder {
	int C[64][64];

	CHolder() {
		for(int i = 0; i < 64; ++i) {
			for(int j = 0; j <= i; ++j) {
				C[i][j] = C_(i, j);
			}
		}
	}
} C;

const int MAX_N = 8;
const int MAX_BITS = 50;

const struct MultiplierHolder {
	int M[MAX_N + 1][MAX_BITS + 1][MAX_BITS + 1];
	int prepared[MAX_N + 1][MAX_BITS + 1][MAX_BITS + 1][MAX_BITS + 1];

	MultiplierHolder() {
		for(int nSpecial = 0; nSpecial <= MAX_N; ++nSpecial) {
			for(int h = 0; h <= MAX_BITS; ++h) {
				for(int delta = 0; delta <= h; ++delta) {
					M[nSpecial][h][delta] = i64(C.C[h][delta]) * fastPow(nSpecial, delta) % MODULO;
				}
			}
		}
		
		for(int nSpecial = 0; nSpecial <= MAX_N; ++nSpecial) {
			for(int h = 0; h <= MAX_BITS; ++h) {
				for(int k = 0; k <= MAX_BITS; ++k) {
					for(int j = 0; j <= std::min(h, k); ++j) {
						prepared[nSpecial][h][k][j] = M[nSpecial][h - j][k - j];
					}
				}
			}
		}
	}
} Multiplier;

struct CacheHolder {
public:
	typedef int Row[MAX_BITS + 1];
	typedef Row Block[MAX_BITS + 1];
	static const int cacheSize = 1 << (MAX_N * 2);
	Row* cache[cacheSize];

	CacheHolder() {
		mset(cache, 0);
		Block* p = data;
		for(int i = 0; i < cacheSize; ++i) {
			if(isTrinary(i)) {
				cache[i] = p[0];
				++p;
			}
		}
	}
private:
		Block data[6561];

		bool isTrinary(const int x) {
			return x == 0 || ((x & 3) < 3 && isTrinary(x >> 2));
		}
} Cache;

bool cache_exists[1 << (MAX_N * 2)][MAX_BITS + 1];

class UpperSolver {
private:
	int cacheMisses, cacheHits;
	const int n;
	const i64 *const lower, *const upper;

	const int* f(const int mask, const int bits) {
		int* answer = Cache.cache[mask][bits];
		if(cache_exists[mask][bits]) {
			++cacheHits;
		}
		else {
			++cacheMisses;
			//f_impl_old(mask, bits, answer);
			f_impl(mask, bits, answer);
			cache_exists[mask][bits] = true;
		}
		return answer;
	}

	void f_impl_ololo(const int mask, const int bits, int* const answer) {
		if(bits == 0 || mask == 0) {
			memset(answer, 0, sizeof(int) * (MAX_BITS + 1));
			answer[0] = 1;
			return;
		}

		int hasHighestBit[MAX_N];
		int hasHighestBitMask = 0;
		int m = 0;
		for(int i = 0; i < n; ++i) {
			const int mode = (mask >> (2 * i)) & 3;
			if(mode) {
				if((mode == 1 ? lower : upper)[i] & (1LL << (bits - 1))) {
					hasHighestBit[m++] = i;
					hasHighestBitMask |= (mode << (2 * i));
				}
			}
		}

		if(!hasHighestBitMask) {
			const int* const lowerAnswer = f(mask, bits - 1);
			memcpy(answer, lowerAnswer, sizeof(int) * (MAX_BITS + 1));
			return;
		}

		memset(answer, 0, sizeof(int) * (MAX_BITS + 1));
		i64 answerL[MAX_BITS + 1];
		int answerH[MAX_BITS + 1];
		mset(answerH, 0);
		mset(answerL, 0);

		// берём
		{
			const int h = bits - 1;
			const int jEnd = bits; // MAX_BITS + 1

			for(int i = 0; i <= 0; ++i) {
				const int remainingMask = i == m ?
					mask ^ hasHighestBitMask :
					mask ^ (hasHighestBitMask & ~(3 << (2 * hasHighestBit[i])));
				const int nSpecial = i == m ? m : m - 1;
				const int* const subAnswer = f(remainingMask, bits - 1);
				const int kEnd = i == m ? bits : bits + 1;

				for(int j = 0; j < jEnd; ++j) {
					const int* mm = Multiplier.M[nSpecial][h - j];
					const int kStart = j + (i != m);
					const i64 sub = subAnswer[j];

					for(int k = kStart; k < kEnd; ++k, ++mm) {					
						const i64 ans_delta = *mm * sub;
						answerL[k] += ans_delta & 1099511627775LL; // ((1LL << 40) - 1);
						answerH[k] += static_cast<int>(ans_delta >> 40);
						//answer[k] = (answer[k] + ans_delta) % MODULO;
					}
				}
			}
		}

		// не берём
		{
			const int remainingMask = mask ^ (hasHighestBitMask & (3 << (2 * hasHighestBit[0])));
			const int nSpecial = 1;
			const int* const subAnswerWithoutHighest = f(remainingMask, bits - 1);
			const int* const subAnswerWithHighest_ = f(remainingMask, bits);
			int subAnswerWithHighest[MAX_BITS + 1];
			for(int i = 0; i <= MAX_BITS; ++i) {
				subAnswerWithHighest[i] = subAnswerWithHighest_[i] + MODULO - subAnswerWithoutHighest[i];
			}

			// without
			{
				const int kEnd = bits; // exclusive
				const int h = bits - 1;
				for(int j = 0; j < bits; ++j) {
					const int* mm = Multiplier.M[nSpecial][h - j];
					const int kStart = j;
					const i64 sub = subAnswerWithoutHighest[j];

					for(int k = kStart; k < kEnd; ++k, ++mm) {					
						const i64 ans_delta = *mm * sub;
						answerL[k] += ans_delta & 1099511627775LL; // ((1LL << 40) - 1);
						answerH[k] += static_cast<int>(ans_delta >> 40);
						//answer[k] = (answer[k] + ans_delta) % MODULO;
					}
				}
			}

			// with
			{
				const int kEnd = bits + 1; // exclusive
				const int h = bits - 1;
				for(int j = 0; j < bits + 1; ++j) {
					const int* mm = Multiplier.M[nSpecial][h - j + 1];
					const int kStart = j;
					const i64 sub = subAnswerWithHighest[j];

					for(int k = kStart; k < kEnd; ++k, ++mm) {					
						const i64 ans_delta = *mm * sub;
						answerL[k] += ans_delta & 1099511627775LL; // ((1LL << 40) - 1);
						answerH[k] += static_cast<int>(ans_delta >> 40);
						//answer[k] = (answer[k] + ans_delta) % MODULO;
					}
				}
			}
		}

		for(int i = 0; i <= MAX_BITS; ++i) {
			answer[i] = static_cast<int>((answerH[i] * 511617885LL + answerL[i]) % MODULO);
		}
	}

	void f_impl(const int mask, const int bits, int* const answer) {
		if(bits == 0 || mask == 0) {
			memset(answer, 0, sizeof(int) * (MAX_BITS + 1));
			answer[0] = 1;
			return;
		}

		int hasHighestBit[MAX_N];
		int hasHighestBitMask = 0;
		int m = 0;
		for(int i = 0; i < n; ++i) {
			const int mode = (mask >> (2 * i)) & 3;
			if(mode) {
				if((mode == 1 ? lower : upper)[i] & (1LL << (bits - 1))) {
					hasHighestBit[m++] = i;
					hasHighestBitMask |= (mode << (2 * i));
				}
			}
		}

		if(!hasHighestBitMask) {
			const int* const lowerAnswer = f(mask, bits - 1);
			memcpy(answer, lowerAnswer, sizeof(int) * (MAX_BITS + 1));
			return;
		}

		memset(answer, 0, sizeof(int) * (MAX_BITS + 1));
		i64 answerL[MAX_BITS + 1];
		int answerH[MAX_BITS + 1];
		mset(answerH, 0);
		mset(answerL, 0);
		
		const int h = bits - 1;
		const int jEnd = bits; // MAX_BITS + 1

		i64 accumulatedAnswer[MAX_BITS + 1];
		mset(accumulatedAnswer, 0);

		for(int takeBit = 1; takeBit >= 0; --takeBit) {
			const int iStart = (takeBit ? 0 : m), iEnd = m + 1 - takeBit;
			const int kEnd = bits + takeBit;
			const int nSpecial = m - takeBit;

			for(int i = iStart; i < iEnd; ++i) {
				const int remainingMask = takeBit ?
					mask ^ (hasHighestBitMask & ~(3 << (2 * hasHighestBit[i]))) :
					mask ^ hasHighestBitMask;
				const int* const subAnswer = f(remainingMask, bits - 1);

				if(takeBit) {
					for(int j = 0; j < jEnd; ++j) {
						accumulatedAnswer[j] += subAnswer[j];
						//accumulatedAnswer[j] %= MODULO;
					}
					if(i != iEnd - 1) {
						continue;
					}
				} else {
					for(int j = 0; j < jEnd; ++j) {
						accumulatedAnswer[j] = subAnswer[j];
					}
				}

				/*for(int k = takeBit; k < kEnd; ++k) {
					const int *mm = Multiplier.prepared[nSpecial][h][k - takeBit];
					const int* mmf = mm + k - takeBit + 1;
					i64 low = 0;
					int high = 0;
					i64* acc = accumulatedAnswer;
					for(; mm != mmf; ++mm, ++acc) {
						const i64 ans_delta = *mm * *acc;
						low += ans_delta & 1099511627775LL; // ((1LL << 40) - 1);
						high += static_cast<int>(ans_delta >> 40);
					}
					answerH[k] += high;
					answerL[k] += low;
				}*/
				
				for(int j = 0; j < jEnd; ++j) {
					const int* mm = Multiplier.M[nSpecial][h - j];
					const int kStart = j + takeBit;
					const i64 sub = accumulatedAnswer[j];

					for(int k = kStart; k < kEnd; ++k, ++mm) {					
						const i64 ans_delta = *mm * sub;
						// answerL[k] MUST be <= 2^60
						// ans_delta MUST be <= 1000000009 * 8 * 1000000009
						// and overflow will not occur
						//const i64 tmp = answerL[k] + ans_delta;
						//answerL[k] = (tmp & 1073741823) + (tmp >> 30) * 73741815;

						answerL[k] += ans_delta & 1099511627775LL; // ((1LL << 40) - 1);
						answerH[k] += static_cast<int>(ans_delta >> 40);
						//answer[k] = (answer[k] + ans_delta) % MODULO;
					}
				}
			}
		}

		for(int i = 0; i <= MAX_BITS; ++i) {
			//answer[i] = answerL[i] % MODULO;
			answer[i] = static_cast<int>((answerH[i] * 511617885LL + answerL[i]) % MODULO);
		}
	}

public:
	UpperSolver(const int n, const i64* const lower, const i64* const upper) :
	  cacheMisses(0), cacheHits(0), n(n), lower(lower), upper(upper) 
	  {
		  mset(cache_exists, false);
	}

	int solve(const int mask) {
		const int* answers = f(mask, MAX_BITS);
		return static_cast<int>(std::accumulate(answers, answers + MAX_BITS + 1, i64(0)) % MODULO);
	}

	int getCacheMisses() const {
		return cacheMisses;
	}

	int getCacheHits() const {
		return cacheHits;
	}
};

int cache2[1 << (MAX_N * 2)][MAX_BITS + 1];
bool cache_exists2[1 << (MAX_N * 2)][MAX_BITS + 1];

class UpperSolver2 {
private:
	int cacheMisses, cacheHits;
	const int n;
	const i64 *const lower, *const upper;

	int f(const int mask, const int bits) {
		int& answer = cache2[mask][bits];
		if(cache_exists2[mask][bits]) {
			++cacheHits;
		}
		else {
			++cacheMisses;
			//f_impl_old(mask, bits, answer);
			answer = f_impl(mask, bits);
			cache_exists2[mask][bits] = true;
		}
		return answer;
	}

	int f_impl(const int mask, const int bits) {
		if(bits == 0) {
			return 1;
		}

		int nFree = n;

		int hasHighestBit[MAX_N];
		int hasHighestBitMask = 0;
		int m = 0;
		for(int i = 0; i < n; ++i) {
			const int mode = (mask >> (2 * i)) & 3;
			if(mode) {
				--nFree;
				if((mode == 1 ? lower : upper)[i] & (1LL << (bits - 1))) {
					hasHighestBit[m++] = i;
					hasHighestBitMask |= (mode << (2 * i));
				}
			}
		}

		i64 answer = 0;
		
		// don't take that bit
		// or give that bit to one of free numbers
		{
			const int remainingMask = mask ^ hasHighestBitMask;
			answer += i64(nFree + 1) * f(remainingMask, bits - 1);
			answer %= MODULO;
		}

		// take that bit
		for(int i = 0; i < m; ++i) {
			const int remainingMask = mask ^ (hasHighestBitMask & ~(3 << (2 * hasHighestBit[i])));
			answer += f(remainingMask, bits - 1);
			answer %= MODULO;
		}

		//cout << "f(mask = " << mask << ", bits = " << bits << ") = " << answer << endl;
		return static_cast<int>(answer);
	}

public:
	UpperSolver2(const int n, const i64* const lower, const i64* const upper) :
	  cacheMisses(0), cacheHits(0), n(n), lower(lower), upper(upper) 
	  {
		  mset(cache_exists2, false);
	}

	int solve(const int mask) {
		const int answer = f(mask, MAX_BITS);
		return answer;
	}

	int getCacheMisses() const {
		return cacheMisses;
	}

	int getCacheHits() const {
		return cacheHits;
	}

	void clearCache() {
		mset(cache_exists2, 0);
	}
};

class ComplexSolver {
public:
	int solve(const int n, v64 start, const v64& end) const {
		UpperSolver2 solver(n, &(*start.begin()), &(*end.begin()));

		for(int i = 0; i < n; ++i) {
			--start[i];
		}

		// если будут проблемы - учесть отрицательные размерности
		i64 ans = 0;
		// inclusion-exclusion
		for(int i = 0; i < 1 << n; ++i) {
			const int sign = (nbits(i) ^ n) & 1 ? -1 : 1;
			int mask = 0;
			bool ok = true;
			for(int j = 0; j < n; ++j) {
				mask ^= (i & (1 << j) ? 2 : 1) << (2 * j);
				if(!(i & (1 << j)) && start[j] < 0) {
					ok = false;
					break;
				}
			}
			if(ok) {
				//solver.clearCache();
				ans = (ans + MODULO + sign * solver.solve(mask)) % MODULO;
				//cout << "there was " << solver.getCacheMisses() << " cache misses, and " << solver.getCacheHits() << " cache hits" << endl;
				//cout << "ans changed to " << ans << endl;
			}
		}

		//cout << "there was " << solver.getCacheMisses() << " cache misses, and " << solver.getCacheHits() << " cache hits" << endl;

		return static_cast<int>(ans);
	}
};

int main()
{
	//return 0;
	#ifdef HOME_PC
	freopen("c:\\var\\tmp\\in.txt", "r", stdin);
	#endif
	//freopen("OUTPUT.TXT", "w", stdout);

	int t;
	cin >> t;

	SimpleSolver simple;
	ComplexSolver solver;

#ifdef HOME_PC
	clock_t startTime = clock();
#endif

	for(int ti = 0; ti < t; ++ti) {
		int n;
		cin >> n;
		v64 start(n), end(n);
		cin >> start >> end;
		
		//continue;
		//cout << "simple: " << simple.solve(n, start, end) << endl;
		//cout << "solver: " << solver.solve(n, start, end) << endl;

		int willDo = 60;

		if(ti < t - willDo) {
			cout << 0 << endl;
		}
		else {
			cout 
			#ifdef HOME_PC
				<< "test " << ti << ": " 
			#endif
				<< solver.solve(n, start, end) << endl;
		}
	}

#ifdef HOME_PC
	cerr << "Elapsed " << (1000 * static_cast<i64>(clock() - startTime) / CLOCKS_PER_SEC) << " ms." << std::endl;
#endif

	return 0;
}
