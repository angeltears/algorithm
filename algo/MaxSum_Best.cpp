#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

#define NUM 1001
int p[NUM] = { 1,-1,2,3,-1,5,-10,1 };

int MaxNum(int n, int& besti, int& bestj)
{
	int sum = 0;
	int b = 0;

	int begin = 0;
	for (int i = 0; i <= n; i++)
	{
		if (b > 0)
			b += p[i];
		else
		{
			b = p[i];
			begin = i;
		}
		if (b > sum)
		{
			sum = b;
			besti = begin;
			bestj = i;
		}
	}
	return sum;
}


int main()
{
	int begin = 0;
	int end = 0;
	cout << MaxNum(7, begin, end) << " ";
	cout << begin << " " << end << endl;;
	getchar();
}
