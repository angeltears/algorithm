#include <iostream>
#include <algorithm>
using namespace std;

#define NUM 100
int as[NUM] = { 65,158,170,155,239,300,207,389 };

int lis(int n)
{
	int b[NUM];
	int i, j;
	b[1] = 1;
	int max = 0;
	for (i = 2; i < n; i++)
	{
		int k = 0;
		for (j = 1; j < i; j++)
		{
			if (as[j] < as[i] && k < b[j])
				k = b[j];
			b[i] = k + 1;
			if (max < b[i])
				max = b[i];
		}
	}
	return max;
}


int main()
{
	cout <<	lis(8);
	getchar();
}
