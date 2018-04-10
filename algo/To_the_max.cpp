#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string.h>
using namespace std;

#define N 101
int main()
{
	int a[N][N];
	int b[N];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> a[i][j];
		}
	}
	int max = -32767;
	for (int i = 0; i < n; i++)
	{
		memset(b, 0, sizeof(b));
		for (int j = i; j < n; j++)
		{
			int sum = 0;
			for (int k = 0; k < n; k++)
			{
				b[k] += a[j][k];
				sum += b[k];
				if (sum < b[k])     // sum(k-1)  < 0 ?  b[k] : sum(k)
					sum = b[k];
				if (sum > max)
					max = sum;
			}
		}
	}
	cout << max << endl;
	getchar();
	getchar();
}
