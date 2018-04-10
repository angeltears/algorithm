#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define NUM 100
int c;
int n;
int cw;
int cv;
int bestv;

struct object
{
	int w;
	int v;
	double d;
}Q[NUM];

bool cmp(object a, object b)
{
	if (a.d < b.d)
		return true;
	return false;
}
int bound(int i)
{
	int cleft = c - cw;
	int b = cv;
	while (i < n && Q[i].w <= cleft)
	{
		cleft -= Q[i].w;
		b += Q[i].v;
		i++;
	}
	if (i < n)
		b += cleft + Q[i].d;
	return b;
}
void backtrack(int i)
{
	if (i + 1 > n)
	{
		bestv = cv;
		return;
	}
	if (cw + Q[i].w <= c)
	{
		cw += Q[i].w;
		cv += Q[i].v;
		backtrack(i + 1);
		cw -= Q[i].w;
		cv -= Q[i].v;
	}
  if (bound(i + 1) > bestv)
	{
		backtrack(i + 1);
	}
}

int main()
{
	while (1)
	{
		cin >> c >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> Q[i].w >> Q[i].v;
			Q[i].d = 1.0 * Q[i].v / Q[i].w;
		}
		sort(Q, Q + n, cmp);
		backtrack(0);
		cout << bestv << endl;
	}
	return 0;
}
