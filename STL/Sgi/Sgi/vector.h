#pragma once
#include "stl_alloc.h"
#include "stl_uninitialized.h"
template<class T, class Alloc =alloc>
class vector
{
public:
	typedef typename T				value_type;
	typedef			value_type *	pointer;
	typedef			value_type *	iterator;
	typedef const	value_type*		const_pointer;
	typedef const	value_type*		const_iterator;
	typedef			value_type&		reference;
	typedef	const	value_type&		const_reference;
	typedef			size_t			size_type;
	typedef			ptrdiff_t		difference_type;

protected:
	typedef simple_alloc<value_type, Alloc> data_allocator;
	iterator start;
	iterator finish;
	iterator end_of_storage;

	void insert_aux(iterator positon, const T& x);
	void deallocate()
	{
		if (start)
			data_allocator::deallocate(start, end_of_storage - start);
	}

	void fill_initialize(size_type n, const T& value)
	{
		start = allocate_and_fill(n, value);
		finish = start + n;
		end_of_storage = finish;
	}
public:
	iterator begin() { return start; }
	iterator begin() const { return start; }
	iterator end() { return finish; }
	iterator end()	 const { return finish; }
	size_type size() const
	{
		return size_type(end() - begin());
	}
	size_type capacity() const
	{
		return size_type(end_of_storage - begin());
	}
	bool empty() const
	{
		return (begin() == end());
	}
	reference operator[](size_type n)
	{
		return *(begin() + n);
	}
	const_reference operator[](size_type n) const 
	{ 
		return *(begin() + n);
	}
public:
	vector(const Alloc& __a = alloc)
		:start(0), end_of_storage(0), finish(0) {};
	vector(size_type n, const T& value)
	{
		fill_initialize(n, value);
	}
	vector(int n, const T& value)
	{
		fill_initialize(n, value);
	}
	vector(long n, const T& value)
	{
		fill_initialize(n, value);
	}
	explicit vector(size_type n)
	{
		fill_initialize(n, T());
	}
	vector(const vector<T, Alloc>& x) {
		start = allocate_and_copy(x.end() - x.begin(), x.begin(), x.end());
		finish = start + (x.end() - x.begin());
		end_of_storage = finish;
	}
	~vector()
	{
		destroy(start, finish);
		deallocate();
	}
public:
	reference front() const { return *(begin()); }
	reference back()  const { return *(end() - 1); }
	reference front() { return *(begin()); }
	reference back() { return *(end() - 1); }
	void push_back(const T& x)
	{
		if (finish != end_of_storage)
		{
			construct(finish++, x);
		}
		else
		{
			insert_aux(end(), x);
		}
	}
	void pop_back()
	{
		--finish;
		destroy(finish);
	}
	iterator erase(iterator position)
	{
		if (position + 1 != end())
		{
			copy(position + 1, finish, position);
		}
		--finish;
		destroy(finish);
		return position;
	}
	iterator erase(iterator first, iterator last)
	{
		iterator i = copy(last, finish, first);
		destroy(i, finish);
		finish = finish - (last - first);
		return first;
	}
	void resize(size_type new_size, const T&x)
	{
		if (new_size < size())
		{
			erase(begin() + new_size, end());
		}
		else
		{
			insert(end(), new_size - size(), x);
		}
	}
	void resize(size_type new_size)
	{
		resize(new_size, T());
	}
	void reserve(size_type n)
	{
		if (capacity() < n) {
			const size_type old_size = size();
			iterator tmp = allocate_and_copy(n, start, finish);
			destroy(start, finish);
			deallocate();
			start = tmp;
			finish = tmp + old_size;
			end_of_storage = start + n;
		}
	}
	void clear()
	{
		erase(begin(), end());
	}
	void swap(vector<T, Alloc>& x)
	{
		STD::swap(start, x.start);
		STD::swap(finish, x.finish);
		STD::swap(end_of_storage, x.end_of_storage);
	}
	void insert(iterator position, size_type n, const T&x);
protected:
	iterator allocate_and_fill(size_type n, const T& x)
	{
		iterator result = data_allocator::allocate(n);
		uninitialized_fill_n(result, n, x);
		return result;
	}
	iterator allocate_and_copy(size_type n, const_iterator first, const_iterator last)
	{
		iterator result = data_allocator::allocate(n);
		uninitialized_copy(first, last, result);
		return result;
	}
	void _deallocate(T* __p, size_t __n)
	{
		data_allocator::deallocate(__p, __n);
	}
};
template<class T, class Alloc>
void vector<T, Alloc>::insert(iterator position, size_type n, const T&x)
{
	if (n != 0)
	{
		if (size_type(end_of_storage - finish) >= n)
		{
			T x_copy = x;
			const size_type elems_after = finish - position;
			iterator old_finish = finish;
			if (elems_after > n)
			{
				copy(finish - n, finish, finish);
				finish = finish + n;
				copy_backward(position, old_finish - n, old_finish);
				fill(position, position + n, x_copy);
			}
			else
			{
				uninitialized_fill_n(finish, n - elems_after, x_copy);
				finish += n - elems_after;
				copy(position, old_finish, finish);
				finish += elems_after;
				fill(position, old_finish, x_copy);
			}
		}
		else
		{
			const size_type old_size = size();
			const size_type len = old_size + max(size(), n);
			iterator new_start = data_allocator::allocate(len);
			iterator new_finish = new_start;
			//try
			new_finish = uninitialized_copy(start, position, new_start);
			new_finish = uninitialized_fill_n(new_finish, n, x);
			new_finish = uninitialized_copy(position, finish, new_finish);
			//catch(action)
			destroy(start, finish);
			_deallocate(start, end_of_storage - start);
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start + len;
		}
	}
}

template<class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator positon, const T &x)
{
	if (finish != end_of_storage)
	{
		construct(finish, *(finish - 1));
		++finish;
		T x_copy = x;
		copy_backward(positon, finish - 2, finish - 1);
		*positon = x_copy;
	}
	else
	{
		const size_type old_size = size();
		const size_type len = old_size != 0 ? 2 * old_size : 1;
		iterator new_start = data_allocator::allocate(len);
		iterator new_finish = new_start;

		//try
		//{
		new_finish = uninitialized_copy(start, positon, new_start);
		construct(new_finish, x);
		++new_finish;
		new_finish = uninitialized_copy(positon, finish, new_finish);
		//}
		//catch().....................
		destroy(begin(), end());
		deallocate();

		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + len;
	}
}