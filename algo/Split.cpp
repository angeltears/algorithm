#include<iostream>
using namespace std;

int slipt(int n, int m)
{
	if (n == 1 || m == 1)
		return 1;
	else if (n < m)
		return slipt(n, n);
	else if (n == m)
		return slipt(n, n - 1) + 1;
	else
		return slipt(n, m - 1) + slipt(n - m, m);
}

int main()
{
	cout << slipt(6, 4) << endl;
	return 0;
}
