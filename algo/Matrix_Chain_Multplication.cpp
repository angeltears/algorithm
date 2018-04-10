#include <map>
#include <string>
#include <stack>
#include <iostream>
using namespace std;

struct node
{
	int row;
	int col;
};

int main()
{
	int n;
	char name;
	map<char, node> mp;

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> name;
		cin >> mp[name].col >> mp[name].row;
	}
	printf("�����ַ���");
	string exp;
	while (cin >> exp)
	{
		stack<node> st;
		size_t i;
		int count = 0;
		for (i = 0; i < exp.size(); i++)
		{
			if (exp[i] == '(')
				continue;
			else if (exp[i] == ')')
			{
				node a = st.top();
				st.pop();
				node b = st.top();
				st.pop();
				if (a.col != b.row)
				{
					cout << "error" << endl;
					break;
				}
				count += a.col * a.row * b.col;
				node tmp;
				tmp.col = b.col;
				tmp.row = a.row;
				st.push(tmp);
			}
			else
			{
				st.push(mp[exp[i]]);
			}
		}
		if (i == exp.size())
			cout << count << endl;
	}
}
