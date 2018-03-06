#ifndef _MEMORY_H
#define _MEMORY_H

template<class _Ty>
_Ty *_My_Allocate(ptrdiff_t  _N, _Ty *)
{
	if (_N < 0)
		_N = 0;
	return ((_Ty*)operator new((size_t)_N * sizeof (_Ty)));
}
template<class _T1, class _T2> 
void _My_Construct(_T1 *_P, const _T2& _V)
{
	new((void *)_P) _T1(_V);  //placement new
}

//#define _DESTRUCTOR(ty, ptr)	(ptr)->~ty()
template<class _Ty>
void _My_Destroy(_Ty  *_P)
{
	//_DESTRUCTOR(_Ty, _P); 
	_P->~_Ty();
}

template<class _Ty>
class my_allocator 
{
public:
	typedef size_t        size_type;
	typedef ptrdiff_t     difference_type;
	typedef _Ty*          pointer;
	typedef const _Ty*    const_pointer;
	typedef _Ty &         reference;
	typedef const _Ty &   const_reference;
	typedef _Ty           value_type;

	pointer address(reference _X) const
	{return (&_X); }
	const_pointer address(const_reference _X) const
	{return (&_X); }

	pointer allocate(size_type _N, const void *)
	{
		return (_My_Allocate((difference_type)_N, (pointer)0));
	}
	char* _Charalloc(size_type _N)
	{
		return (_My_Allocate((difference_type)_N,(char *)0)); 
	}
	void deallocate(void  *_P, size_type)
	{
		operator delete(_P); 
	}
	void construct(pointer _P, const _Ty& _V)
	{
		_My_Construct(_P, _V); 
	}
	void destroy(pointer _P)
	{
		_My_Destroy(_P); 
	}
	size_t max_size() const
	{
		size_t _N = (size_t)(-1) / sizeof (_Ty);
		return (0 < _N ? _N : 1);
	}
};


#endif