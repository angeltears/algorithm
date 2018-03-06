#ifndef _LIST_H
#define _LIST_H

#include"memory.h"
#include<assert.h>

//1 框架构建
//2 insert函数分析
//3 分析迭代器iterator
//4 节点删除

//双向的循环链表
template<class _Ty, class _A = my_allocator<_Ty> >
class list
{
public:
	struct _Node;
	typedef struct _Node* _Nodeptr;
	struct _Node
	{
		_Nodeptr _Next;
		_Nodeptr _Prev;
		_Ty      _Value;
	};
	struct _Acc
	{
		typedef _Node*&  _Nodepref;
		typedef _Ty&     _Vref;
		static _Nodepref _Next(_Nodeptr _P)
		{return ((_Nodepref)(*_P)._Next);}
		static _Nodepref _Prev(_Nodeptr _P)
		{return ((_Nodepref)(*_P)._Prev);}
		static _Vref _Value(_Nodeptr _P)
		{return ((_Vref)(*_P)._Value);}
	};
public:
	//萃取
	typedef size_t size_type;
	typedef size_t difference_type;
	typedef _Ty&   reference;
	typedef _Ty*   pointer;
	typedef _Ty    value_type;
	typedef const _Ty& const_reference;
	typedef const _Ty* const_pointer;
public:
	class iterator
	{
	public:
		iterator()
		{}
		iterator(_Nodeptr _P) : _Ptr(_P)
		{}
	public:
		_Nodeptr _Mynode()const
		{return _Ptr;}
	public:
		reference operator*()const
		{return _Acc::_Value(_Ptr);}
		pointer operator->()const
		{return(&**this);}
	public:
		//++it
		iterator& operator++()
		{
			_Ptr = _Acc::_Next(_Ptr);
			return *this;
		}
		iterator operator++(int)
		{
			iterator _Tmp = *this;
			++*this;
			return _Tmp;
		}
		iterator& operator--()
		{
			_Ptr = _Acc::_Prev(_Ptr);
			return *this;
		}
		iterator  operator--(int);
	public:
		//it1 == it2;   it1.operator==(it2)
		bool operator==(const iterator &_X)const
		{return _Ptr == _X._Ptr;}
		bool operator!=(const iterator &_X)const
		{return !(*this==_X);}
	protected:
		_Nodeptr _Ptr;
	};

	typedef iterator _It;
public:
	//list<int> list1;
	explicit list() : _Head(_Buynode()), _Size(0)
	{}
	//list<int> list2(10);  or list<int> list3(10,2);
	explicit list(size_type _N, const _Ty &_V=_Ty()):_Head(_Buynode()),_Size(0)
	{insert(begin(), _N, _V);}
	list(const _Ty *_F, const _Ty *_L):_Head(_Buynode()),_Size()
	{insert(begin(), _F, _L);}
	list(_It _F, _It _L):_Head(_Buynode()),_Size(0)
	{insert(begin(), _F, _L);}
	~list()
	{
		erase(begin(), end());
		_Freenode(_Head);
		_Head = 0, _Size = 0;
	}
public:
	///////////////////////////////////////////////////////////////////
	/*
	list(const _Myt& _X);
	~list();
	_Myt& operator=(const _Myt& _X);
	const_iterator begin() const;
	const_iterator end() const;
	//reverse_iterator;
	void resize(size_type _N, _Ty _X = _Ty());
	size_type size() const;
	size_type max_size() const;
	bool empty() const;
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;
	void assign(_It _F, _It _L);
	void assign(size_type _N, const _Ty& _X = _Ty());
	iterator erase(iterator _F, iterator _L);
	void clear();
	void swap(_Myt& _X);
	void splice(iterator _P, _Myt& _X);
	void splice(iterator _P, _Myt& _X, iterator _F);
	void splice(iterator _P, _Myt& _X, iterator _F, iterator _L);
	void remove(const _Ty& _V);
	void remove_if(_Pr1 _Pr);
	void unique();
	void unique(_Pr2 _Pr);
	void merge(_Myt& _X);
	void merge(_Myt& _X, _Pr3 _Pr);
	void sort();
	void sort(_Pr3 _Pr);
	void reverse();
	*/
	///////////////////////////////////////////////////////////////////
public:
	iterator begin()
	{return (iterator(_Acc::_Next(_Head)));}
	iterator end()
	{return (iterator(_Head));}
public:
	void push_back(const _Ty &x)
	{insert(end(), x);}
 	void push_front(const _Ty &x)
	{insert(begin(),x);}
	void pop_front()
	{erase(begin());}
	void pop_back()
	{erase(--end());}
public:
	iterator insert(iterator _P, const _Ty &_X=_Ty())
	{
		_Nodeptr _S = _P._Mynode();
		_Acc::_Prev(_S) = _Buynode(_S, _Acc::_Prev(_S));
		_S = _Acc::_Prev(_S);
		_Acc::_Next(_Acc::_Prev(_S)) = _S;
		//_Acc::_Value(_S) = _X;
		allocator.construct(&_Acc::_Value(_S), _X);
		++_Size;
		return iterator(_S);
	}
	void insert(iterator _P, size_type _M, const _Ty &_X)
	{
		for(; 0<_M; --_M)
			insert(_P, _X);
	}
	void insert(iterator _P, const _Ty *_F, const _Ty *_L)
	{
		for(; _F!=_L; ++_F)
			insert(_P, *_F);
	}
	void insert(iterator _P, _It _F, _It _L)
	{
		for(; _F!=_L; ++_F)
			insert(_P, *_F);
	}
	iterator erase(iterator _P)
	{
		_Nodeptr _S = (_P++)._Mynode();
		_Acc::_Next(_Acc::_Prev(_S)) = _Acc::_Next(_S);
		_Acc::_Prev(_Acc::_Next(_S)) = _Acc::_Prev(_S);
		allocator.destroy(&_Acc::_Value(_S)); //deconstruct
		_Freenode(_S);
		--_Size;
		return _P;
	}
	iterator erase(iterator _F, iterator _L)
	{
		while (_F != _L)
			erase(_F++);
		return (_F); 
	}
protected:
	_Nodeptr _Buynode(_Nodeptr _Narg=0, _Nodeptr _Parg=0)
	{
		//_Nodeptr _S = (_Nodeptr)malloc(sizeof(_Node));
		_Nodeptr _S = (_Nodeptr)allocator._Charalloc(1 * sizeof (_Node));
		assert(_S != NULL);
		_Acc::_Next(_S) = _Narg!=0 ? _Narg : _S;
		_Acc::_Prev(_S) = _Parg!=0 ? _Parg : _S;
		return _S;
	} 
	void _Freenode(_Nodeptr _S)
	{allocator.deallocate(_S, 1);}
private:
	_A allocator;
	_Nodeptr _Head;
	size_type _Size;
};


#endif