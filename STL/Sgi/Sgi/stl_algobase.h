#pragma once
#include "concept_checks.h"
#include "stl_iterator_base.h"
#include <memory.h>
namespace STD
{
	template <class _Tp>
	void swap(_Tp& __a, _Tp& __b) {
		__STL_REQUIRES(_Tp, _Assignable);
		_Tp __tmp = __a;
		__a = __b;
		__b = __tmp;
	}
};
///////////////////////////////////////////////////////////////
template <class _InputIter1, class _InputIter2>
bool equal(_InputIter1 __first1, _InputIter1 __last1,
	_InputIter2 __first2) {
	for (; __first1 != __last1; ++__first1, ++__first2)
		if (*__first1 != *__first2)
			return false;
	return true;
}
template <class _InputIter1, class _InputIter2, class _BinaryPredicate>
bool equal(_InputIter1 __first1, _InputIter1 __last1,
	_InputIter2 __first2, _BinaryPredicate __binary_pred) 
{
	for (; __first1 != __last1; ++__first1, ++__first2)
		if (!__binary_pred(*__first1, *__first2))
			return false;
	return true;
}
//////////////////////////////////////////////////////////////
template <class _ForwardIter, class _Tp>
void fill(_ForwardIter __first, _ForwardIter __last, const _Tp& __value)
{
	//__STL_REQUIRES(_ForwardIter, _Mutable_ForwardIterator);
	for (; __first != __last; ++__first)
	{
		*__first = __value;
	}
}
template <class _OutputIter, class _Size, class _Tp>
_OutputIter fill_n(_OutputIter __first, _Size __n, const _Tp& __value) {
//	__STL_REQUIRES(_OutputIter, _OutputIterator);
	for (; __n > 0; --__n, ++__first)
		*__first = __value;
	return __first;
}
////////////////////////////////////////////////////////////////////////////////////////
template <class _RandomAccessIter, class _BidirectionalIter, class _Distance>
_BidirectionalIter __copy_backward(_RandomAccessIter __first, _RandomAccessIter __last,
	_BidirectionalIter __result, bidirectional_iterator_tag, _Distance*)
{
	while (__first != __last)
	{
		*--__result = *--__last;
	}
	return result;
}
template <class _RandomAccessIter, class _BidirectionalIter, class _Distance>
 _BidirectionalIter __copy_backward(_RandomAccessIter __first,_RandomAccessIter __last,
	 _BidirectionalIter __result, random_access_iterator_tag, _Distance*)
{
	 for (_Distance n = __last - __first; n > 0; n--)
	 {
		 *--__result = *--__last;
	 }
	 return __result;
}
template<class _BI1, class _BI2>
_BI2 copy_backward(_BI1 __first, _BI1 __last, _BI2 __result)
{
	return __copy_backward(__first, __last, __result, __ITERATOR_CATEGORY(__first), __DISTANCE_TYPE(__first));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
template <class _InputIter, class _OutputIter, class _Distance>
_OutputIter __copy(_InputIter __first, _InputIter __last,
	_OutputIter __result, input_iterator_tag,  _Distance*)
{
	for (; __first != __last; ++__result, ++__first)
		*__result = *__first;
	return __result;
}
template <class _RandomAccessIter, class _BidirectionalIter, class _Distance>
_BidirectionalIter __copy(_RandomAccessIter __first, _RandomAccessIter __last,
	_BidirectionalIter __result, random_access_iterator_tag, _Distance*)
{
	for (_Distance n = __last - __first; n > 0; n--)
	{
		*__result = *__first;
		__result++;
		__first++;
	}
	return __result;
}
template <class _InputIter, class _OutputIter>
 _OutputIter copy(_InputIter __first, _InputIter __last, _OutputIter __result)
{
	 return __copy(__first, __last, __result, __ITERATOR_CATEGORY(__first), __DISTANCE_TYPE(__first));
}
//////////////////////////////////////////////////////////////////////////////////
 template <class _Tp>
 const _Tp& max(const _Tp& __a, const _Tp& __b) {
	 //__STL_REQUIRES(_Tp, _LessThanComparable);
	 return  __a < __b ? __b : __a;
 }

 template <class _Tp>
const _Tp& min(const _Tp& __a, const _Tp& __b) {
	 //__STL_REQUIRES(_Tp, _LessThanComparable);
	 return __b < __a ? __b : __a;
 }
 ///////////////////////////////////////////////////////////////////////////////
 template <class _InputIter1, class _InputIter2>
 bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
	 _InputIter2 __first2, _InputIter2 __last2) {
	 for (; __first1 != __last1 && __first2 != __last2
		 ; ++__first1, ++__first2) {
		 if (*__first1 < *__first2)
			 return true;
		 if (*__first2 < *__first1)
			 return false;
	 }
	 return __first1 == __last1 && __first2 != __last2;
 }

 template <class _InputIter1, class _InputIter2, class _Compare>
 bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
	 _InputIter2 __first2, _InputIter2 __last2, _Compare __comp)
{
	 for (; __first1 != __last1 && __first2 != __last2
		 ; ++__first1, ++__first2)
	 {
		 if (__comp(*__first1, *__first2))
			 return true;
		 if (__comp(*__first2, *__first1))
			 return false;
	 }
	 return __first1 == __last1 && __first2 != __last2;
 }

bool lexicographical_compare(const unsigned char* __first1, const unsigned char* __last1,
		 const unsigned char* __first2, const unsigned char* __last2)
 {
	 const size_t __len1 = __last1 - __first1;
	 const size_t __len2 = __last2 - __first2;
	 const int __result = memcmp(__first1, __first2, min(__len1, __len2));
	 return __result != 0 ? __result < 0 : __len1 < __len2;
 }
bool lexicographical_compare(const char* __first1, const char* __last1,
	 const char* __first2, const char* __last2)
 {
	return lexicographical_compare((const signed char*)__first1,
									(const signed char*)__last1,
									(const signed char*)__first2,
									(const signed char*)__last2);
 }
/////////////////////////////////////////////////////////////////////////////////

template <class _InputIter, class _Distance>
void __advance(_InputIter& __i, _Distance __n, 
			    input_iterator_tag)
{
	while (__n--)
		++__i;
}

template <class _BidirectionalIterator, class _Distance>
void __advance(_BidirectionalIterator& __i, _Distance __n,
			   bidirectional_iterator_tag) 
{
	//__STL_REQUIRES(_BidirectionalIterator, _BidirectionalIterator);
	if (__n >= 0)
		while (__n--) ++__i;
	else
		while (__n++) --__i;
}

template <class _RandomAccessIterator, class _Distance>
void __advance(_RandomAccessIterator& __i, _Distance __n, 
			   random_access_iterator_tag) 
{
	//__STL_REQUIRES(_RandomAccessIterator, _RandomAccessIterator);
	__i += __n;
}

template <class _InputIterator, class _Distance>
void advance(_InputIterator& __i, _Distance __n) 
{
	//__STL_REQUIRES(_InputIterator, _InputIterator);
	__advance(__i, __n, iterator_category(__i));
}