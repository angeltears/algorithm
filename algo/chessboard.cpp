#include <iostream>
#include <algorithm>
using namespace std;

static int tile = 1;
int board[1024][1024] = { 0 };

void chessBoard(int tr, int tc, int dr, int dc, int size)
{
	if (size == 1)
		return;

	int t = tile++;
	int s = size / 2;

	if (dr < tr + s && dc < tc + s)
	{
		chessBoard(tr, tc, dr, dc, s);
	}
	else
	{
		board[tr + s - 1][tc + s - 1] = t;
		chessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
	}

	if (dr < tr + s && dc >= tc + s)
	{
		chessBoard(tr, tc + s, dr, dc, s);
	}
	else
	{
		board[tr + s - 1][tc + s] = t;
		chessBoard(tr, tc + s, tr + s - 1, tc + s, s);
	}

	if (dr >= tr + s && dc < tc + s)
	{
		chessBoard(tr + s, tc, dr, dc, s);
	}
	else
	{
		board[tr + s][tc + s - 1] = t;
		chessBoard(tr + s, tc, tr + s, tc + s - 1, s);
	}

	if (dr >= tr + s && dc >= tc + s)
	{
		chessBoard(tr + s, tc + s, dr, dc, s);
	}
	else
	{
		board[tr + s][tc + s] = t;
		chessBoard(tr + s, tr + s, tr + s, tc + s, s);
	}
}


int main()
{
	int size;
	cin >> size;
	int dr, dc;
	cin >> dr >> dc;
	chessBoard(0, 0, dr, dc, 1 << size);

	for (int i = 0; i < 1 << size; i++)
	{
		for (int j = 0; j < 1 << size; j++)
			cout << board[i][j] << " ";
		cout << endl;
	}
	getchar();
	getchar();

}
