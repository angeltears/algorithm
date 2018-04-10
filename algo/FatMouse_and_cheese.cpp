#include <iostream>
#include <cstdio>
using namespace std;
#define N 101
int n, k;
int grid[N][N];
int d[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
int cheese[N][N];

int memSearch(int x, int y)
{
	int i, j;
	int max = 0;
	if (cheese[x][y] > 0)
		return cheese[x][y];
	for (i = 0; i < 4; i++)
	{
		for (j = 1; j <= k; j++)
		{
			int tx = x + d[i][0] * j;
			int ty = y + d[i][1] * j;
			if (tx >= 0 && tx < n && ty >= 0 && ty < n && grid[x][y] < grid[tx][ty])
			{
				int tmp = memSearch(tx, ty);
				if (max < tmp)
					max = tmp;
			}
		}
	}
	cheese[x][y] = max + grid[x][y];
	return cheese[x][y];
}

int main()
{
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> grid[i][j];
		}
	}
	cout <<memSearch(0, 0);
	getchar();
	getchar();
}
