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


const int seed = 17;

class Treap{
public:
	int key;
	int y;
	int size;
	Treap* left;
	Treap* right;

	Treap(int key){ this->key = key;left = 0; right = 0; y = rand(); size = 1;}
	Treap(int key, Treap* left,Treap* right,int size) {
		this->key = key;
		this->left = left;
		this->right = right;
		this->size = size;
	}

	inline int getLeftSize(){
		if(left == 0)
			return 0;
		return left->size;
	}

	inline int getRightSize(){
		if(right == 0)
			return 0;
		return right->size;
	}

	inline void justify(){
		size = 1 + getLeftSize() + getRightSize();
	}


};




Treap* merge(Treap* L,Treap* R){
	Treap* T;
	if(L == 0)
		return R;
	if(R == 0)
		return L;
	if(R->y < L->y){
		T = L;
		T -> right = merge(T->right,R);
		T->justify();
	}
	else{
		T = R;
		T -> left = merge(L,T->left);
		T->justify();
	}
	return T;
}

void split(Treap* T,Treap** L,Treap** R,int key){
	*L = 0;
	*R = 0;
	if(T == 0)
		return;
	if(T->key < key){
		*L = T;
		split(T->right,&(*L)->right,R,key);
		(*L)->justify();
	}
	else{
		*R = T;
		split(T->left,L,&((*R)->left),key);
		(*R)->justify();
	}

}


Treap* add(Treap* T, int key){
	if(T == 0)
	{
		T = new Treap(key);
		return T;
	}
	Treap* L = 0;
	Treap* R = 0;
	Treap* M = new Treap(key);
	split(T,&L,&R,key);
	T = merge(L,M);
	T = merge(T,R);
	return T;
}

Treap* del(Treap* T,int key){
	Treap* L = 0;
	Treap* MR = 0;
	split(T,&L,&MR,key);
	Treap* R = 0;
	Treap* M = 0;
	split(MR,&M,&R,key+1);
	delete M;
	return merge(L,R);
}

int kth(Treap* T,int k){
	int l = T->getLeftSize();
	int r = T->getRightSize();
	if(k == l+1)
		return T->key;

	if(k <= l)
		return kth(T->left,k);
	else
		return kth(T->right,k-(l+1));
}


int main(){
//freopen("in.txt","r",stdin);
freopen("f2.in","r",stdin);
freopen("f2.out","w",stdout);
	int n;
	scanf("%d",&n);
	srand(seed);
	int com;
	int k;
	Treap* T = 0;
	int size = 0;
	for(int i = 0; i < n; ++i){
		scanf("%d %d",&com,&k);
		if(com>0)
		{
			T = add(T,k);
			++size;
		}
		else if(com < 0)
		{
			T = del(T,k);
			--size;
		}
		else{
			int ans = kth(T,size-k+1);
			printf("%d\n",ans);
		}
	}
	return 0;
}