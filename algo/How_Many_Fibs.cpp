#include<cstdio>
#include<cstring>
#include<iostream>
#include<string.h>
using namespace std;
#define MAXD 1000
#define LEN  100 + 10
int Fibs[MAXD][LEN];
void Add(int x[], int y[], int z[]) {
	for (int i = 0; i < LEN; i++) {
		z[i] += x[i] + y[i];
		if (z[i] >= 10) {
			z[i] %= 10;
			z[i + 1] ++;
		}
	}
}
void Fib() {
	memset(Fibs, 0, sizeof(Fibs));
	Fibs[0][0] = 1;
	Fibs[1][0] = 2;
	for (int i = 2; i < MAXD; i++) {
		Add(Fibs[i - 1], Fibs[i - 2], Fibs[i]);
	}
	return;
}
int Compare(char x[], int y[]) {
	int t[LEN] = { 0 };
	for (int i = 0, j = strlen(x) - 1; i < strlen(x); i++, j--) {
		t[i] = x[j] - '0';
	}
	for (int i = LEN - 1; i >= 0; i--) {
		if (t[i] > y[i]) return 0;
		else if (t[i] < y[i]) return 1;
	}
	return 2;
}
int main() {
	Fib();
	char a[LEN];
	char b[LEN];
	while (gets(a) && gets(b))
	{
		if (strcmp(a, "0") == 0 && strcmp(b, "0") == 0)
			return 0;
		int x, y;
		for (int i = 0; i < MAXD; i++) {
			int t = Compare(a, Fibs[i]);
			if (t) {
				x = i;
				break;
			}
		}
		for (int i = x; i < MAXD; i++) {
			int t = Compare(b, Fibs[i]);
			if (t == 1) {
				y = i;
				break;
			}
			else if (t == 2) {
				y = i + 1;
				break;
			}
		}
		printf("%d\n", y - x);
	}
	getchar();
	return 0;
}
