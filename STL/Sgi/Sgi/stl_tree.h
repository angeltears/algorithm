#pragma once
#include "stl_construct.h"
#include "stl_algobase.h"
#include "stl_alloc.h"
#include "stl_function.h"
#include"stl_pair.h" 
typedef bool __Rb_tree_color_type;
__Rb_tree_color_type __rb_tree_red = false;
__Rb_tree_color_type __rb_tree_black = true;

struct __Rb_tree_node_base
{
	typename typedef __Rb_tree_color_type _Color_type;
	typename typedef __Rb_tree_node_base* _Base_ptr;
	_Color_type _color;
	_Base_ptr _parent;
	_Base_ptr _left;
	_Base_ptr _right;
	
	static _Base_ptr _mininum(_Base_ptr x)
	{
		while (x->_left != 0)
			x = x->_left;
		return x;
	}

	static _Base_ptr _maxinum(_Base_ptr x)
	{
		while (x->_right != 0)
			x = x->_right;
		return x;
	}

};

template<class _Value>
struct __Rb_tree_node :public __Rb_tree_node_base
{
	typedef __Rb_tree_node<_Value>* _Link_type;
	_Value _value_field;
};

struct _Rb_tree_base_iterator
{
	typedef __Rb_tree_node_base::_Base_ptr _Base_ptr;
	typedef bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
	_Base_ptr _node;

	void increment()
	{
		if (_node->_right != 0)
		{
			_node = _node->_right;
			while (_node->_left != 0)
				_node = _node->_left;
		}
		else
		{
			_Base_ptr _y = _node->_parent;
			while (_node == _y->_right)
			{
				_node = _y;
				_y = _y->_parent;
			}
			if (_node->_right != _y)
				_node = _y;
		}
	}
	void decrement()
	{
		if (_node->_color == __rb_tree_red && _node->_parent->_parent == _node)
		{
			_node = _node->_right;
		}
		else if (_node->_left != 0)
		{
			_Base_ptr _y = _node->_left;
			while (_y->_right != 0)
				_y = _y->_right;
			_node = _y;
		}
		else
		{
			_Base_ptr _y = _node->_parent;
			while (_node == _y->_left)
			{
				_node = _y;
				_y = _node->_parent;
			}
			_node = _y;
		}
	}
};

template<class _Value, class _Ref, class _Ptr>
struct _Rb_tree_iterator : public _Rb_tree_base_iterator
{
	typedef _Value                                                    value_type;
	typedef _Ref													  reference;
	typedef _Ptr													  pointer;
	typedef _Rb_tree_iterator<_Value, _Value&, _Value*>               iterator;
	typedef _Rb_tree_iterator<_Value, const _Value&, const _Value*>   const_iterator;
	typedef _Rb_tree_iterator<_Value, _Ref, _Ptr>                     _Self;
	typedef __Rb_tree_node<_Value>*									  _Link_type;

	_Rb_tree_iterator(){}
	_Rb_tree_iterator(_Link_type _x)
	{
		_node = _x;
	}
	_Rb_tree_iterator(const iterator& _it)
	{
		_node = _it._node;
	}
	reference operator*() const
	{
		return _Link_type(_node)->_value_field;
	}
	pointer operator->() const
	{
		return  &(operator *());
	}
	_Self& operator++()
	{
		increment();
		return *this;
	}
	_Self operator++(int)
	{
		_Self tmp = *this;
		increment();
		return tmp;
	}
	_Self& operator--()
	{
		decrement();
		return *this;
	}
	_Self operator--(int)
	{
		_Self tmp = *this;
		decrement();
		return tmp;
	}
};
bool operator==(const _Rb_tree_base_iterator& __x,
	const _Rb_tree_base_iterator& __y) 
{
	return __x._node == __y._node;
}
bool operator!=(const _Rb_tree_base_iterator& __x,
	const _Rb_tree_base_iterator& __y) 
{
	return __x._node != __y._node;
}

void _Rb_tree_rotate_left(__Rb_tree_node_base* __x, __Rb_tree_node_base*& __root)
{
	__Rb_tree_node_base* __y = __x->_right;
	__x->_right = __y->_left;
	if (__y->_left != 0)
	{
		__y->_left->_parent = __x;
	}
	__y->_parent = __x->_parent;
	if (__x == __root)
	{
		__root = __y;
	}
	else if (__x == __x->_parent->_left)
	{
		__x->_parent->_left = __y;
	}
	else
	{
		__x->_parent->_right = __y;
	}
	__x->_parent = __y;
	__y->_left = __x;
}

void _Rb_tree_rotate_right(__Rb_tree_node_base* __x, __Rb_tree_node_base*& __root)
{
	__Rb_tree_node_base* __y = __x->_left;
	__x->_left = __y->_right;
	if (__y->_right != 0)
	{
		__y->_right->_parent = __x;
	}
	__y->_parent = __x->_parent;
	if (__x == __root)
	{
		__root = __y;
	}
	else if (__x == __x->_parent->_left)
	{
		__x->_parent->_left = __y;
	}
	else
	{
		__x->_parent->_right = __y;
	}
	__y->_right = __x;
	__x->_parent = __y;
}

void _Rb_tree_rebalance(__Rb_tree_node_base* __x, __Rb_tree_node_base*& __root)
{
	__x->_color = __rb_tree_red;
	while (__x != __root && __x->_parent->_color == __rb_tree_red)
	{
		if (__x->_parent == __x->_parent->_parent->_left)
		{
			__Rb_tree_node_base* __y = __x->_parent->_parent->_right;
			if (__y && (__y->_color = __rb_tree_red))
			{
				__x->_parent->_color = __rb_tree_black;
				__x->_parent->_parent->_color = __rb_tree_red;
				__y->_color = __rb_tree_black;
				__x = __x->_parent->_parent;
			}
			else
			{
				if (__x == __x->_parent->_right)
				{
					__x = __x->_parent;
					_Rb_tree_rotate_left(__x, __root);
				}
				__x->_parent->_color = __rb_tree_black;
				__x->_parent->_parent->_color = __rb_tree_red;
				_Rb_tree_rotate_right(__x->_parent->_parent, __root);
			}
		}
		else
		{
			__Rb_tree_node_base* __y = __x->_parent->_parent->_left;
			if (__y && (__y->_color = __rb_tree_red))
			{
				__x->_parent->_color = __rb_tree_black;
				__x->_parent->_parent->_color = __rb_tree_red;
				__y->_color = __rb_tree_black;
				__x = __x->_parent->_parent;
			}
			else
			{
				if (__x == __x->_parent->_left)
				{
					__x = __x->_parent;
					_Rb_tree_rotate_right(__x, __root);
				}
				__x->_parent->_color = __rb_tree_black;
				__x->_parent->_parent->_color = __rb_tree_red;
				_Rb_tree_rotate_left(__x->_parent->_parent, __root);
			}
		}
	}
	__root->_color = __rb_tree_black;
}

__Rb_tree_node_base* _Rb_tree_rebalance_for_erase(
	__Rb_tree_node_base* __z,  __Rb_tree_node_base*& __root, 
	__Rb_tree_node_base*& __leftmost, __Rb_tree_node_base*& __rightmost)
{
	__Rb_tree_node_base* __y = __z;
	__Rb_tree_node_base* __x = 0;
	__Rb_tree_node_base* __x_parent = 0;
	
	if (__y->_left == 0)
	{
		__x = __y->_right;
	}
	else
	{
		if (__y->_right == 0)
		{
			__x = __y->_left;
		}
		else
		{
			__y = __y->_right;
			while (__y->_left != 0)
			{
				__y = __y->_left;
			}
			__x = __y->_right;
		}
	}

	if (__y != __z)
	{
		__z->_left->_parent = __y;
		__y->_left = __z->_left;
		if (__z->_right != __y)
		{
			__x_parent = __y->_parent;
			if (__x != 0)
			{
				__x->_parent = __y->_parent;
			}
			__y->_parent->_left = __x;
			__y->_right = __z->_right;
			__z->_right->_parent = __y;
		}
		else
			__x_parent = __y;

		if (__root == __z)
			__root = __y;
		else if (__z->_parent->_left == __z)
			__z->_parent->_left = __y;
		else
			__z->_parent->_right = __y;
		__y->_parent = __z->_parent;
		STD::swap(__y->_color, __z->_color);
		__y = __z;
	}
	else
	{
		__x_parent = __y->_parent;
		if (__x != 0)
			__x->_parent = __y->_parent;
		if (__root == __z)
			__root = __x;
		else
			if (__z->_parent->_left == __z)
				__z->_parent->_left = __x;
			else
				__z->_parent->_right = __x;
		if (__leftmost == __z)
			if (__z->_right == 0)
				__leftmost = __z->_parent;
			else
				__leftmost = __Rb_tree_node_base::_mininum(__x);
		if (__rightmost == __z)
			if (__z->_left == 0)
				__rightmost = __z->_parent;
			else
				__rightmost = __Rb_tree_node_base::_maxinum(__x);
	}
	
	if (__y->_color != __rb_tree_red)
	{
		while (__x != __root && (__x == 0 || __x->_color == __rb_tree_black))
			if (__x == __x_parent->_left)
			{
				__Rb_tree_node_base* __w = __x_parent->_right;
				if (__w->_color == __rb_tree_red)
				{
					__w->_color = __rb_tree_black;
					__x_parent->_color = __rb_tree_red;
					_Rb_tree_rotate_left(__x_parent, __root);
					__w = __x_parent->_right;
				}
				if ((__w->_left == 0 || __w->_left->_color == __rb_tree_black) &&
					(__w->_right == 0 || __w->_right->_color == __rb_tree_black))
				{
					__w->_color = __rb_tree_red;
					__x = __x_parent;
					__x_parent = __x_parent->_parent;
				}
				else 
				{
					if (__w->_right == 0 || __w->_right->_color == __rb_tree_black) 
					{
						if (__w->_left) __w->_left->_color = __rb_tree_black;
						__w->_color = __rb_tree_red;
						_Rb_tree_rotate_right(__w, __root);
						__w = __x_parent->_right;
					}
					__w->_color = __x_parent->_color;
					__x_parent->_color = __rb_tree_black;
					if (__w->_right) __w->_right->_color = __rb_tree_black;
					_Rb_tree_rotate_left(__x_parent, __root);
					break;
				}
			}
			else 
			{                
				__Rb_tree_node_base* __w = __x_parent->_left;
				if (__w->_color == __rb_tree_red)
				{
					__w->_color = __rb_tree_black;
					__x_parent->_color = __rb_tree_red;
					_Rb_tree_rotate_right(__x_parent, __root);
					__w = __x_parent->_left;
				}
				if ((__w->_right == 0 ||
					__w->_right->_color == __rb_tree_black) &&
					(__w->_left == 0 ||
						__w->_left->_color == __rb_tree_black))
				{
					__w->_color = __rb_tree_red;
					__x = __x_parent;
					__x_parent = __x_parent->_parent;
				}
				else 
				{
					if (__w->_left == 0 || __w->_left->_color == __rb_tree_black) 
					{
						if (__w->_right) __w->_right->_color = __rb_tree_black;
						__w->_color = __rb_tree_red;
						_Rb_tree_rotate_left(__w, __root);
						__w = __x_parent->_left;
					}
					__w->_color = __x_parent->_color;
					__x_parent->_color = __rb_tree_black;
					if (__w->_left)
					{
						__w->_left->_color = __rb_tree_black;
					}
					_Rb_tree_rotate_right(__x_parent, __root);
					break;
				}
			}
			if (__x) __x->_color = __rb_tree_black;
	}
	return __y;
}

template <class _Tp, class _Alloc>
struct _Rb_tree_base
{
	typedef _Alloc allocator_type;
	allocator_type get_allocator() const { return allocator_type(); }

	_Rb_tree_base(const allocator_type&)
		: _header(0) {
		_header = _get_node();
	}
	~_Rb_tree_base() { _put_node(_header); }

protected:
	__Rb_tree_node<_Tp>* _header;

	typedef simple_alloc<__Rb_tree_node<_Tp>, _Alloc> _Alloc_type;

	__Rb_tree_node<_Tp>* _get_node()
	{
		return _Alloc_type::allocate(1);
	}
	void _put_node(__Rb_tree_node<_Tp>* __p)
	{
		_Alloc_type::deallocate(__p, 1);
	}
};


template <class _Key, class _Value, class _KeyOfValue, class _Compare,
	class _Alloc = alloc>
	class _Rb_tree : protected _Rb_tree_base<_Value, _Alloc>
{
	typedef _Rb_tree_base<_Value, _Alloc>	_Base;
protected:
	typedef _Rb_tree_base* _Base_ptr;
	typedef __Rb_tree_node<_Value>			_Rb_tree_node;
	typedef __Rb_tree_color_type			_Color_type;
public:
	typedef _Key							key_type;
	typedef _Value							value_type;
	typedef value_type*					    pointer;
	typedef const value_type*				const_pointer;
	typedef value_type&						reference;
	typedef const value_type&				const_reference;
	typedef _Rb_tree_node*					_Link_type;
	typedef size_t							size_type;
	typedef ptrdiff_t						difference_type;
	typedef typename _Base::allocator_type	allocator_type;

protected:
	_Link_type _create_node(const value_type& x)
	{
		_Link_type tmp = _get_node();
		//try
		_Construct(&tmp->_value_field, x);
		//unwind
		return tmp;
	}
	_Link_type _clone_node(_Link_type x)
	{
		_Link_type tmp = _create_node(x->_value_field);
		tmp->_color = x->_color;
		tmp->_left = 0;
		tmp->_right = 0;
		return tmp;
	}
	void _destroy_node(_Link_type p)
	{
		_Destroy(&p->_value_field);
		_put_node(p);
	}
protected:
	size_type   _node_count;
	_Compare    _key_compare;

	_Link_type& _root() const
	{
		return (_Link_type&)_header->_parent;
	}
	_Link_type& _leftmost() const
	{
		return (_Link_type&)_header->_left;
	}
	_Link_type& _rightmost() const
	{
		return (_Link_type&)_header->_right;
	}
	static _Link_type& _left(_Link_type __x)
	{
		return (_Link_type&)(__x->_left);
	}
	static _Link_type& _right(_Link_type __x)
	{
		return (_Link_type&)(__x->_right);
	}
	static _Link_type& _parent(_Link_type __x)
	{
		return (_Link_type&)(__x->_parent);
	}
	static reference _value(_Link_type __x)
	{
		return __x->_value_field;
	}
	static const _Key& _key(_Link_type __x)
	{
		return _KeyOfValue()(_value(__x));
	}
	static _Color_type& _color(_Link_type __x)
	{
		return (_Color_type&)(__x->_color);
	}
	static _Link_type _minimum(_Link_type __x)
	{
		return (_Link_type)__Rb_tree_node_base::_mininum(__x);
	}
	static _Link_type _maximum(_Link_type __x)
	{
		return (_Link_type)__Rb_tree_node_base::_maxinum(__x);
	}
public:
	typedef _Rb_tree_iterator<value_type, reference, pointer> iterator;
	typedef _Rb_tree_iterator<value_type, const_reference, const_pointer> const_iterator;
private:
	iterator _insert(_Base_ptr __x, _Base_ptr __y, const value_type &__v);
	iterator _copy(_Link_type __x, _Link_type __p);
	void _erase(_Link_type x);
	void _empty_init()
	{
		_color(_header) = __rb_tree_red;
		_root() = 0;
		_leftmost() = _header;
		_rightmost() = _header;
	}
public:
	_Rb_tree() :_Base(allocator_type()), _node_count(0), _key_compare()
	{
		_empty_init();
	}
	_Rb_tree(const _Compare& __comp)
		: _Base(allocator_type()), _node_count(0), _key_compare(__comp)
	{
		_empty_init();
	}
	_Rb_tree(const _Compare& __comp, const allocator_type& __a)
		: _Base(__a), _node_count(0), _key_compare(__comp)
	{
		_empty_init();
	}
	_Rb_tree(const _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& __x)
		: _Base(__x.get_allocator()),
		_node_count(0), _key_compare(__x._key_compare)
	{
		if (__x._root() == 0)
			_empty_init();
		else {
			_color(_header) = __rb_tree_red;
			_root() = (_Link_type)_copy(__x._root(), _header)._node;
			_leftmost() = _minimum(_root());
			_rightmost() = _maximum(_root());
		}
		_node_count = __x._node_count;
	}
	~_Rb_tree()
	{
		clear();
	}
	_Rb_tree< _Key, _Value, _KeyOfValue, _Compare, _Alloc>& operator=(const _Rb_tree< _Key, _Value, _KeyOfValue, _Compare, _Alloc>& x);
public:
	_Compare key_comp() const
	{
		return _key_compare;
	}
	iterator begin()
	{
		return _leftmost();
	}
	const_iterator begin() const
	{
		return _leftmost();
	}
	iterator end()
	{
		return _rightmost();
	}
	const_iterator end() const
	{
		return _rightmost();
	}
	bool empty() const
	{
		return _node_count == 0;
	}
	size_type size() const
	{
		return _node_count;
	}
	size_type max_size() const
	{
		return size_type(-1);
	}
	void swap(_Rb_tree< _Key, _Value, _KeyOfValue, _Compare, _Alloc>& _t)
	{
		STD::swap(_header, _t._header);
		STD::swap(_node_cout, _t._node_count);
		STD::swap(_key_compare, _t._key_compare);
	}
public:
	pair<iterator, bool> insert_unique(const value_type& __v);
	iterator insert_equal(const value_type& __v);
	iterator insert_unique(iterator __position, const value_type& __v);
	iterator insert_equal(iterator __position, const value_type& __v);
public:
	void erase(iterator __position);
	size_type erase(const key_type& __x);
	void erase(iterator __first, iterator __last);
	void erase(const key_type* __first, const key_type* __last);
	void clear()
	{
		if (_node_count != 0)
		{
			_erase(_root());
			_leftmost() = _header;
			_root() = 0;
			_rightmost() = _header;
			_node_count = 0;
		}
	}
public:
	iterator find(const key_type& __x);
	const_iterator find(const key_type& __x) const;
	size_type count(const key_type& __x) const;
	iterator lower_bound(const key_type& __x);
	const_iterator lower_bound(const key_type& __x) const;
	iterator upper_bound(const key_type& __x);
	const_iterator upper_bound(const key_type& __x) const;
	pair<iterator, iterator> equal_range(const key_type& __x);
	pair<const_iterator, const_iterator> equal_range(const key_type& __x) const;
public:
	bool __rb_verify() const;
};

template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
bool operator==(const _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& __x,
		const _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& __y)
{
	return __x.size() == __y.size() && equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
bool operator<(const _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& __x,
		const _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& __y)
{
	return lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>&
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::
operator=(const _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& __x)
{
	if (this != &__x) {
		clear();
		_node_count = 0;
		_key_compare = __x._key_compare;
		if (__x._root() == 0) {
			_root() = 0;
			_leftmost() = _header;
			_rightmost() = _header;
		}
		else {
			_root() = _copy(__x.__root(), _header);
			_leftmost() = _minimum(_root());
			_rightmost() = _maximum(_root());
			_node_count = __x._node_count;
		}
	}
	return *this;
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::_insert
(_Base_ptr __x, _Base_ptr __y, const value_type &__v)
{
	_Link_type _x = (_Link_type)__x;
	_Link_type _y = (_Link_type)__y;
	_Link_type _z;
	//参数_x为新值插入点，参数_y为插入点的父节点，参数_v为新值
	if (_y == _header || _x != 0 || _key_compare(_KeyOfValue()(__v), _key(_y)))
	{
		_z = _create_node(__v);
		_left(_y) = _z;
		if (_y == _header)
		{
			_root() = _z;
			_rightmost() = _z;
		}
		else if (_y == _leftmost())
		{
			_leftmost() = _z;
		}
	}
	else
	{
		_z = _create_node(__v);
		_right(_y) = _z;
		if (_y == _rightmost())
		{
			_rightmost() = _z;
		}
	}
	_parent(_z) = _y;
	_left(_z) = 0;
	_right(_z) = 0;
	_Rb_tree_rebalance(_z, _header->_parent);
	++_node_count;
	return iterator(_z);
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator 
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::_copy(_Link_type __x, _Link_type __p)
{
	_Link_type __top = _clone_node(__x);
	__top->_parent = __p;

	//try
	if (__x->_right)
		__top->_right = (_Link_type)_copy(_right(__x), __top)._node;
	__p = __top;
	__x = _left(__x);

	while (__x != 0)
	{
		_Link_type __y = _clone_node(__x);
		__p->_left = __y;
		__y->_parent = __p;
		if (__x->_right)
			__y->_right = (_Link_type)_copy(_right(__x), __y)._node;
		__p = __y;
		__x = _left(__x);
	}
	
	//unwind
	return __top;	
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
void _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::_erase(_Link_type x)
{
	while (x != 0)
	{
		_erase(_left(x));
		_Link_type y = (_Link_type)x->_right;
		_destroy_node(x);
		y = x;
	}
}


template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::insert_equal
(const value_type& __v)
{
	_Link_type __y = _header;
	_Link_type __x = _root();
	while (__x != 0)
	{
		__y = __x;
		__x = _key_compare(_KeyOfValue()(__v), _key(__x)) ? _left(__x) : _right(__x);
	}
	return _insert((_Base_ptr)__x, (_Base_ptr)__y, __v);
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
pair<typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator, bool> 
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::insert_unique
(const value_type& __v)
{
	_Link_type _y = _header;
	_Link_type _x = _root();
	bool _comp = true;
	while (_x != 0)
	{
		_y = _x;
		_comp = _key_compare(_KeyOfValue()(__v), _key(_x));
		_x = _comp ? _left(_x) : _right(_x);
	}
	
	iterator _j = iterator(_y);
	if (_comp)
	{
		if (_j == begin())
		{
			return pair<iterator, bool>(_insert((_Base_ptr)_x, (_Base_ptr)_y, __v), true);
		}
		else
		{
			_j--;
		}
	}
	if (_key_compare(_key((_Link_type)_j._node), _KeyOfValue()(__v)))
	{
		return pair<iterator, bool>(_insert((_Base_ptr)_x, (_Base_ptr)_y, __v), true);
	}
	return pair<iterator, bool>(_j, false);
}

template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc> ::insert_unique
(iterator __position, const value_type& __v)
{
	if (__position._node == _header->_left)
	{
		if (size() > 0 && _key_compare(_KeyOfValue()(__v), _key((_Link_type)__position._node)))
			return _insert((_Base_ptr)__position._node, (_Base_ptr)__position._node, __v);
		else
			return insert_unique(__v).first;
	}
	else if (__position._node == _header)
	{
		if (_key_compare(_key(_rightmost()), _KeyOfValue()(__v)))
			return _insert((_Base_ptr)0, (_Base_ptr)_rightmost(), __v);
		else
			return insert_unique(__v).first;
	}
	else
	{
		iterator __before = __position;
		--__before;
		if (_key_compare(_key((_Link_type)__before._node), _KeyOfValue()(__v))
			&& _key_compare(_KeyOfValue()(__v), _key((_Link_type)__position._node)))
		{
			if (_right((_Link_type)__before._node) == 0)
				return _insert((_Base_ptr)0, (_Base_ptr)__before._node, __v);
			else
				return _insert((_Base_ptr)__position._node, (_Base_ptr)__position._node, __v);
		}
		else
			return insert_unique(__v).first;
	}
}

template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc> ::insert_equal
(iterator __position, const value_type& __v)
{
	if (__position._node == _header->_left)
	{
		if (size() > 0 && _key_compare(_KeyOfValue()(__v), _key((_Link_type)__position._node)))
			return _insert((_Base_ptr)__position._node, (_Base_ptr)__position._node, __v);
		else
			return insert_equal(__v);
	}
	else if (__position._node == _header)
	{
		if (_key_compare(_key(_rightmost()), _KeyOfValue()(__v)))
			return _insert((_Base_ptr)0, (_Base_ptr)_rightmost(), __v);
		else
			return insert_equal(__v);
	}
	else
	{
		iterator __before = __position;
		--__before;
		if (_key_compare(_key((_Link_type)__before._node), _KeyOfValue()(__v))
			&& _key_compare(_KeyOfValue()(__v), _key((_Link_type)__position._node)))
		{
			if (_right((_Link_type)__before._node) == 0)
				return _insert((_Base_ptr)0, (_Base_ptr)__before._node, __v);
			else
				return _insert((_Base_ptr)__position._node, (_Base_ptr)__position._node, __v);
		}
		else
			return insert_equal(__v);
	}
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
void _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::erase(
	typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator __position)
{
	_Link_type __y = (_Link_type)_Rb_tree_rebalance_for_erase(__position._node,
																_header->_parent,
																_header->_left,
																_header->_right);
	_destroy_node(__y);
	--_node_count;
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
void _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::erase(iterator __first, iterator __last)
{
	if (__first == begin() && __last == end())
		clear();
	else
		while (__first != __last) 
			erase(__first++);
}


template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::size_type
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::erase(const key_type& __x)
{
	pair<iterator, iterator> __p = equal_range(__x);
	size_type __n = 0;
	_distance(__p.first, __p.second, __n);
	erase(__p.first, __p.second);
	return __n;
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::find(const key_type& __k)
{
	_Link_type __y = _header;
	_Link_type __x = _root();
	
	while (__x != 0)
	{
		//__x大于等于__k(左移)时才会移动__y;
		if (!_key_compare(_key(__x), __k))
		{
			__y = __x;
			__x = _left(__x);
		}
		else
			__x = _right(__x);
	}
	
	iterator __j = (iterator)__y;
	return (__j == end() || _key_compare(__k, _key(__j._node))) ?
		end() : __j;
}


template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::const_iterator
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::find(const key_type& __k) const
{
	_Link_type __y = _header;
	_Link_type __x = _root();

	while (__x != 0)
	{
		if (!_key_compare(_key(__x), __k))
		{
			__y = __x;
			__x = _left(__x);
		}
		else
			__x = _right(__x);
	}

	const_iterator __j = (const_iterator)__y;
	return (__j == end() || _key_compare(__k, _key(__j._node))) ?
		end() : __j;
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
void _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc> ::erase(const key_type* __first, const key_type* __last)
{
	while (__first != __last)
		erase(*__first++);
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::size_type
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::count(const key_type& __k) const
{
	pair<const_iterator, const_iterator> __p = equal_range(__k);
	size_type __n = 0;
	_distance(__p.first, __p.second, __n);
	return __n;
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::lower_bound(const key_type& __k)
{
	//不小于__k的第一个节点
	_Link_type __y = _header; 
	_Link_type __x = _root(); 

	while (__x != 0)
		if (!_key_compare(_key(__x), __k))
			__y = __x, __x = _left(__x);
		else
			__x = _right(__x);

	return iterator(__y);
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::const_iterator
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::lower_bound(const key_type& __k) const
{
	_Link_type __y = _header;
	_Link_type __x = _root();

	while (__x != 0)
		if (!_key_compare(_key(__x), __k))
			__y = __x, __x = _left(__x);
		else
			__x = _right(__x);

	return const_iterator(__y);
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::upper_bound(const key_type& __k)
{
	_Link_type __y = _header;
	_Link_type __x = _root();
	
	while (__x != 0)
	{
		//__x的_key大于__k(向左移动）才移动__y
		//所以_y是大于且最接近__K的节点
		if (_key_compare(__k, _key(__x)))
		{
			__y = __x;
			__x = _left(__x);
		}
		else
		{
			__x = _right(__x);
		}
	}
	return iterator(__y);
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::const_iterator
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::upper_bound(const key_type& __k) const
{
	_Link_type __y = _header;
	_Link_type __x = _root();

	while (__x != 0)
	{
		if (_key_compare(__k, _key(__x)))
		{
			__y = __x;
			__x = _left(__x);
		}
		else
		{
			__x = _right(__x);
		}
	}
	return const_iterator(__y);
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
pair<typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator,
	typename _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator>
_Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc> ::equal_range(const key_type& __k)
{
	return pair<iterator, iterator>(lower_bound(__k), upper_bound(__k));
}

template <class _Key, class _Value, class _KoV, class _Compare, class _Alloc>
pair<typename _Rb_tree<_Key, _Value, _KoV, _Compare, _Alloc>::const_iterator,
	typename _Rb_tree<_Key, _Value, _KoV, _Compare, _Alloc>::const_iterator>
_Rb_tree<_Key, _Value, _KoV, _Compare, _Alloc>::equal_range(const key_type& __k) const
{
	return pair<const_iterator, const_iterator>(lower_bound(__k), upper_bound(__k));
}

 int __black_count(__Rb_tree_node_base* __node, __Rb_tree_node_base* __root)
{
	if (__node == 0)
		return 0;
	else {
		int __bc = __node->_color == __rb_tree_black ? 1 : 0;
		if (__node == __root)
			return __bc;
		else
			return __bc + __black_count(__node->_parent, __root);
	}
}

template <class _Key, class _Value, class _KeyOfValue,
	class _Compare, class _Alloc>
bool _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__rb_verify() const
{
	if (_node_count == 0 || begin() == end())
		return _node_count == 0 && begin() == end() &&_header->_left == _header && _header->_right == _header;

	int __len = __black_count(_leftmost(), _root());
	for (const_iterator __it = begin(); __it != end(); ++__it) 
	{
		_Link_type __x = (_Link_type)__it._node;
		_Link_type __L = _left(__x);
		_Link_type __R = _right(__x);

		if (__x->_color == __rb_tree_red)
			if ((__L && __L->_color == __rb_tree_red) || (__R && __R->_color == __rb_tree_red))
				return false;
		if (__L && _key_compare(_key(__x), _key(__L)))
			return false;
		if (__R && _key_compare(_key(__R), _key(__x)))
			return false;

		if (!__L && !__R && __black_count(__x, _root()) != __len)
			//秒
			return false;
	}

	if (_leftmost() != __Rb_tree_node_base::_mininum(_root()))
		return false;
	if (_rightmost() != __Rb_tree_node_base::_maxinum(_root()))
		return false;

	return true;
}
template <class _InputIterator, class _Distance>
void _distance(_InputIterator __first, _InputIterator __last, _Distance& __n)
{
	while (__first != __last)
	{
		++__first;
		++__n;
	}
}
