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
typedef pair<i64,int> p6432;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
 
const double pi=2*acos(0.0);
const i64 inf=1LL<<60;

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

const int MAXM = 102400;
const int MAXN = 10;

typedef i64 DISTANCES[MAXM];
typedef pii EDGES[MAXM][MAXN];

DISTANCES distances;

inline void dijkstra(const int n, const int m, const EDGES& edges) {
	std::fill(distances, distances + m, inf);
	distances[0] = 0;

	priority_queue<p6432> queue;
	queue.push(p6432(0, 0));

	int k = 0;
	while(!queue.empty()) {
		const int current = queue.top().second;
		const i64 distance = -queue.top().first;

		queue.pop();

		if(distance == distances[current]) {
			for(const pii* edge = edges[current]; edge != edges[current] + n; ++edge) {
				const int neighbour = edge->first;
				const i64 newDistance = distances[current] + edge->second;

				if(newDistance < distances[neighbour]) {
					distances[neighbour] = newDistance;
					queue.push(p6432(-newDistance, neighbour));
				}
			}
		}
		++k;
		//if(k%10000==0) cout << k << endl;
	}
}
 
int main()
{
#ifdef HOME_PC
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif
	int t;
	cin >> t;

	for(int ti = 0; ti < t; ++ti) {
		int n;
		cin >> n;
		
		vi glasses(n);
		cin >> glasses;

		int m = *std::min_element(glasses.begin(), glasses.end());

		EDGES edges;

		for(int j = 0; j < m; ++j) {
			for(int i = 0; i < n; ++i) {
				edges[j][i] = pii((j + glasses[i]) % m, glasses[i]);
			}
		}

		dijkstra(n, m, edges);

		cout << (*std::max_element(distances, distances + m) - m) << endl;

		int q;
		cin >> q;

		i64 a, b, c;
		cin >> a >> b >> c;
		int can = 0;
		for(i64 i = 0, z = (a + b) % c; i < q; ++i, z = (a + z) % c) {
			if(z >= distances[z % m]) {
				++can;
			}
		}

		cout << (q - can) << ' ' << can << endl;
	}

	return 0;
}
