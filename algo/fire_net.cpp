#include<iostream>
#include<algorithm>
using namespace std;

char cmap[5][5];
int iBest = 0;
int number;
/*
û�б�Ҫ��֤ǰ����û�б��ݣ�ֻ�ù��Ĳ���֮ǰ������û�У���Ϊ���Ǵ�0 0��ʼ������
*/
bool canput(int row, int col)
{
	for (int i = row - 1; i >= 0; i--)
	{
		if (cmap[i][col] == '0')
			return false;
		else if(cmap[i][col] == 'X')
			break;
	}
	for (int i = col - 1; i >= 0; i--)
	{
		if (cmap[row][i] == '0')
			return false;
		else if (cmap[row][i] == 'X')
			break;
	}
	return true;
}


void solve(int k, int current)
{
	int x, y;
	if (k == number*number)
	{
		if (current > iBest)
		{
			iBest = current;
			return;
		}
	}
	else
	{
		x = k / number;
		y = k % number;
		if (cmap[x][y] == '.' && canput(x, y))
		{
			cmap[x][y] = '0';
			solve(k + 1, current + 1);
			cmap[x][y] = '.';
		}
		solve(k + 1, current);
	}
}


int main()
{
	while (cin >> number)
	{
		for (int i = 0; i < number; i++)
		{
			for (int j = 0; j < number; j++)
			{
				cin >> cmap[i][j];
			}
		}
		solve(0, 0);
		cout << iBest << endl;
		iBest = 0;
	}
	return 0;
}
