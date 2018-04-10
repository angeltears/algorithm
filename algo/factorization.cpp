#include<iostream>
using namespace std;
int totals = 0;
void solov(int n)
{
	if (n == 1)
		totals++;
	else
		for (int i = 2; i <= n; i++)
			if (n % i == 0)
				solov(n / i);

}
//
int main()
{
	int n;
	cin >> n;
	solov(n);
	cout << totals;
}
