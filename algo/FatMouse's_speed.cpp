#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define N 1001

struct mouse
{
	int wight;
	int speed;
	int id;
}nice[N];

bool cmp(const mouse a, const mouse b)
{
	if (a.wight == b.wight)
	{
		if (a.speed > b.speed)
			return true;
		else
			return false;
	}
	else
		return a.wight < b.wight;
}

void output(int path[], int pos)
{
	if (pos == 0)
		return;
	output(path, path[pos]);
	cout << nice[pos].id;
}
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> nice[i].wight;
		cin >> nice[i].speed;
		nice[i].id = i;
	}
	sort(nice, nice + n, cmp);
	// 6008 1300 6000 2100 500 2000 1000 4000 1100 3000 6000 2000 8000 1400 6000 1200 2000 1900
	int count[N] = { 0 };
	int path[N] = { 0 };
	count[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j < i; j++)
		{
			if (nice[i].wight > nice[j].wight && nice[i].speed < nice[j].speed)
			{
				if (count[i] < count[j])
				{
					count[i] = count[j];
					path[i] = j;
				}
			}
		}
		count[i]++;
	}
	int max = 0;
	int pos;
	for (int i = 1; i <= n; i++)
	{
		if (count[i] > max)
		{
			max = count[i];
			pos = i;
		}
	}
	cout << max << endl;
	output(path, pos);
	getchar();
	getchar();
}
