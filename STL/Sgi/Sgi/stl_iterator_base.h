#pragma once

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class _Tp, class _Distance> 
struct input_iterator {
	typedef input_iterator_tag iterator_category;
	typedef _Tp                value_type;
	typedef _Distance          difference_type;
	typedef _Tp*               pointer;
	typedef _Tp&               reference;
};

struct output_iterator {
	typedef output_iterator_tag iterator_category;
	typedef void                value_type;
	typedef void                difference_type;
	typedef void                pointer;
	typedef void                reference;
};

template <class _Tp, class _Distance> 
struct forward_iterator {
	typedef forward_iterator_tag iterator_category;
	typedef _Tp                  value_type;
	typedef _Distance            difference_type;
	typedef _Tp*                 pointer;
	typedef _Tp&                 reference;
};


template <class _Tp, class _Distance> 
struct bidirectional_iterator {
	typedef bidirectional_iterator_tag iterator_category;
	typedef _Tp                        value_type;
	typedef _Distance                  difference_type;
	typedef _Tp*                       pointer;
	typedef _Tp&                       reference;
};

template <class _Tp, class _Distance>
struct random_access_iterator {
	typedef random_access_iterator_tag iterator_category;
	typedef _Tp                        value_type;
	typedef _Distance                  difference_type;
	typedef _Tp*                       pointer;
	typedef _Tp&                       reference;
};

template <class _Tp, class _Distance>
input_iterator_tag iterator_category(const input_iterator<_Tp, _Distance>&)
{
	return input_iterator_tag();
}

output_iterator_tag iterator_category(const output_iterator&)
{
	return output_iterator_tag();
}

template <class _Tp, class _Distance>
forward_iterator_tag iterator_category(const forward_iterator<_Tp, _Distance>&)
{
	return forward_iterator_tag();
}

template <class _Tp, class _Distance>
bidirectional_iterator_tag iterator_category(const bidirectional_iterator<_Tp, _Distance>&)
{
	return bidirectional_iterator_tag();
}

template <class _Tp, class _Distance>
random_access_iterator_tag iterator_category(const random_access_iterator<_Tp, _Distance>&)
{
	return random_access_iterator_tag();
}

template <class _Tp>
random_access_iterator_tag iterator_category(const _Tp*)
{
	return random_access_iterator_tag();
}

template <class _Tp, class _Distance>
_Tp* value_type(const input_iterator<_Tp, _Distance>&)
{
	return (_Tp*)(0);
}

template <class _Tp, class _Distance>
_Tp* value_type(const forward_iterator<_Tp, _Distance>&)
{
	return (_Tp*)(0);
}

template <class _Tp, class _Distance>
 _Tp* value_type(const bidirectional_iterator<_Tp, _Distance>&)
{
	return (_Tp*)(0);
}

template <class _Tp, class _Distance>
 _Tp* value_type(const random_access_iterator<_Tp, _Distance>&)
{
	return (_Tp*)(0);
}

template <class _Tp>
 _Tp* value_type(const _Tp*) { return (_Tp*)(0); }

template <class _Tp, class _Distance>
_Distance* distance_type(const input_iterator<_Tp, _Distance>&)
{
	return (_Distance*)(0);
}

template <class _Tp, class _Distance>
_Distance* distance_type(const forward_iterator<_Tp, _Distance>&)
{
	return (_Distance*)(0);
}

template <class _Tp, class _Distance>
 _Distance* distance_type(const bidirectional_iterator<_Tp, _Distance>&)
{
	return (_Distance*)(0);
}

template <class _Tp, class _Distance>
_Distance* distance_type(const random_access_iterator<_Tp, _Distance>&)
{
	return (_Distance*)(0);
}

template <class _Tp>
ptrdiff_t* distance_type(const _Tp*) 
{
	return (ptrdiff_t*)(0);
}


#define __ITERATOR_CATEGORY(__i) iterator_category(__i)
#define __DISTANCE_TYPE(__i)     distance_type(__i)
#define __VALUE_TYPE(__i)        value_type(__i)


template <class _InputIterator, class _Distance>
void __distance(_InputIterator __first, _InputIterator __last, _Distance& __n, input_iterator_tag)
{
	while (__first != __last)
	{ 
		++__first;
		++__n;
	}
}

template <class _RandomAccessIterator, class _Distance>
void __distance(_RandomAccessIterator __first,_RandomAccessIterator __last, _Distance& __n, random_access_iterator_tag)
{
	//__STL_REQUIRES(_RandomAccessIterator, _RandomAccessIterator);
	__n += __last - __first;
}

template <class _InputIterator, class _Distance>
void distance(_InputIterator __first, _InputIterator __last, _Distance& __n)
{
	__STL_REQUIRES(_InputIterator, _InputIterator);
	__distance(__first, __last, __n, iterator_category(__first));
}


