#pragma once
#include "type_traits.h"
#include "stl_construct.h"
#include "stl_iterator_base.h"
#include "stl_algobase.h"
template<class ForwardIterator, class Size, class T>
ForwardIterator __uninitialized_fill_n_aux(ForwardIterator frist, Size  n, const T& x, __false_type)
{
	ForwardIterator cur = frist;
	for (; n > 0; --n, ++cur)
	{
		_Construct(&*cur, x);
	}
	return cur;
}
template<class ForwardIterator, class Size, class T>
ForwardIterator __uninitialized_fill_n_aux(ForwardIterator frist, Size  n, const T& x, __true_type)
{
	return fill_n(frist, n, x);
}

template<class ForwardIterator, class Size, class T, class T1>
ForwardIterator __uninitialized_fill_n(ForwardIterator frist, Size n, const T& x, T1*)
{
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	return  __uninitialized_fill_n_aux(frist, n, x, is_POD());
}
template<class ForwardIterator, class Size, class T>
ForwardIterator	uninitialized_fill_n(ForwardIterator frist, Size n, const T& x)
{
	return __uninitialized_fill_n(frist, n, x, value_type(frist));
}
///////////////////////////////////////////////////////////////////////////////////
template <class _InputIter, class _ForwardIter>
_ForwardIter __uninitialized_copy_aux(_InputIter __first, _InputIter __last,
	_ForwardIter __result, __false_type)
{
	_ForwardIter __cur = __result;
	for (; __first != __last; ++__first, ++__cur)
	{
		_Construct(&*__cur, *__first);
	}
	return __cur;
}
template <class _InputIter, class _ForwardIter>
_ForwardIter __uninitialized_copy_aux(_InputIter __first, _InputIter __last,
	_ForwardIter __result, __true_type)
{
	return copy(__first, __last, __result);
}
template <class _InputIter, class _ForwardIter, class _Tp>
_ForwardIter __uninitialized_copy(_InputIter __first, _InputIter __last,
	_ForwardIter __result, _Tp*)
{
	typedef typename __type_traits<_Tp>::is_POD_type _is_POD;
	return __uninitialized_copy_aux(__first, __last, __result, _is_POD());
}
template <class _InputIter, class _ForwardIter>
_ForwardIter uninitialized_copy(_InputIter __first, _InputIter __last,
	_ForwardIter __result)
{
	return __uninitialized_copy(__first, __last, __result, __VALUE_TYPE(__first));
}

