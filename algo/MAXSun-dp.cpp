#include <iostream>
#include <algorithm>
using namespace std;
#define NUM 1001
int e[NUM] = {1,1,-1,-10,11,4,-6,9,20,-10,-2 };

int MaxSum(int n)
{
	int sum = 0;
	int b = 0;
	for (int i = 0; i <= n; i++)
	{
		if (b > 0)
			b += e[i];
		else
			b = e[i];

		if (b > sum)
			sum = b;
	}
	return sum;
}
int main()
{
	cout << MaxSum(10) << endl;
	getchar();
}
