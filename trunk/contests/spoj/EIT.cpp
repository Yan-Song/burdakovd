#include <iostream>
#include <stdio.h>
#include <stdlib.h>


unsigned char buffer[26000000];

int main()
{
	int n, k, t, ans = 0;

	scanf("%d %d\n", &n, &k);
	register unsigned char* p = buffer;
	register unsigned char c;

	std::cin.read((char *)buffer, 25000000);
	buffer[std::cin.gcount()] = 0;

	bool digit[256];
	bool nondigit[256];

	for(int i = 0; i < 256; ++i)
	{
		digit[i] = (i >= '0') && (i <= '9');
		nondigit[i] = ((i < '0') || (i > '9')) && (i != 0);
	}

	while(n--)
	{
		t = 0;

		for(; digit[c = *(p++)]; t = t * 10 + c - '0');

		for(; nondigit[*p]; ++p);
 
		//std::cerr << "t = " << t << std::endl;
		if(!(t % k))
		{
			++ans;
		}
	}

	printf("%d\n", ans);

	return 0;
}
