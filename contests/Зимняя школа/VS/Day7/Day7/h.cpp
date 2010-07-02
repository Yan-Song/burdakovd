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

typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef pair<int,int> pii;
typedef long long i64;
typedef vector<string> VS;

const int inf = 1<<26;
const double eps = 1e-9;

inline i64 sqr(i64 b) { return b*b;}
#pragma comment(linker,"/stack:64000000")

#define adebug2d(a,n,m) for(int i = 0; i < n; ++i,cout<<endl) for(int j = 0; j < m; ++j) cout<<a[i][j]<<" ";


enum {LESS_EQUAL,GREATER_EQUAL,EQUAL,NOT_EQUAL,LESS,GREATER};
char signs[6][5] = {"<=",">=","=","<>","<",">",};
int signum;



int gcd(int a,int b){
	return !b?a:gcd(b,a%b);
}

struct Canonical{
	VI a;
	int signum;

	Canonical(){}
	Canonical(const VI& b,int sign) { a = b; signum = sign; }

	bool independent() const{
		for(int i = 0; i < 10; ++i)
			if(a[i]!=0)
				return false;
		return true;
	}
	bool eval() const{
		int cur = a[10];
		switch(signum){
			case LESS:
				return cur<0;
			case EQUAL:
				return cur==0;
			case NOT_EQUAL:
				return cur!=0;
			case LESS_EQUAL:
				return cur<=0;
		}

		throw 0;
		
	}

	bool operator==(const Canonical& b) const{
		return a == b.a && signum == b.signum;
	}

};

bool contains(const string& s,string what){
	return s.find(what)!=string::npos;
}

bool contains(const string& s,char what){
	return s.find(what)!=string::npos;
}

vector<int> operator- (const VI& a,const VI& b){
	VI ret(a.size());
	for(int i = 0; i < a.size();++i)
		ret[i] = a[i] - b[i];
	return ret;
}


vector<int> operator+ (const VI& a,const VI& b){
	VI ret(a.size());
	for(int i = 0; i < a.size();++i)
		ret[i] = a[i] + b[i];
	return ret;
}

vector<int> operator* (const VI& a,const int b){
	VI ret(a.size());
	for(int i = 0; i < a.size();++i)
		ret[i] = b*a[i];
	return ret;
}


VS split(const string& s,const string& by){
	VS ret;
	int k = s.find(by);
	if(k==-1)
		throw 1;

	ret.push_back(s.substr(0,k));
	ret.push_back(s.substr(k+by.size()));

	return ret;
}

pii parse_pair(const string& s){
	if(contains(s,'*')){
		VS a = split(s,"*");
		if(a[0][0] == 'X')
			swap(a[0],a[1]);

		int Xnum = a[1][1]-'0';
		int coef;
		sscanf(a[0].c_str(),"%d",&coef);
		return pii(coef,Xnum);
	}
	else{
		if(s[0] == 'X'){
			int Xnum = s[1] -'0';
			return pii(1,Xnum);
		}
		else{
			int Xnum = 10;
			int coef;
			sscanf(s.c_str(),"%d",&coef);
			return pii(coef,Xnum);
		}

	}
	return pii();
}


VI f(const string& s){
	VI ret(11,0);
	
	int l = 0;
	for(int i = 1; i < s.size(); ++i){
		if(s[i] == '+' || s[i] == '-'){
			pii coef = parse_pair(s.substr(l+1,i-l-1));
			if(s[l] == '-')
				coef.first*=-1;
			ret[coef.second] += coef.first;
			l = i;
		}
	}
	
	return ret;
}


string add_sign(string s){
	s+="+";
	if(s[0]!='-')
		return "+"+s;
	return s;
}

Canonical canonical(const string& s)
{
	for(int i = 0; i < 6; ++i)
	{
		if(contains(s,string(signs[i]))){			
			
			VS b =  split(s,signs[i]);	
			string left = b[0], right = b[1];
			
			VI coefsLeft = f(add_sign(left));
			VI coefsRight = f(add_sign(right));
			

			VI coefs = coefsLeft - coefsRight;
			
			int sign = i;

			if(sign == GREATER_EQUAL || sign == GREATER ){
				coefs = coefs*(-1);
				sign = sign^1;
			}
				

			int d = abs(coefs[0]);
			for(int i = 1 ; i < coefs.size(); ++i)
				d = gcd(abs(d),abs(coefs[i]));

		
			if(d>0)	
				for(int i = 0 ; i < coefs.size(); ++i)
					coefs[i]/=d;

			if(sign == EQUAL || sign == NOT_EQUAL){
				int sgn = -2;
				for(int i = 0; i <= 10;++i){
					if(sgn==-2 && coefs[i]!=0){
						if(coefs[i]<0)
							sgn = -1;
						else
							sgn = 1;
					}
					
					coefs[i]*=sgn;
				}
			}

			return Canonical(coefs,sign);
		}
	}

	throw 0;
	return Canonical();
}

bool equals(const Canonical& a,const Canonical& b){
	bool ind1 = a.independent();
	bool ind2 = b.independent();

	if(ind1 || ind2)
		return ind1 && ind2 && ( a.eval() == b.eval());

	return a == b;
}


int main(){
//freopen("in.txt","r",stdin);
freopen("h.in","r",stdin);
freopen("h.out","w",stdout);
	string s1,s2;
	cin>>s1>>s2;
	
	Canonical first = canonical(s1);
	Canonical second = canonical(s2);
	
	if(equals(first,second))
		printf("YES");
	else
		printf("NO");
	
	
	return 0;
}