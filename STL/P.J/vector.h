#ifndef _VECTOR_H
#define _VECTOR_H

template<class _Ty, class _A = my_allocator<_Ty> >
class vector
{
public:
	typedef _A allocator_type;
	typedef _A::size_type       size_type;
	typedef _A::value_type      value_type;
	typedef _A::pointer         pointer;
	typedef _A::const_pointer   const_pointer;
	typedef _A::reference       reference;
	typedef _A::const_reference const_reference;
	typedef _A::pointer         iterator;
	typedef _A::const_pointer   const_iterator;
public:
	explicit vector(const _A &_Al = _A()) :allocator(_Al),_First(0),_Last(0),_End(0)
	{}
public:
	iterator begin()
	{return _First;}
	iterator end()
	{return _Last;}

public:
	void push_back(const _Ty &_X)
	{insert(end(), _X);}
public:
	size_type size()const
	{return _First==0 ? 0 : _Last-_First;}
public:
	iterator insert(iterator _P, const _Ty &_X = _Ty())
	{
		size_type _O = _P - begin();
		insert(_P, 1, _X);
		return begin() + _O;
	}
	void insert(iterator _P, size_type _M, const _Ty &_X)
	{
		if(_End - _Last < _M)
		{
			size_type _N = size() + (_M < size() ? size() : _M);
			iterator _S = allocator.allocate(_N, (void *)0);
			iterator _Q = _Ucopy(_First, _P, _S);
			_Ufill(_Q, _M, _X);
			_Ucopy(_P, _Last, _Q+_M);
			_Destroy(_First, _Last);
			allocator.deallocate(_First, _End - _First);
			_End = _S + _N;
			_Last = _S + size() + _M;
			_First = _S;
		}
		else if(_Last - _P < _M)
		{
			_Ucopy(_P, _Last, _P + _M);
			_Ufill(_Last, _M - (_Last - _P), _X);
			fill(_P, _Last, _X);
			_Last += _M;
		}
		else if(0 < _M)
		{
			_Ucopy(_Last - _M, _Last, _Last);
			copy_backward(_P, _Last - _M, _Last);
			fill(_P, _P + _M, _X);
			_Last += _M;
		}
	}
protected:
	void _Destroy(iterator _F, iterator _L)
	{
		for(; _F != _L; ++_F)
			allocator.destroy(_F);
	}
	iterator _Ucopy(const_iterator _F, const_iterator _L, iterator _P)
	{
		for(; _F != _L; ++_P, ++_F)
			allocator.construct(_P, *_F);
		return _P;
	}
	void _Ufill(iterator _F, size_type _N, const _Ty &_X)
	{
		for(; 0 < _N; --_N, ++_F)
			allocator.construct(_F, _X);

	}
	void _Xran()const
	{
		_THROW(out_of_range, "invalid vector<T> subscript");
	}
private:
	_A allocator;
	iterator _First;
	iterator _Last; 
	iterator _End;
};

#endif