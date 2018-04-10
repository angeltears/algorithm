#include <iostream>
#include <string>
using namespace std;

#define LEN 98
int main()
{
	string base = "T.T^__^";
	long long int f[LEN];
	f[0] = 7;
	f[1] = 10;
	for (int i = 2; i < LEN; i++)
		f[i] = f[i - 1] + f[i - 2];
	long long int n;
	while (cin >> n)
	{
		while (n > 7)
		{
			int i = 0;
			while (i < LEN && f[i] < n)
				i++;
			n -= f[i - 1];
		}
		cout << base[n - 1] << endl;
	}
}
