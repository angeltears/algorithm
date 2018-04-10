#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

#define NUM 50
#define CAP 1500
int w[NUM] = {2,2,6,4,5};        //��Ʒ������
int v[NUM] = {6,3,5,4,6};        //��Ʒ�ļ۸�
int p[NUM][CAP];

//cΪ������������ n����Ʒ������
void knapsack(int c, int n)
{
	int Jmax = min(w[n] - 1, c);
	for (int j = 0; j <= Jmax; j++)
		p[n][j] = 0;
	for (int j = w[n]; j <= c; j++)
		p[n][j] = v[n];
	for (int i = n - 1; i > 1; i--)
	{
		Jmax = min(w[n] - 1, c);
		for (int j = 0; j <= Jmax; j++)
			p[i][j] = p[i + 1][j];
		for (int j = w[i]; j <= c; j++)
		{
			p[i][j] = max(p[i + 1][j], p[i + 1][j - w[i]] + v[i]);
		}
	}
	p[1][c] = p[2][c];
	if (c >= w[1])
		p[1][c] = max(p[1][c], p[2][c - w[1]] + v[1]);
}

void traceback(int c, int n, int x[])
{
	for (int i = 1; i < n; i++)
	{
		if (p[i][c] == p[i + 1][c])
			x[i] = 0;
		else
		{
			x[i] = 1;
			c = x[i];
		}
	}
	x[n] = (p[n][c]) ? 1 : 0;
	for (int i = 1; i <= n; i++)
		cout << x[i] << " ";
	cout << endl;
}

int dp[NUM];
void solov(int n, int wg)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = wg; j >= w[i]; j--)
		{
			if (dp[j-w[i]] + v[i] > dp[j])
				dp[j] = dp[j - w[i]] + v[i];
		}
	}
	cout << dp[wg] << endl;
}

int dps[NUM][NUM];
void solovs(int n, int wg)
{
	int i;
	for ( i= 0; i < n; i++)
	{
		for (int j = wg; j >= w[i]; j--)
		{
			if (dps[i][j - w[i]] + v[i] > dps[i][j])
				dps[i + 1][j] = dps[i][j - w[i]] + v[i];
		}
	}
	cout << dps[i][wg] << endl;
}
int main()
{
	int a[5];
	knapsack(10,5);
	traceback(10, 5, a);
	solov(5, 20);
	solovs(5, 20);
	cout << p[1][5] << endl;
	getchar();
}
