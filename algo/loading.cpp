#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

#define N 1000
struct load
{
	int index;
	int w;
}box[N];

bool cmp(const load& a, const load& b)
{
	if (a.w < b.w)
		return true;
	else
		return false;
}


int main()
{
	int c, n;
	int x[N];
	while (cin >> c >> n)
	{
		memset(box, 0, sizeof(box));
		memset(x, 0, sizeof(x));
		for (int i = 1; i <= n; i++)
		{
			cin >> box[i].w;
			box[i].index = i;
		}

		stable_sort(box, box + (n+1), cmp);

		if (box[1].w > c)
		{
			printf("No answer\n");
			continue;
		}
		int i;
		for (i = 1; i <= n; i++)
		{
			if (c >= box[i].w)
			{
				c -= box[i].w;
				x[box[i].index] = 1;
			}
			else
				break;
		}
		cout << i - 1 << endl;
		for (int i = 1; i <= n; i++)
			if (x[i] == 1)
				cout << i << " ";
		cout << endl;
	}
}
