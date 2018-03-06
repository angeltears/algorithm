#pragma once
#include <new.h>
#include "type_traits.h"
template<class _T1, class _T2>
void _Construct(_T1* __p, const _T2& __value)
{
	new((void *)__p) _T1(__value);
}


template <class _T1>
void _Construct(_T1* __p) {
	new ((void*)__p) _T1();
}


template<class _Tp>
void _Destroy(_Tp* __pointer) 
{
	__pointer->~_Tp();
}
template <class _ForwardIterator>
void __destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __false_type)
{
	for (; __first != __last; ++__first)
		destroy(&*__first);
}

template <class _ForwardIterator>
void __destroy_aux(_ForwardIterator, _ForwardIterator, __true_type) {}

template <class _ForwardIterator, class _Tp>
 void __destroy(_ForwardIterator __first, _ForwardIterator __last, _Tp*)
{
	typedef typename __type_traits<_Tp>::has_trivial_destructor _Trivial_destructor;
	__destroy_aux(__first, __last, _Trivial_destructor());
}

template <class _ForwardIterator>
void _Destroy(_ForwardIterator __first, _ForwardIterator __last)
{
	__destroy(__first, __last, value_type(__first));
}
template<>
void _Destroy(char*, char*) {}
template<>
void _Destroy(int*, int*) {}
template<>
void _Destroy(long*, long*) {}
template<>
void _Destroy(float*, float*) {}
template<>
void _Destroy(double*, double*) {}




///////////////////////////////////////////////////
template <class _T1, class _T2>
void construct(_T1* __p, const _T2& __value) 
{
	_Construct(__p, __value);
}
template <class _Tp>
void construct(_Tp* __p)
{
	_Construct(__p);
}
template <class _ForwardIterator>
void destroy(_ForwardIterator __first, _ForwardIterator __last)
{
	_Destroy(__first, __last);
}

template<class _Tp>
void destroy(_Tp * __p)
{
	_Destroy(__p);
}