#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;


int mod(int a, int p, int k)
{
	if (p == 1)
		return a % k;
	else if (p % 2 == 0)
		return mod((a * a) % k, p / 2, k);
	else
		return mod(a, p - 1, k) * a % k;
}

int main()
{
	int a;
	int p;
	int k;
	while (scanf("%d %d %d", &a, &p, &k) != EOF)
		cout << mod(a, p, k);

  return 0;
}
