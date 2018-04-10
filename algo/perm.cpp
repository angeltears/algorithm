#include<iostream>
using namespace std;

void Perm(int*list, int k, int m)
{
	if (k == m)
	{
		for (int i = 0; i <= m; i++)
		{
			cout << list[i] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int j = k; j <= m; j++)
		{
			swap(list[k], list[j]);
			Perm(list, k + 1, m);
			swap(list[k], list[j]);
		}
	}
}
int main()
{
	int a[4] = { 1,2,3,4 };
	Perm(a, 0, 3);
	getchar();
}
