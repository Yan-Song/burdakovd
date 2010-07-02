	#include <iostream>
	#include <cstdio>
	#include <cmath>
	#include <algorithm>
	#include <cstdlib>
	#include <vector>
	#include <string>
	#include <queue>
	#include <stack>

int gcd(int a,int b){
	return !b? a : gcd(b,a%b);
}

	int main(){
		for(int k = 1; k < 100; ++k)
		{
			int r = 1;
			bool b = true;
			for(int j = 1; j < k; ++j)
			{
				if(gcd(j,k) == 1)
				{
					b = b&& ( j*j % k == 1);
					r = r*j % k;

				}

			}
			r%=k;

			if(r!=k-1 && !(r==1 && b))
				printf("m = %d , r = %d\n",k,r);
		}
		return 0;
	}