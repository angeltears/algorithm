#include <iostream>
#include <string.h>
using std::cout;
using std::cin;
using std::endl;
int a[1001];
int comp(int n)
{
	int ans = 1;
	for (int i = 1; i <= n / 2; i++)
		ans += comp(i);
	a[n] = ans;
	return ans;
}

int main()
{
	int n;
	while (cin >> n)
	{
		memset(a, 0, sizeof(a));
		a[1] = 1;
		cout << comp(n) << endl;
	}
}

/*
		6                                        8
	1   2    3                           1     2      3     4
	1   1    1                           1     1      1    1   2
	                                                           1
*/
