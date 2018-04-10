#include <iostream>
#include <algorithm>
using namespace std;


#define NUM 100
int tri[NUM][NUM] = { {9},
					  {12,15},
					  {10,6,8},
					  {2,18,9,5},
					  {19,7,10,4,16} };
int triangle(int n)
{
	int i, j;
	for (i = n - 2; i >= 0; i--)
	{
		for (j = 0; j <= i; j++)
		{
			tri[i][j] += max(tri[i + 1][j], tri[i + 1][j + 1]);
		}
	}
	return tri[0][0];
}

int main()
{
	cout << triangle(5);
	getchar();
}
