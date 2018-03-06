#include "stl_alloc.h"
#include "stl_hashtable.h"
//#include <vector>
#include <iostream>

int main()
{
	hashtable<int, int, hash<int>, identity<int>, equal_to<int>, alloc> hs(10, hash<int>(), equal_to<int>(), identity<int>());
	int a[5] = { 1,2,3,4,5 };
	hs.insert_equal(5);
	hs.insert_equal(a, a + 5);
	hs.insert_equal(a, a + 5);
	hashtable<int, int, hash<int>, identity<int>, equal_to<int>, alloc> hb(hs);
	hashtable<int, int, hash<int>, identity<int>, equal_to<int>, alloc>::iterator it;
	for (it = hb.begin(); it!= hb.end(); it++)
		std::cout <<" "<< *it;

	getchar();
}
/*
template<class T>
struct KeyOfValue 
{
	T& operator()(const T &val) 
	{
		T* _val = new T(val);
		return *_val;
	}
};
int main()
{
	_Rb_tree<int, int, KeyOfValue<int>, less<int>> rb;
	rb.insert_unique(7);
	rb.insert_unique(4);
	rb.insert_unique(10);
	rb.insert_unique(rb.end(),8);
	rb.erase(10);
	_Rb_tree<int, int, KeyOfValue<int>, less<int>> rc(rb);
	rc.__rb_verify();
	_Rb_tree<int, int, KeyOfValue<int>, less<int>>::iterator it = rc.begin();
	for (; it != rc.end(); it++)
		std::cout << *it << std::endl;
	std::cout << *it << std::endl;
	//getchar();
}



void foo()
{
	cout << "you see you" << endl;
}

int main()
{
	malloc_alloc::set_malloc_handler(foo);
	int *p = (int *)malloc_alloc::allocate(16 * 899345920);
	p[0] = 1;
}
*/