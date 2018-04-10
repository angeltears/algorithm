#include <iostream>
#include<algorithm>
using namespace std;

template<class Type>
int BinarySearch(Type a[], Type& x, int n)
{
	int left = 0;
	int right = n - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (a[middle] == x)
			return middle;
		else if (a[middle] < x)
			left = middle + 1;
		else
			right = middle - 1;
	}
	return -1;
}


int main()
{
	int a[5];
	for (int i = 0; i < 5; i++)
	{
		cin >> a[i];
	}
	int x;
	cin >> x;
	sort(a, a + 5);
	cout<<BinarySearch(a, x, 5);
	getchar();
}
