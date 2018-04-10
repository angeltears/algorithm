
#include <string>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
string a, b;
stack<char> build;
vector<char> operate;
int length = 0;

void dfs(int iPush, int iPop)
{
	if (iPush == length && iPop == length)
	{
		for (size_t i = 0; i < operate.size(); i++)
		{
			cout << operate[i] << " ";
		}
		cout << endl;
	}

	if (iPush + 1 <= length)
	{
		build.push(a[iPush]);
		operate.push_back('i');
		dfs(iPush + 1, iPop);
		build.pop();
		operate.pop_back();
	}

	if (iPop + 1 <= iPush && iPop + 1 <= length && build.top() == b[iPop])
	{
		char tc = build.top();
		build.pop();
		operate.push_back('o');
		dfs(iPush, iPop + 1);
		build.push(tc);
		operate.pop_back();
	}
}
int main()
{
	while (cin >> a >> b)
	{
		length = a.length();
		cout << "[";
		dfs(0, 0);
		cout << "]";
	}
}
