#include <cstdio>
#include <cstdlib>
#include <string>
#include <set>

#define R std::string

char D[99], *Q, *W;
int N, l = 1;

int S(int p) {

	std::set<R> s;

	for(W = D; W++ < D + p; )
		for(Q = D; Q < W; )
			s.insert(R(Q++, W));

	int z = N - s.size();

	for(D[p] = 96; p < l & ++D[p] < '{' & l * l - p * p >= z + z - l + p; S(p + 1));

	if(!z)

		D[l] = 0, printf(D), exit(0);
}

int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);

	for(scanf("%d", &N); ; ++l)
		S(0);
}
