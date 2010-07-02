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

#pragma comment(linker,"/stack:64000000")

typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef pair<int,int> pii;

/*
class Fenwick1d{
	const int maxN = 1050;
	int a[maxN];
	
	void update(int i,int x)
	{

}
*/
/*
template<int maxN,int neutral> class SegmentTree1d{
	int a[2*maxN+1];



};
*/

const int maxN = 2000000;

int a[maxN];
int f[maxN];

int dims[10];
int parts[10];
int d;
int maxMask;
int indexes1[10];

inline int index(int indexes[]){
	int ret = 0;
	for(int i = 0, j = d-1; i < d; ++i,j--){
		ret+=parts[i]*indexes[j];
	}
	return ret;
}

inline int elem(int a[],int indexes[]){
	for(int i = 0; i < d; ++i)
		if(indexes[i] < 0)
			return 0;
	return a[index(indexes)];
}

inline int sum(int lx[],int rx[]){
	////return f[i2][j2] - f[i1-1][j2] - f[i2][j1-1] + f[i1-1][j1-1];
	//return f[i2][j2][k2] - f[i1-1][j2][k2] - f[i2][j1-1][k2] - f[i2][j2][k1-1]
	//					+ f[i1-1][j1-1][k2] + f[i1-1][j2][k1-1] + f[i2][j1-1][k1-1]
	//					- f[i1-1][j1-1][k1-1];
	int ret = 0;
	for(int i = 0; i < maxMask; ++i){
		int sign = 0;
		for(int j = 0; j < d; j++){
			if(((1<<j)&i)==0)
			{
				indexes1[j] = lx[j] -1;
				sign^=1;
			}
			else
			{
				indexes1[j] = rx[j];
			}
		}
		int b = elem(f,indexes1);
		if(sign) b = -b;
		ret+=b;
	}
	return ret;
							
}

inline int part_sum(int indexes[]){
	////return f[i2][j2] - f[i1-1][j2] - f[i2][j1-1] + f[i1-1][j1-1];
	//return f[i2][j2][k2] - f[i1-1][j2][k2] - f[i2][j1-1][k2] - f[i2][j2][k1-1]
	//					+ f[i1-1][j1-1][k2] + f[i1-1][j2][k1-1] + f[i2][j1-1][k1-1]
	//					- f[i1-1][j1-1][k1-1];
	int ret = elem(a,indexes);
	for(int i = 0; i < maxMask-1; ++i){
		int sign = 1;
		for(int j = 0; j < d; j++){
			if(((1<<j)&i)==0)
			{
				indexes1[j] = indexes[j] -1;
				sign^=1;
			}
			else
			{
				indexes1[j] = indexes[j];
			}
		}
		int a = elem(f,indexes1);
		if(sign) a = -a;
		ret+=a;
	}
	return ret;
							
}

inline void index_split(int i,int indexes[]){
	for(int j = d-1,k = 0; j >=0; --j, ++k){
		indexes[k] = i/parts[j];
		i%=parts[j];
	}
}

int indexes[10];
int main(){
//freopen("in.txt","r",stdin);
freopen("k2.in","r",stdin);
freopen("k2.out","w",stdout);

	scanf("%d",&d);
	maxMask = 1<<d;
	for(int i = 0; i < d; ++i)
		scanf("%d",&dims[i]);

	parts[0] = 1;
	for(int i = 1; i <= d; ++i)
		parts[i]= parts[i-1]*dims[d-i];

	int size = parts[d];
	for(int i = 0; i < size; ++i)
	{
//		index_split(i,indexes);
//		reverse(indexes,indexes+d);
//		scanf("%d",&a[index(indexes)]);
		scanf("%d",&a[i]);
	}


	
	
	memset(f,0,sizeof(f));
	//for(int i = 0; i <= n; ++i)
	//	for(int j = 0; j <=m ; ++j)
	//		for(int k = 0; k <= K; ++k)
	//			//f[i][j] = f[i-1][j] + f[i][j-1] + a[i][j] - f[i-1][j-1];
	//			f[i][j][k] = a[i][j][k] + f[i-1][j][k] + f[i][j-1][k] + f[i][j][k-1]
	//			- f[i-1][j-1][k] - f[i-1][j][k-1] - f[i][j-1][k-1]
	//									+f[i-1][j-1][k-1];

	

	for(int i = 0; i < size; ++i)
	{
		index_split(i,indexes);
		f[i] = part_sum(indexes);
//		cout<<"f(";
//		for(int j = 0; j < d; ++j)
//			cout<<indexes[j]<<",";
//		cout<<") = "<<f[i]<<endl;
	}
	


//	cout<<sum(1,2,1,3,1,5)<<endl;
//	cout<<f[2][3][5]<<endl;

//	cout<<sum(1,1,1,1,1,1)<<endl;
//	cout<<f[1][1][1]<<endl;

//	return 0;
	int q;
	scanf("%d",&q);
	int lx[10];
	int rx[10];
	for(int i = 0; i < q; ++i){
		for(int j = 0; j < d;++j)
		{
			scanf("%d",&lx[j]);
			lx[j]--;
		}
		for(int j = 0; j < d;++j)
		{
			scanf("%d",&rx[j]);
			rx[j]--;
		}
		
		if(i) printf("\n");
		printf("%d",sum(lx,rx));
	}



	return 0;
}