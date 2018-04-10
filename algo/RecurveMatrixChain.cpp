#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define Num 15
int p[Num] = { 50,10,40,30,5,20,15,10 };
int a[Num][Num] = { 0 };
int m[Num][Num] = { 0 };
int Recure(int i, int j)
{
	if (i == j)
		return 0;
	int u = Recure(i, i) + Recure(i + 1, j) + p[i - 1] * p[i] * p[j];
	a[i][j] = i;
	for (int k = i + 1; k < j; k++)
	{
		int t = Recure(i, k) + Recure(k + 1, j) + p[i - 1] * p[k] * p[j];
		if (u > t)
		{
			u = t;
			a[i][j] = k;
		}
	}
	m[i][j] = u;
	return u;
}

int main()
{

	cout << Recure(1, 6)<< endl;
	getchar();
}
