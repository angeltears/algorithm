#include <iostream>
#include <cstdio>
using namespace std;

#define NUM 100
int n;
//int c;
//int w[NUM];
//int x[NUM];
//int r;
//int cw;
//int bestw;
//int bestx[NUM];
//
//void Backtrack(int t)
//{
//	if (t > n)
//	{
//		if (cw > bestw)
//		{
//			bestw = cw;
//			for (int i = 1; i <= n; i++)
//				bestx[i] = x[i];
//		}
//		return;
//	}
//
//	r -= w[t];
//	if (cw + w[t] <= c)
//	{
//		x[t] = 1;
//		cw += w[t];
//		Backtrack(t + 1);
//		cw -= w[t];
//	}
//
//	if (cw + r > bestw)
//	{
//		x[t] = 0;
//		Backtrack(t + 1);
//	}
//	r += w[t];
//}
//
//
//int main()
//{
//	while (1)
//	{
//		cin >> c >> n;
//		r = 0;
//		cw = 0;
//		for (int i = 1; i <= n; i++)
//		{
//			cin >> w[i];
//			r += w[i];
//		}
//		Backtrack(1);
//		cout << bestw << endl;
//		for (int i = 1; i <= n; i++)
//		{
//			if (bestx[i] != 0)
//				cout << i << " ";
//		}
//		cout << endl;
//	}
//}
#include <iostream>
using namespace std;
template<class T>
class MinHeap
{
private:
	T *heap; //