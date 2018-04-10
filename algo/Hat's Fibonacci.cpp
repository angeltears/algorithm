#include<stdio.h>
#include<string.h>
#define N 10000    //N�ܹؼ���N=10000����20000������AC��Nȡ�ù�С������
int str[N][260];
// int main()
// {
// 	memset(str, 0, sizeof(str));
// 	str[1][0] = 1;
// 	str[2][0] = 1;
// 	str[3][0] = 1;
// 	str[4][0] = 1;
// 	int i, j, ans = 0, c, n;
// 	for (i = 5; i<N; i++)
// 	{
// 		for (j = 0, c = 0; j<260; j++)
// 		{
// 			ans = str[i - 1][j] + str[i - 2][j] + str[i - 3][j] + str[i - 4][j] + c;
// 			c = ans / 100000000;
// 			str[i][j] = ans % 100000000;   //ÿһ��������8λ���֣�c�������Ƿ���λ��
// 		}
// 	}
// 	while (scanf_s("%d", &n) != EOF)
// 	{
// 		j = 259;
// 		while (!str[n][j])    //����0������
// 			j--;
// 		printf("%d", str[n][j]);
// 		for (i = j - 1; i >= 0; i--)
// 			printf("%08d", str[n][i]);//ÿ8λ����������8λ�Զ���0��
// 		printf("\n");
// 	}
// 	return 0;
// }


#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;


string add(string a, string b)
{
	string result;
	int tmp = 0;
	int res = 0;
	int asize = a.size() - 1;
	int bsize = b.size() - 1;
	int maxsize = max(asize, bsize) + 1;
	result.resize(maxsize + 1);
	result[0] = '0';
	while (1)
	{
		if (asize >= 0 && bsize >= 0)
		{
			res = a[asize] + b[bsize] - 96 + tmp;
			tmp = res / 10;
			res = res % 10;
			result[maxsize] = res + 48;
			asize--;
			bsize--;
			maxsize--;
		}
		else if (bsize < 0 && asize >= 0)
		{
			res = a[asize] - 48 + tmp;
			tmp = res / 10;
			res = res % 10;
			result[maxsize] = res + 48;
			asize--;
			maxsize--;
		}
		else if (asize < 0 && bsize >= 0)
		{
			res = b[bsize] - 48 + tmp;
			tmp = res / 10;
			res = res % 10;
			result[maxsize] = res + 48;
			bsize--;
			maxsize--;
		}
		else
		{
			if (tmp != 0)
			{
				result[0] = tmp + 48;
				return  result;
			}
			else
			{
				string tmp((++result.begin()), result.end());
				return tmp;
			}
		}
	}
	return result;
}


int main()
{
	string a[10006];
	for (int i = 0; i < 4; i++)
		a[i] = "1";
	int n;
	while (cin >> n)
	{
		int i;
		for (i = 4; i < n; i++)
		{
			a[i] = add(add(a[i - 1], a[i - 2]), add(a[i - 3], a[i - 4]));
		}
		cout << a[i - 1] << endl;
	}
  return 0;
}
