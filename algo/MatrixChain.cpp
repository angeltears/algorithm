#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define NUM 51
int p[NUM] = { 50,10,40,30,5,20,15,10 };
int m[NUM][NUM];
int s[NUM][NUM];

void MatrixChain(int n)
{
	for (int i = 0; i <= n; i++)
		m[i][i] = 0;

	// r Ϊ�����ĳ���
	for (int r = 2; r <= n; r++)
	{
		for (int i = 1; i <= n - r + 1; i++)
		{
			int j = i + r - 1;
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			s[i][j] = i;
			for (int k = i + 1; k < j; k++)
			{
				int t  = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if(m[i][j] > t)
				{
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
}


void TracBack(int i, int j)
{
	if (i == j)
		cout << 'A' << i;
	else
	{
		cout << '(';
		TracBack(i, s[i][j]);
		TracBack(s[i][j] + 1, j);
		cout << ')';
	}
}
int main()
{
	MatrixChain(7);
	TracBack(1, 7);
	cout << (int)m[1][7] << endl;
	getchar();
}
