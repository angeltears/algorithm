#include<iostream>
#include<vld.h>
#include"list.h"
#include"vector.h"
#include"deque.h"
#include"stack.h"
using namespace std;

//template<class _Ty, class _C = deque<_Ty> >

void main()
{
	stack<int, vector<int> > st;
	st.push(1);
	st.push(2);
}

/*
void main()
{
	deque<int> de;
	de.push_back(1);
	for(int i=100; i<612; ++i)
		de.push_front(i);
	de.push_front(613);
}

/*
void main()
{
	deque<int> de;
	for(int i=1; i<512; ++i)
	{
		de.push_back(i);
	}
	de.push_back(512);

	for(i=513; i<1536; ++i)
		de.push_back(i);
	de.push_back(1537);


	/*
	deque<int>::iterator it = de.begin();
	for(i=0; i<512; ++i)
	{
		cout<<*it<<"->";
		if(i == 511)
			++it;
		else
			++it;
	}
	cout<<*it<<endl;
	

}

/*
void main()
{
	deque<int> de;
	de.push_back(1);
	de.push_back(2);
	de.push_back(3);
	de.push_back(4);
	de.push_back(5);
	de.push_back(6);
	de.push_back(7);
	de.push_back(8);
	de.push_back(9);

	deque<int>::iterator it = de.begin();
	while(it != de.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

/*
void main()
{
	deque<int> de;
	for(int i=1; i<512; ++i)
	{
		de.push_back(i);
	}
	de.push_back(512);
	de.push_back(513);
}

/*
class Test
{
public:
	Test(int d = 0):data(d)
	{
		cout<<"Create Test Object."<<endl;
	}
	Test(const Test &t)
	{
		data = t.data; //
	}
	~Test()
	{
		cout<<"Free Test Object."<<endl;
	}
private:
	int data;
};

void main()
{
	Test t1(10);
	list<Test> mylist;
	mylist.push_back(t1);
}
/*
class String
{
public:
	String(const char *str = "")
	{
		data = new char[strlen(str)+1];
		strcpy(data, str);
	}
	~String()
	{
		delete []data;
		data = NULL;
	}
private:
	char *data;
};

void main()
{
	String *ps1 = new String("C++");
	list<String*> mylist;
	mylist.push_back(ps1);

}

/*
void main()
{
	list<int> mylist;
	mylist.push_back(1);
	mylist.push_back(2);
	mylist.push_back(3);
	mylist.push_back(4);
	mylist.push_back(5);


	mylist.pop_back();

	list<int>::iterator it;
	it = mylist.begin();
	
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
	
}

/*
void main()
{

	list<int> list1;
	list<int> list2(10);
	list<int> list3(10,2);

	int ar[10] = {1,2,3,4,5,6,7,8,9,10};
	list<int> list4(ar, ar+10);

	list<int>::iterator _F = list4.begin();
	list<int>::iterator _L = list4.end();
	//--_L;

	list<int> list5(_F, _L);

}

/*
class Test
{
public:
	void fun()
	{
		cout<<"Test::fun()"<<endl;
	}
};

void main()
{
	Test t;
	list<Test> mylist;
	mylist.push_back(t);

	list<Test>::iterator it = mylist.begin();
	it->fun();
}

/*
void main()
{
	list<int> mylist;
	mylist.push_back(1);
	mylist.push_back(2);
	mylist.push_back(3);
	mylist.push_back(4);
	mylist.push_back(5);

	list<int>::iterator it;
	it = mylist.begin();
	
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
	
}
*/