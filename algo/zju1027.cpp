#include <iostream>
#include <algorithm>
using namespace std;

int socre[5][5] = { {5,-1,-2,-1,-3},
					{-1,5,-3,-2,-4},
					{-2,-3,5,-2,-2},
					{-1,-2,-2,5,-1},
					{-3,-4,-2,-1,0} };
char map[128];
#define NUM 100
char str1[NUM], str2[NUM];
int gene[NUM][NUM];
int main()
{
	map['A'] = 0;
	map['C'] = 1;
	map['G'] = 2;
	map['T'] = 3;
	map['-'] = 4;
	int frist;
	int second;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> frist >> str1;
		cin >> second >> str2;
		gene[0][0] = 0;
		for (int i = 1; i <= second; i++)
			gene[0][i] = gene[0][i - 1] + socre[4][map[str2[i - 1]]];
		for (int i = 1; i <= frist; i++)
			gene[i][0] = gene[i - 1][0] + socre[map[str1[i - 1]]][4];
		for (int i = 1; i <= frist;i++)
		{
			for (int j = 1; j <= second;j++)
			{
				int m1 = gene[i - 1][j] + socre[map[str1[i - 1]]][4];
				int m2 = gene[i][j - 1] + socre[4][map[str2[j - 1]]];
				int m3 = gene[i - 1][j - 1] + socre[map[str1[i - 1]]][map[str2[j - 1]]];
				gene[i][j] = max(m1, max(m2, m3));
			}
		}
		cout << endl;
		cout << gene[frist][second] << endl;;
	}
	getchar();
	getchar();
}
