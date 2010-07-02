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
	//int key;
	int number;
	int y;
	int size;
	Treap* left;
	Treap* right;

	Treap(int number){ left = 0; right = 0; y = rand(); size = 1; this->number = number; }
/*	Treap(int key, Treap* left,Treap* right,int size) {
		this->key = key;
		this->left = left;
		this->right = right;
		this->size = size;
	}
*/
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

void split(Treap* T,Treap** L,Treap** R,int i){
	*L = 0;
	*R = 0;

	if(T == 0)
		return;

	int l = T->getLeftSize();
	int r = T->getRightSize();

	if(l+1 <= i - 1){
		*L = T;
		split(T->right,&(*L)->right,R,i - l - 1);
		(*L)->justify();
	}
	else{
		*R = T;
		split(T->left,L,&(*R)->left,i);
		(*R)->justify();
	}

}


Treap* add(Treap* T, int key){
	if(T == 0)
	{
		T = new Treap(key);
		return T;
	}

	Treap* L = T;
	Treap* R = new Treap(key);
	
	
	T = merge(L, R);
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

//int kth(Treap* T,int k){
//	int l = T->getLeftSize();
//	int r = T->getRightSize();
//	if(k == l+1)
//		return T->key;
//
//	if(k <= l)
//		return kth(T->left,k);
//	else
//		return kth(T->right,k-(l+1));
//}

void print(Treap* T){
	if(T==0) return;
	print(T->left);
	printf("%d ",T->number);
	print(T->right);
}

int main(){
//freopen("in.txt","r",stdin);
freopen("g2.in","r",stdin);
freopen("g2.out","w",stdout);
	srand(seed);
	int com;
	int k;
	Treap* T = 0;
	int size = 0;
	int n,m;
	scanf("%d%d",&n,&m);

	for(int i = 0; i<n; ++i)
	{
		T = add(T, i+1);
	}

	int l,r;
	for(int i = 0; i < m; ++i){
		scanf("%d %d",&l,&r);
		Treap *L=0, *M=0, *R=0;
		
		split(T, &L, &R, r+1);
		split(L, &L, &M, l);

		T = merge(M, merge(L, R));

	}

	print(T);
	return 0;
}