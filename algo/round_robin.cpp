#include <iostream>
#include <algorithm>

using std::cout;
using std::cin;
#define MAX 100
int a[MAX][MAX];

void copy(int tox, int toy, int fromx, int fromy, int r)
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			a[tox + i][toy + j] = a[fromx + i][fromy + j];
		}
	}
}

void Table(int k)
{
	int r, i;
	int n = 1 << k;

	for (int i = 0; i < n; i++)
	{
		a[0][i] = i + 1;
	}

	for (r = 1; r < n; r <<= 1)
	{
		for (i = 0; i < n; i += 2 * r)
		{
			copy(r, r + i, 0, i, r);
			copy(r, i, 0, r + i, r);
		}
	}
}

int main()
{
	int k;
	cin >> k;
	Table(k);
	for (int i = 0; i < 1 << k; i++)
	{
		for (int j = 0; j < 1 << k; j++)
		{
			cout << a[i][j]<< " ";
		}
		cout << std::endl;
	}
	getchar();
	getchar();
}
