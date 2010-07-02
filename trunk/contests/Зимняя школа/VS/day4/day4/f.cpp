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

const int inf = 1<<26;
const double eps = 1e-9;

#define sqr(x) ((x)*(x))
//#pragma comment(linker,"/stack:256000000")

const int maxN = 111000;
char s[2*maxN];



struct Node{
	int next[26];
	bool m_bEmpty;
	int nim;
	Node() {
		memset(next,-1,sizeof(next));
		m_bEmpty = true;
	}
	inline bool empty() { return m_bEmpty; }

	inline bool existsNext(char c) { return next[c-'A'] != -1; }
	inline void setNext(char c,int val) { next[c-'A'] = val; m_bEmpty = false; }
	inline void setNim(int val) { nim = val; }
	inline int nimValue() { return nim; }

};

struct Bor{

	Node nodes[maxN];
	int root;
	int size;


	Bor() {  root = 0; size = 1; }

	void add(char s[]){
		int len = strlen(s);
		//cout<<len<<endl;
		int cur = root;
		for(int i = 0; i < len; ++i){
			if(nodes[cur].existsNext(s[i]))
				cur = nodes[cur].next[s[i]-'A'];
			else
			{
				nodes[cur].setNext(s[i],size);
				cur = size;
				++size;
			}
		}

	}

	int countNim(){

		VI v;
		int cur_nim;
		int next;
		for(int i = size-1;i>=0;--i){
			if(nodes[i].empty())
				nodes[i].setNim(0);
			else{
				v.clear();
				for(int j = 0; j < 26;++j){
					int next = nodes[i].next[j];
					if(next!=-1)
						v.push_back(nodes[next].nimValue());
				}
				sort(v.begin(),v.end());
				cur_nim = -1;
				for(int j = 0; j < v.size();++j){
					if(v[j]!=j)
					{
						cur_nim = j;
						break;
					}
				}

				if(cur_nim == -1)
					cur_nim = v.size();

				nodes[i].setNim(cur_nim);
			}
		}


		return nodes[root].nimValue();
	}

	//int countNim(int t){
	//	if(cur == -1) 
	//		return -1;
	//	if(nodes[cur].empty()){
	//		nodes[cur].setNim(0);
	//		return 0;
	//	}
	//	int cur_nim; 

	//	VI v;


	//	return cur_nim;
	//}
	char winningMove(){
		for(int i = 0;i < 26;++i)
			if(nodes[root].next[i]!=-1 && nodes[nodes[root].next[i]].nimValue() == 0)
				return i+'A';
		return -1;
	}
};


Bor B;



int main(){
	//freopen("in.txt","r",stdin);
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);

	int n;
	scanf("%d",&n);
	for(int i = 0; i <n ; ++i)
	{
		scanf("%s",s);
		B.add(s);
	}
	int result = B.countNim();
	if(result == 0)
		printf("Second");
	else
		printf("First %c",B.winningMove());

//	for(;;);

	return 0;
}