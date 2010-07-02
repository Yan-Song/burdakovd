#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <map>


using namespace std;

typedef int ololo;
typedef long long i64;
#define int i64

typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef pair<int,int> pii;




const int inf = 1<<26;
const double eps = 1e-9;

#define sqr(x) ((x)*(x))
#pragma comment(linker,"/stack:64000000")

vector<string> a;



int n;
const int mod1 = 712677127;
const int mod2 = 1000000007;

struct Hash{
	int Nstring;
	int pos;

	pii values;

	Hash(){}
	Hash(const pii& values,int Nstring,int pos){
		this->values = values;
		this->pos = pos;
		this->Nstring = Nstring;
	}

	bool equals(const Hash& H) const{
		return values == H.values;
	}

	bool operator<(const Hash& H) const{
		return make_pair(values,pii(Nstring,pos)) < make_pair(H.values,pii(H.Nstring,H.pos));
	}

};

template <int modulo> 
struct HashComputer{
	static void Init() {
		seedDegs.resize(maxN);
		seedDegs[0] = 1;
		for(int i = 1; i < maxN; ++i){
			seedDegs[i] = (i64)seed*seedDegs[i-1];
			seedDegs[i]%=modulo;
		}
	}

	const static int maxN = 101000;
	static VI seedDegs;
	const static int seed = 151;
	i64 value;

	HashComputer() { value = 0; }
	
	void add(char c){
		value*=seed;
		value+=c;
		value%=modulo;
	}

	void shift(char prev,char cur,int len){
		value = (value - (i64)seedDegs[len-1]*prev)*seed + cur;
		value = (value%modulo + modulo)%modulo;
	}


};

template<>
VI HashComputer<mod1>::seedDegs = VI();
template<>
VI HashComputer<mod2>::seedDegs = VI();



struct EqualString{
	bool operator()(const Hash& H1,const Hash& H2) const{
		return H1.Nstring == H2.Nstring && H2.equals(H1);
	}
};

bool can(int prefLength,VI& result,bool return_result = false){
	result.clear();

	vector<Hash> hashes;
	for(int sn = 0; sn<n;++sn){
		HashComputer<mod1> curHash1;
		HashComputer<mod2> curHash2;

		for(int i = 0; i < prefLength; ++i){
			curHash1.add(a[sn][i]);
			curHash2.add(a[sn][i]);
		}
		hashes.push_back(Hash(make_pair(curHash1.value,curHash2.value),sn,0));

		for(int i = prefLength; i < a[sn].size(); ++i){
			curHash1.shift(a[sn][i-prefLength],a[sn][i],prefLength);
			curHash2.shift(a[sn][i-prefLength],a[sn][i],prefLength);
			hashes.push_back(Hash(make_pair(curHash1.value,curHash2.value),sn,i-prefLength+1));
		}
	}

	sort(hashes.begin(),hashes.end());

	hashes.resize(unique(hashes.begin(),hashes.end(),EqualString())-hashes.begin());

	
	VVI results;
	for(int i = n-1; i < hashes.size();++i)
		if(hashes[i].equals(hashes[i-n+1])){
			if(return_result == true){
				results.push_back(VI());
				int k = results.size()-1;
				for(int j = i-n+1; j <=i;++j)
					results[k].push_back(hashes[j].pos);
			}
			else
				return true;
		}

	if(return_result == true){
		result = *min_element(results.begin(),results.end());
		return true;
	}

	return false;
}

ololo main(){
//	freopen("in.txt","r",stdin);
	freopen("b4.in","r",stdin);
	freopen("b4.out","w",stdout);
	HashComputer<mod1>::Init();
	HashComputer<mod2>::Init();
  
	cin>>n;
	a.resize(n);
	int left = 0, right = inf;
	for(int i = 0; i < n; ++i)
	{
		cin>>a[i];
		right = min(right,(int)a[i].length());
	}


	VI result;
	while(left<right){
		int mid = (left+right+1)/2;
		if(can(mid,result))
			left = mid;
		else
			right = mid-1;
	}
	can(left,result,true);

	printf("%d\n",left);
	if(!result.empty()){
		for(int i = 0 ; i < result.size();++i)
			printf("%d\n",result[i]);
	}





	return 0;
}