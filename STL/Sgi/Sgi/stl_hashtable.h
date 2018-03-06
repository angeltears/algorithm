#pragma once
#include "stl_algobase.h"
#include "stl_alloc.h"
#include "stl_construct.h"
#include "vector.h"
#include "stl_function.h"
#include "stl_iterator.h"
#include "stl_iterator_base.h"
#include "stl_algo.h"
#include "stl_hash_function.h"
#include "config.h"
#include "stl_pair.h"
template<class _Val>
struct _hashtable_node
{
	_hashtable_node* _next;
	_Val _val;
};


template <class _Val, class _Key, class _HashFcn,class _ExtractKey, class _EqualKey, class _Alloc = alloc>
	class hashtable;

template <class _Val, class _Key, class _HashFcn,class _ExtractKey, class _EqualKey, class _Alloc>
	struct _hashtable_iterator;

template <class _Val, class _Key, class _HashFcn,class _ExtractKey, class _EqualKey, class _Alloc>
	struct _hashtable_const_iterator;

template <class _Val, class _Key, class _HashFcn, class _ExtractKey, class _EqualKey, class _Alloc>
struct _hashtable_iterator
{
	typedef hashtable<_Val, _Key, _HashFcn,
					_ExtractKey, _EqualKey, _Alloc>      
		_hashtable;
	typedef typename _hashtable_iterator<_Val, _Key, _HashFcn,
								_ExtractKey, _EqualKey, _Alloc> 
		iterator;
	typedef typename _hashtable_const_iterator<_Val, _Key, _HashFcn,
									_ExtractKey, _EqualKey, _Alloc>
		const_iterator;
	typedef _hashtable_node<_Val> _node;

	typedef forward_iterator_tag iterator_category;
	typedef _Val				 value_type;
	typedef ptrdiff_t            difference_type;
	typedef size_t				 size_type;
	typedef _Val&				 reference;
	typedef _Val*				 pointer;

	_node* _cur;
	_hashtable* _ht;

	_hashtable_iterator(_node *__n, _hashtable* __tab)
		:_cur(__n), _ht(__tab) {};
	_hashtable_iterator(const iterator& __it)
		: _cur(__it._cur), _ht(__it._ht) {}
	_hashtable_iterator() {}
	reference operator*() const 
	{ 
		return _cur->_val; 
	}
	pointer operator->() const 
	{ 
		return &(operator*()); 
	}
	iterator& operator++();
	iterator operator++(int);
	bool operator==(const iterator& __it) const
	{
		return _cur == __it._cur;
	}
	bool operator!=(const iterator& __it) const
	{
		return _cur != __it._cur;
	}
};


template <class _Val, class _Key, class _HashFcn,
	class _ExtractKey, class _EqualKey, class _Alloc>
struct _hashtable_const_iterator 
{
	typedef hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>
		_hashtable;
	typedef typename _hashtable_iterator<_Val, _Key, _HashFcn,
		_ExtractKey, _EqualKey, _Alloc>
		iterator;
	typedef typename _hashtable_const_iterator<_Val, _Key, _HashFcn,
		_ExtractKey, _EqualKey, _Alloc>
		const_iterator;
	typedef _hashtable_node<_Val> _node;

	typedef forward_iterator_tag	iterator_category;
	typedef _Val					value_type;
	typedef ptrdiff_t				difference_type;
	typedef size_t					size_type;
	typedef const _Val&				reference;
	typedef const _Val*				pointer;

	const _node* _cur;
	const _hashtable* _ht;

	_hashtable_const_iterator(const _node* __n, const _hashtable* __tab)
		: _cur(__n), _ht(__tab) {}
	_hashtable_const_iterator() {}
	_hashtable_const_iterator(const iterator& __it)
		: _cur(__it._cur), _ht(__it._ht) {}
	reference operator*() const 
	{ 
		return _cur->_val; 
	}
	pointer operator->() const 
	{ 
		return &(operator*()); 
	}
	const_iterator& operator++();
	const_iterator operator++(int);
	bool operator==(const const_iterator& __it) const
	{
		return _cur == __it._cur;
	}
	bool operator!=(const const_iterator& __it) const
	{
		return _cur != __it._cur;
	}
};

enum { __stl_num_primes = 28 };

static const unsigned long __stl_prime_list[__stl_num_primes] =
{
	53ul,         97ul,         193ul,       389ul,       769ul,
	1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
	49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
	1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
	50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};

unsigned long __stl_next_prime(unsigned long __n)
{
	const unsigned long* __first = __stl_prime_list;
	const unsigned long* __last = __stl_prime_list + (int)__stl_num_primes;
	const unsigned long* pos = lower_bound(__first, __last, __n);
	return pos == __last ? *(__last - 1) : *pos;
}


template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
class hashtable;

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
bool operator==(const hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>& __ht1,
				const hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>& __ht2);


template  <class _Val, class _Key, class _HashFcn,
		   class _ExtractKey, class _EqualKey, class _Alloc>
	class hashtable
{
public:
	friend struct
		_hashtable_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>;
	friend struct
		_hashtable_const_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>;
	typedef typename _hashtable_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>
		iterator;
	typedef typename _hashtable_const_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>
		const_iterator;
public:
	typedef _Key			  key_type;
	typedef _Val			  value_type;
	typedef _HashFcn		  hasher;
	typedef _EqualKey		  key_equal;

	typedef size_t            size_type;
	typedef ptrdiff_t         difference_type;
	typedef value_type*       pointer;
	typedef const value_type* const_pointer;
	typedef value_type&       reference;
	typedef const value_type& const_reference;

	hasher hash_funct() const
	{
		return _hash;
	}
	key_equal key_eq() const
	{
		return _equals;
	}
private:
	typedef _hashtable_node<_Val> _node;
public:
	typedef _Alloc            allocator_type;
	allocator_type get_allocator() const
	{
		return allocator_type();
	}
private:
	typedef simple_alloc<_node, _Alloc> _node_allocator_type;
	_node*  _get_node()
	{
		return _node_allocator_type::allocate(1);
	}
	void _put_node(_node* __p)
	{
		return _node_allocator_type::deallocate(__p, 1);
	}
private:
	hasher					_hash;
	key_equal				_equals;
	_ExtractKey             _get_key;
	vector<_node*, _Alloc>  _buckets;
	size_type               _num_elements;
public:
	hashtable(size_type __n,
		const _HashFcn&    __hf,
		const _EqualKey&   __eql,
		const _ExtractKey& __ext,
		const allocator_type& __a = allocator_type())
		:_hash(__hf),
		_equals(__eql),
		_get_key(__ext),
		_buckets(__a),
		_num_elements(0)
	{
		_initialize_buckets(__n);
	}

	hashtable(size_type __n,
		const _HashFcn&    __hf,
		const _EqualKey&   __eql,
		const allocator_type& __a = allocator_type())
		:_hash(__hf),
		_equals(__eql),
		_buckets(__a),
		_num_elements(0)
	{
		_initialize_buckets(__n);
	}

	hashtable(const hashtable& __ht)
		:_hash(__ht._hash),
		_equals(__ht._equals),
		_get_key(__ht._get_key),
		_buckets(__ht.get_allocator()),
		_num_elements(0)
	{
		_copy_from(__ht);
	}

	hashtable& operator= (const hashtable& __ht)
	{
		if (&__ht != this) {
			clear();
			_hash = __ht._hash;
			_equals = __ht._equals;
			_get_key = __ht._get_key;
			_copy_from(__ht);
		}
		return *this;
	}

	~hashtable() { clear(); }
public:
	size_type size() const
	{
		return _num_elements;
	}
	size_type max_size() const
	{
		return size_type(-1);
	}
	bool empty() const
	{
		return size() == 0;
	}
	void swap(hashtable& __ht)
	{
		STD::swap(_hash, __ht._hash);
		STD::swap(_get_key, __ht._get_key);
		STD::swap(_equals, __ht._equals);
		_buckets.swap(__ht._buckets);
		STD::swap(_num_elements, __ht._num_elements);
	}
	iterator begin()
	{
		for (size_type __n = 0; __n < _buckets.size(); ++__n)
			if (_buckets[__n])
				return iterator(_buckets[__n], this);
		return end();
	}
	iterator end()
	{ 
		return iterator(0, this);
	}
	const_iterator begin() const
	{
		for (size_type __n = 0; __n < size(); __n++)
			if (_buckets[__n])
				return const_iterator(_buckets[__n], this);
		return end();
	}
	const_iterator end() const
	{
		return const_iterator(0, this);
	}
public:
	void resize(size_type __num_elements_hint);
	size_type bucket_size() const
	{
		return _buckets.size();
	}
	size_type max_bucket_count() const
	{
		return __stl_prime_list[(int)__stl_num_primes - 1];
	}
	size_type elems_in_bucket(size_type __bucket) const
	{
		size_type _result = 0;
		for (_node * __cur = _buckets[__bucket]; __cur; __cur = __cur->_next)
			_result += 1;
		return _result;
	}
	pair<iterator, bool> insert_unique(const value_type& __obj)
	{
		resize(_num_elements + 1);
		return insert_unique_noresize(__obj);
	}
	iterator insert_equal(const value_type& __obj)
	{
		resize(_num_elements + 1);
		return insert_equal_noresize(__obj);
	}
	void insert_unique(const value_type* __f, const value_type* __l)
	{
		size_type __n = __l - __f;
		resize(_num_elements + __n);
		for (; __n > 0; --__n, ++__f)
		{
			insert_unique_noresize(*__f);
		}
	}
	void insert_equal(const value_type* __f, const value_type* __l)
	{
		size_type __n = __l - __f;
		resize(_num_elements + __n);
		for (; __n > 0; --__n, ++__f)
		{
			insert_equal_noresize(*__f);
		}
	}
	void insert_unique(const_iterator __f, const_iterator __l)
	{
		size_type __n = 0;
		distance(__f, __l, __n);
		resize(_num_elements + __n);
		for (; __n > 0; --__n, ++__f)
		{
			insert_unique_noresize(*__f);
		}
	}
	void insert_euqal(const_iterator __f, const_iterator __l)
	{
		size_type __n = 0;
		distance(__f, __l, __n);
		resize(_num_elements + __n);
		for (; __n > 0; --__n, ++__f)
		{
			insert_euqal_noresize(*__f);
		}
	}
private:
	pair<iterator, bool> insert_unique_noresize(const value_type& __obj);

	iterator insert_equal_noresize(const value_type& __obj);
public:
	reference find_or_insert(const value_type& __obj);

	iterator find(const key_type& __key)
	{
		size_type __n = _bkt_num_key(__key);
		_node* _first;
		for (_first = _buckets[__n]; _first && !_equals(_get_key(_first->_val), __key); 
			_first = _first->_next);
		return iterator(_first, this);
	}

	const_iterator find(const key_type& __key) const
	{
		size_type __n = _bkt_num_key(__key);
		const _node* _first;
		for (_first = _buckets[__n]; _first && !_equals(_get_key(_first->_val), __key);
			_first = _first->_next);
		return const_iterator(_first, this);
	}

	size_type count(const key_type& __key) const
	{
		size_type __n = _bkt_num_key(__key);
		size_type _result = 0;
		const _node* _cur;
		for (_cur = _buckets[__n]; _cur; _cur = _cur->_next)
		{
			if (_equals(_get_key(_cur->_val), __key))
			{
				++_result;
			}
		}
		return _result;
	}
public:
	pair<iterator, iterator> equal_range(const key_type& __key);

	pair<const_iterator, const_iterator> equal_range(const key_type& __key) const;

	size_type erase(const key_type& __key);
	void erase(const iterator& __it);
	void erase(iterator __first, iterator __last);

	void erase(const const_iterator& __it);
	void erase(const_iterator __first, const_iterator __last);

	void clear();
private:
	size_type _next_size(size_type __n) const
	{
		return __stl_next_prime(__n);
	}
	void _initialize_buckets(size_type __n)
	{
		size_type __n_bucket = _next_size(__n);
		_buckets.reserve(__n_bucket);
		_buckets.insert(_buckets.end(), __n_bucket, (_node*)0);
		_num_elements = 0;
	}
	size_type _bkt_num_key(const size_type &__key) const
	{
		return _bkt_num_key(__key, _buckets.size());
	}
	size_type _bkt_num(const value_type& __obj) const
	{
		return _bkt_num_key(_get_key(__obj));
	}
	size_type _bkt_num_key(const key_type& __key, size_t __n) const
	{
		return __key % __n;
	}
	size_type _bkt_num(const value_type& __obj, size_t __n) const
	{
		return _bkt_num_key(_get_key(__obj), __n);
	}
	_node* _new_node(const value_type& __obj)
	{
		_node* __n = _get_node();
		__n->_next = 0;
		__STL_TRY
		{
			construct(&__n->_val, __obj);
			return __n;
		}
		__STL_UNWIND(_put_node(__n));
	}
	void _deallocate_node(_node* __n)
	{
		destroy(&__n->_val);
		_put_node(__n);
	}
	void _erase_bucket(const size_type __n, _node* __first, _node* __last);
	void _erase_bucket(const size_type __n, _node* __last);
	void _copy_from(const hashtable& __ht);
};

template <class _Val, class _Key, class _HF, class _ExK, class _EqK,
	class _All>
_hashtable_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>&
_hashtable_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>::operator++()
{
	const _node* __old = _cur;
	_cur = _cur->_next;
	if (!_cur)
	{
		size_type __bucket = _ht->_bkt_num(__old->_val);
		while (!_cur && ++__bucket < _ht->_buckets.size())
			_cur = _ht->_buckets[__bucket];
	}
	return *this;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK,
	class _All>
_hashtable_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>
_hashtable_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>::operator++(int)
{
	iterator __tmp = *this;
	++*this;
	return __tmp;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK,
	class _All>
_hashtable_const_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>&
_hashtable_const_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>::operator++()
{
	const _node* _old = _cur;
	_cur = _cur->_next;
	if (!_cur)
	{
		size_type __bucket = _ht->_bkt_num(_old->_val);
		while (!_cur && ++__bucket < _ht->_buckets.size())
			_cur = _ht->_buckets[__bucket];
	}
	return *this;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK,
	class _All>
_hashtable_const_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>
_hashtable_const_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>::operator++(int)
{
	const_iterator __tmp = *this;
	++*this;
	return __tmp;
}

template  <class _Val, class _Key, class _HashFcn,
	class _ExtractKey, class _EqualKey, class _Alloc>
pair<_hashtable_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>, bool>
hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>
::insert_unique_noresize(const value_type& _obj)
{
	const size_type _n = _bkt_num(_obj);
	_node* _first = _buckets[_n];
	for (_node* _cur = _first; _cur; _cur = _cur->_next)
	{
		if (_equals(_get_key(_cur->_val), _get_key(_obj)))
			return pair<iterator, bool>(iterator(_cur, this), false);
	}

	_node *_tmp = _new_node(_obj);
	_tmp->_next = _first;
	_buckets[_n] = _tmp;
	++_num_elements;
	return pair<iterator, bool>(iterator(_tmp, this), true);
}

template  <class _Val, class _Key, class _HashFcn,
	class _ExtractKey, class _EqualKey, class _Alloc>
_hashtable_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>
hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>
::insert_equal_noresize(const value_type& _obj)
{
	const size_type _n = _bkt_num_key(_obj);
	_node* _first = _buckets[_n];
	for (_node* _cur = _first; _cur; _cur = _cur->_next)
	{
		if (_equals(_get_key(_cur->_val), _get_key(_obj)))
		{
			_node* _tmp = _new_node(_obj);
			_tmp->_next = _cur->_next;
			_cur->_next = _tmp;
			++_num_elements;
			return iterator(_tmp, this);
		}
	}
	_node* _tmp = _new_node(_obj);
	_tmp->_next = _first;
	_buckets[_n] = _tmp;
	++_num_elements;
	return iterator(_tmp, this);
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
_Val& hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::find_or_insert(const value_type& __obj)
{
	resize(_num_elements + 1);
	size_type __n = _bkt_num(__obj);
	_node* _cur;

	for (_cur = _buckets[__obj]; _cur; _cur = _cur->_next)
	{
		if (_equals(_get_key(_cur->_val), _get_key(__obj)))
		{
			return _cur->_val;
		}
	}
	
	_node* _tmp = _new_node(__obj);
	_tmp->_next = _buckets[__n];
	_buckets[__n] = _tmp;
	++_num_elements;
	return _tmp->_val;
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
pair<_hashtable_iterator<_Val, _Key, _HF, _Ex, _Eq, _All>,
	 _hashtable_iterator<_Val, _Key, _HF, _Ex, _Eq, _All>>
hashtable<_Val, _Key, _HF, _Ex, _Eq, _All> ::equal_range(const key_type& __key) 
{
	typedef pair<iterator, iterator> _Pill;
	size_type __n = _bkt_num_key(__key);

	for (_node* __first = _buckets[__n]; __first; __first = __first->_next)
	{
		if (_equals(_get_key(__first->_val), __key))
		{
			for (_node* __end = __first->_next; __end; __end = __end = __end->_next)
			{
				if (!_equals(_get_key(__end->_val), __key))
				{
					return _Pill(iterator(__first, this), iterator(__end, this));
				}
			}
			for (size_type __m = __n + 1; __m < _buckets.size(); ++__m)
			{
				if (_buckets[__m]);
				{
					return _Pill(iterator(__first, this), iterator(_buckets[__m], this));
				}
			}
			return  _Pill(iterator(__first, this), end());
		}
	}
	return _Pill(end(), end());
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
pair<_hashtable_const_iterator<_Val, _Key, _HF, _Ex, _Eq, _All>,
	 _hashtable_const_iterator<_Val, _Key, _HF, _Ex, _Eq, _All>>
hashtable<_Val, _Key, _HF, _Ex, _Eq, _All> ::equal_range(const key_type& __key) const
{
	typedef pair<const_iterator, const_iterator> _Pill;
	size_type __n = _bkt_num_key(__key);
	
	for (_node* __first = _buckets[__n]; __first; __first = __first->_next)
	{
		if (_equals(_get_key(__first->_val), __key))
		{
			for (_node* __end = _buckets[__n]; __end; __end = __end = __end->_next)
			{
				if (_equals(_get_key(__end->_val), __key))
				{
					return _Pill(const_iterator(__first, this), const_iterator(__end, this));
				}
			}
			return _Pill(const_iterator(__first, this), end());
		}
	}
	return _Pill(begin(), end());
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
size_t hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::erase(const key_type& __key)
{
	const size_type __n = _bkt_num_key(__key);
	_node* __first = _buckets[__n];
	size_type __erased = 0;

	if (__first)
	{
		_node* __cur = __first;
		_node* __next = __cur->_next;
		while (__next)
		{
			if (_equals(_get_key(__next->_val), __key))
			{
				__cur->_next = __next->_next;
				_deallocate_node(__next);
				__next = __cur->_next;
				--_num_elements;
				++__erased;
			}
			else
			{
				__cur = __cur->_next;
				__next = __cur->_next;
			}
		}

		if (_equals(_get_key(__first->_val), __key))
		{
			_buckets[__n] = __first->_next;
			_deallocate_node(__first);
			--_num_elements;
			++__erased;
		}
	}
	return __erased;
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::erase(const iterator& __it)
{
	_node* __p = __it._cur;
	if (__p)
	{
		size_type __n = _bkt_num_key(__p->_val);
		_node* __cur = _buckets[__n];
		
		if (__cur == __p)
		{
			_buckets[__n] = __cur->_next;
			_deallocate_node(__cur);
			--_num_elements;
		}
		else
		{
			_node* __next = __cur->_next;
			while (__next)
			{
				if (__next == __p)
				{
					__cur->_next = __next->_next;
					_deallocate_node(__next);
					--_num_elements;
					break;
				}
				else
				{
					__cur = __cur->_next;
					__next = __cur->_next;
				}
			}
		}
	}
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>
::erase(iterator __first, iterator __last)
{
	size_type __f_bucket = __first._cur ? 
		_bkt_num(__first._cur->_val) : _buckets.size();
	size_type __l_bucket = __last._cur ? 
		_bkt_num(__last._cur->_val) : _buckets.size();

	if (__first._cur == __last._cur)
		return;
	else if (__f_bucket == __l_bucket)
		_erase_bucket(__f_bucket, __first._cur, __last._cur);
	else
	{
		_erase_bucket(__f_bucket, __first._cur, 0);
		for (size_type __n = __f_bucket + 1; __n != __l_bucket; __n++)
		{
			_erase_bucket(__n, 0);
		}
		if (__l_bucket != _buckets.size())
			_erase_bucket(__l_bucket, __last._cur);
	}

}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::erase
(const_iterator __first, const_iterator __last)
{
	erase(iterator(const_cast<_node*>(__first._M_cur),
		  const_cast<hashtable*>(__first._M_ht)),
		  iterator(const_cast<_node*>(__last._M_cur),
		  const_cast<hashtable*>(__last._M_ht)));
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
inline void
hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::erase(const const_iterator& __it)
{
	erase(iterator(const_cast<_node*>(__it._cur),
		const_cast<hashtable*>(__it._ht)));
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::clear()
{
	for (size_type __i = 0; __i < _buckets.size(); ++__i)
	{
		_node* __cur = _buckets[__i];
		while (__cur != 0) 
		{
			_node* __next = __cur->_next;
			_deallocate_node(__cur);
			__cur = __next;
		}
		_buckets[__i] = 0;
	}
	_num_elements = 0;
}


template  <class _Val, class _Key, class _HashFcn,
	class _ExtractKey, class _EqualKey, class _Alloc>
void hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>
::resize(size_type _num_elements_hint)
{
	size_type _old_n = _buckets.size();
	if (_old_n < _num_elements_hint)
	{
		const size_type _n = _next_size(_num_elements_hint);
		if (_n > _old_n)
		{
			vector<_node*, alloc> _tmp(_n, (_node*)0);
			//__STL_TRY
			//{
			for (size_type _bucket = 0; _bucket < _old_n; ++_bucket)
			{
				_node* _first = _buckets[_bucket];
				while (_first)
				{
					size_type _new_bucket = _bkt_num(_first->_val, _n);
					_buckets[_bucket] = _first->_next;
					_first->_next = _tmp[_new_bucket];
					_tmp[_new_bucket] = _first;
					_first = _buckets[_bucket];         //Í·²åÍ·³ö
				}
			}
				_buckets.swap(_tmp);
			//}
		}
	}
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>
::_erase_bucket(const size_type __n, _node* __first, _node* __last)
{
	_node* __cur = _buckets[__n];
	if (__cur == __first)
	{
		_erase_bucket(__n, __last);
	}
	else
	{
		_node*__next = __cur;
		for (; __next != __first; __next = __next->_next);
		while (__next != __last)
		{
			__cur->_next = __next->_next;
			_deallocate_node(__next);
			___next = __cur->_next;
			--_num_elements;
		}
	}
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>
::_erase_bucket(const size_type __n, _node* __last)
{
	_node* __cur = _buckets[__n];
	while (__cur != __last) {
		_node* __next = __cur->_next;
		_delete_node(__cur);
		__cur = __next;
		_buckets[__n] = __cur;
		--_num_elements;
	}
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::_copy_from(const hashtable& __ht)
{
	_buckets.clear();
	_buckets.resize(__ht._buckets.size());
	_buckets.insert(_buckets.end(), __ht._buckets.size(), (_node*)0);
	__STL_TRY
	{
		for (size_type __i = 0; __i < __ht._buckets.size(); ++__i)
		{
			_node* __cur = __ht._buckets[__i];
			if (__cur)
			{
				_node* __copy = _new_node(__cur->_val);
				_buckets[__i] = __copy;
	
				for (_node* __next = __cur->_next; __next; __cur = __next, __next = __cur->_next)
				{
					__copy->_next = _new_node(__next->_val);
					__copy = __copy->_next;
				}
			}
		}
		_num_elements = __ht._num_elements;
	}
	__STL_UNWIND(clear());
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK,
	class _All>
forward_iterator_tag iterator_category(const _hashtable_const_iterator<_Val, _Key, _HF,
		_ExK, _EqK, _All>&)
{
	return forward_iterator_tag();
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK,
	class _All>
	typename forward_iterator_tag iterator_category(const _hashtable_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>&)
{
	return forward_iterator_tag();
}