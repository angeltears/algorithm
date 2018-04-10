#include <iostream>
#include <algorithm>
using namespace std;

struct bag
{
	int w;
	int v;
	double c;
	double x;
	int index;
}bags[1000];

bool cmp(const bag& a, const bag& b)
{
	if (a.c < b.c)
		return false;
	else
		return true;
}

double knapack(int n, bag a[], double c)
{
	double cleft = c;
	int i = 0;
	double b = 0;
	while (i < n && a[i].w < cleft)
	{
		cleft -= a[i].w;
		b += a[i].v;
		a[i].x = 1.0;
		i++;
	}
	if (i < n)
	{
		b += 1.0 * a[i].v * cleft / a[i].w;
		a[i].x = 1.0 * cleft / a[i].w;
	}
	return b;
}


int main()
{
	int n;
	cin >> n;
	double c;
	cin >> c;
	for (int i = 0; i < n; i++)
	{
		cin >> bags[i].w;
		cin >> bags[i].v;
		bags[i].index = i + 1;
		bags[i].c = (double)bags[i].v / bags[i].w;
	}
	sort(bags, bags + n, cmp);
	cout <<knapack(n, bags, c)<<endl;
	for (int i = 0; i < n; i++)
	{
		if (bags[i].x > 0)
		{
			cout << bags[i].index << " " << bags[i].x * bags[i].w << endl;
		}
	}
	getchar();
	getchar();
}
