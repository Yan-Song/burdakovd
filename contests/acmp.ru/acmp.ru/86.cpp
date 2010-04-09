#include <iostream> 
int main()
{
	freopen("INPUT.TXT", "r", stdin); freopen("OUTPUT.TXT", "w", stdout);
	int n;
	std::cin >> n;
	std::cout << (n*(n-3)+2);
}
