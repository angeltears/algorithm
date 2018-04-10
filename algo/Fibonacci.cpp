#include<cstdio>
#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;

#define N 56



// int main()
// {
// 	int n[N];
// 	n[1] = 1;
// 	n[2] = 2;
// 	n[3] = 3;
// 	n[4] = 4;
// 	int x;
// 	for (int i = 5; i < N; i++)
// 		n[i] = n[i - 1] + n[i - 3];
// 	while (cin >> x)
// 	{
// 		if (x > 0 && x < 55)
// 		{
// 			cout << n[x] << endl;
// 		}
// 	}
// }
int main()
{
	int n[N];
	n[0] = 0;
	n[1] = 1;
	for (int i = 2; i < N; i++)
		n[i] = n[i - 1] + n[i - 2];
	double x;
	while (cin >> x)
	{
		if (x < N)
			cout << n[(int)x] << endl;
		else
		{
			double al = log10(1.0 / sqrt(5));
			double a2 = log10((sqrt(5) + 1) / 2);
			double ans = al + x * a2;
			ans -= floor(ans);
			ans = pow(10, ans);
			ans = (int)(ans * 1000);
			cout << ans << endl;
		}
	}
  return 0;
}
