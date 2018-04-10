#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define NUM  100
int c[NUM][NUM];
int b[NUM][NUM];


void LcsLength(int m, int n, const char x[], char y[])
{
	for (int i = 0; i <= m; i++)
		c[i][0] = 0;
	for (int j = 0; j <= n; j++)
		c[0][j] = 0;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (x[i] == y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1;
			}
			else if (c[i][j - 1] >= c[i - 1][j])
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = 3;
			}
			else
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = 2;
			}
		}
	}
}


void LCS(int i, int j, char x[])
{
	if (i == 0 || j == 0)
	{
		return;
	}
	if (b[i][j] == 1)
	{
		LCS(i - 1, j - 1, x);
		cout << x[i];
	}
	else if (b[i][j] == 3)
	{
		LCS(i, j - 1, x);
	}
	else
	{
		LCS(i - 1, j, x);
	}
}

int main()
{
	char x[] = { '0','A','B','C','D','A','B'};
	char y[] = { '0','B','D','C','A','B','A' };
	LcsLength(6, 6, x, y);
	cout << c[6][6] << endl;
	LCS(6, 6, x);
	return 0;
}
